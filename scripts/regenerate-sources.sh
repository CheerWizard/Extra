#!/usr/bin/env bash
set -euo pipefail

repo_root="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"

manifest="$repo_root/scripts/frozen-sources/generated-files.txt"
processor="$repo_root/extra-gen/src/main/kotlin/com/cws/extra/gen/ExtraProcessor.kt"
generated_metadata_root="$repo_root/extra/build/generated/ksp/metadata"
generated_common_root="$generated_metadata_root/commonMain/kotlin"
generated_jni_root="$generated_metadata_root/jniMain/kotlin"

cd "$repo_root"

if [[ ! -f settings.gradle.kts || ! -f "$processor" || ! -f "$manifest" ]]; then
    echo "The Extra repository or frozen-source state files are incomplete." >&2
    exit 1
fi

if ! grep -Fq 'private const val FREEZE_VERSION =' "$processor"; then
    echo "Missing FREEZE_VERSION declaration in $processor." >&2
    exit 1
fi

frozen_files=()
while IFS= read -r path; do
    [[ -n "$path" ]] && frozen_files+=("$path")
done < "$manifest"

for path in "${frozen_files[@]}"; do
    if [[ ! -f "$path" ]]; then
        echo "Manifest path is missing: $path" >&2
        exit 1
    fi
done

if [[ -n "$(git status --porcelain -- "${frozen_files[@]}")" ]]; then
    echo "Replacing uncommitted files from the generated snapshot (a rollback backup will be kept)."
fi

backup_dir="$(mktemp -d "${TMPDIR:-/tmp}/extra-freeze.XXXXXX")"
flag_restored=false

restore_flag() {
    if [[ "$flag_restored" == false ]]; then
        python3 - "$processor" <<'PY'
from pathlib import Path
import sys
path = Path(sys.argv[1])
text = path.read_text()
path.write_text(text.replace(
    "private const val FREEZE_VERSION = false",
    "private const val FREEZE_VERSION = true",
    1,
))
PY
        flag_restored=true
    fi
}

rollback() {
    status=$?
    restore_flag
    if [[ $status -ne 0 ]]; then
        echo "Regeneration failed; restoring the previous frozen snapshot." >&2
        while IFS= read -r path; do
            [[ -n "$path" ]] && rm -f -- "$path"
        done < "$manifest"
        tar -xf "$backup_dir/snapshot.tar" -C "$repo_root"
        cp "$backup_dir/generated-files.txt" "$manifest"
    fi
    rm -rf -- "$backup_dir"
    exit $status
}
trap rollback EXIT

tar -cf "$backup_dir/snapshot.tar" "${frozen_files[@]}"
cp "$manifest" "$backup_dir/generated-files.txt"

echo "Setting FREEZE_VERSION=false to enable KSP generation."
python3 - "$processor" <<'PY'
from pathlib import Path
import re
import sys
path = Path(sys.argv[1])
text = path.read_text()
pattern = r"private const val FREEZE_VERSION = (?:true|false)"
if len(re.findall(pattern, text)) != 1:
    raise SystemExit("Expected exactly one FREEZE_VERSION declaration")
path.write_text(re.sub(
    pattern,
    "private const val FREEZE_VERSION = false",
    text,
    count=1,
))
PY

for path in "${frozen_files[@]}"; do
    rm -f -- "$path"
done

./gradlew :extra:clean :extra:kspCommonMainKotlinMetadata -PregenerateFrozenSources=true

new_manifest="$backup_dir/new-generated-files.txt"
{
    find "$generated_common_root" -type f -name '*.kt' -print0 |
        while IFS= read -r -d '' generated; do
            relative="${generated#"$generated_common_root/"}"
            if [[ "$relative" == com/cws/extra/test/* ]]; then
                destination="extra/src/commonTest/kotlin/$relative"
            else
                destination="extra/src/commonMain/kotlin/$relative"
            fi
            mkdir -p "$(dirname "$destination")"
            cp "$generated" "$destination"
            echo "$destination"
        done

    if [[ -d "$generated_jni_root" ]]; then
        find "$generated_jni_root" -type f -name '*.kt' -print0 |
            while IFS= read -r -d '' generated; do
                relative="${generated#"$generated_jni_root/"}"
                if [[ "$relative" == com/cws/extra/test/* ]]; then
                    destination="extra/src/jniTest/kotlin/$relative"
                else
                    destination="extra/src/jniMain/kotlin/$relative"
                fi
                mkdir -p "$(dirname "$destination")"
                cp "$generated" "$destination"
                echo "$destination"
            done
    fi
} | sort > "$new_manifest"

if [[ ! -s "$new_manifest" ]]; then
    echo "KSP generated no Kotlin sources; refusing an empty snapshot." >&2
    exit 1
fi
cp "$new_manifest" "$manifest"
restore_flag
echo "Restored FREEZE_VERSION=true; verifying the frozen build."

./gradlew :extra:clean :extra:compileKotlinDesktop :benchmarks:jmhClasses

generated_count=0
if [[ -d "$generated_metadata_root" ]]; then
    generated_count="$(find "$generated_metadata_root" -type f -name '*.kt' | wc -l | tr -d ' ')"
fi
if [[ "$generated_count" != 0 ]]; then
    echo "Frozen verification unexpectedly generated $generated_count Kotlin files." >&2
    exit 1
fi

"$repo_root/scripts/frozen-sources-fingerprint.py" --write

trap - EXIT
rm -rf -- "$backup_dir"
echo "Frozen Extra snapshot regenerated and verified."
