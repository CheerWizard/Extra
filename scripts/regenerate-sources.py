#!/usr/bin/env python3
import re
import shutil
import subprocess
import sys
import tempfile
from pathlib import Path


ROOT = Path(__file__).resolve().parent.parent
STATE_DIR = ROOT / "scripts" / "frozen-sources"
MANIFEST = STATE_DIR / "generated-files.txt"
SETTINGS = ROOT / "settings.gradle.kts"


def project_name() -> str:
    match = re.search(r'^\s*rootProject\.name\s*=\s*["\']([^"\']+)["\']', SETTINGS.read_text(), re.MULTILINE)
    if match is None:
        raise RuntimeError(f"Could not find rootProject.name in {SETTINGS}.")
    return match.group(1).lower()


def set_codegen(build_file: Path, value: bool) -> None:
    text = build_file.read_text()
    pattern = re.compile(r'^\s*arg\("enable_codegen",\s*"(true|false)"\)\s*$', re.MULTILINE)
    if len(pattern.findall(text)) != 1:
        raise RuntimeError(f"Expected exactly one enable_codegen declaration in {build_file}.")
    build_file.write_text(pattern.sub(f'    arg("enable_codegen", "{str(value).lower()}")', text, count=1))


def manifest_files() -> list[Path]:
    return [ROOT / line for line in MANIFEST.read_text().splitlines() if line]


def generated_roots(module: Path) -> list[tuple[str, Path]]:
    metadata = module / "build/generated/ksp/metadata"
    return [
        (root.name, root / "kotlin")
        for root in sorted(metadata.iterdir())
        if root.is_dir() and (root / "kotlin").is_dir()
    ] if metadata.is_dir() else []


def destination_for(
    generated: Path,
    source_set: str,
    module: Path,
    old_files: set[Path],
) -> Path:
    relative = generated.relative_to(next(root for name, root in generated_roots(module) if generated.is_relative_to(root)))
    suffix_matches = [path for path in old_files if path.as_posix().endswith(f"/{relative.as_posix()}")]
    if len(suffix_matches) == 1:
        return suffix_matches[0]

    package_dir = relative.parent
    source_root = module / "src"
    candidates = []
    if source_root.is_dir():
        for kotlin_root in source_root.glob("*/kotlin"):
            if (kotlin_root / package_dir).is_dir():
                candidates.append(kotlin_root)
    preferred = source_root / source_set.replace("Main", "Test") / "kotlin"
    root = preferred if preferred in candidates else (candidates[0] if candidates else source_root / source_set / "kotlin")
    return root / relative


def collect_generated(module: Path, old_files: set[Path]) -> list[tuple[Path, Path]]:
    collected = []
    for source_set, root in generated_roots(module):
        for generated in root.rglob("*.kt"):
            collected.append((generated, destination_for(generated, source_set, module, old_files)))
    return sorted(collected, key=lambda pair: pair[1].as_posix())


def restore_snapshot(backup_dir: Path, original_manifest: str) -> None:
    for path in manifest_files():
        path.unlink(missing_ok=True)
    snapshot = backup_dir / "snapshot"
    for backup in snapshot.rglob("*"):
        if backup.is_file():
            destination = ROOT / backup.relative_to(snapshot)
            destination.parent.mkdir(parents=True, exist_ok=True)
            shutil.copy2(backup, destination)
    MANIFEST.write_text(original_manifest)


def main() -> int:
    try:
        module_name = project_name()
        module = ROOT / module_name
        build_file = module / "build.gradle.kts"
        original_manifest = MANIFEST.read_text()
        original_files = manifest_files()
        if not build_file.is_file() or not original_files:
            raise RuntimeError("Codegen configuration or frozen-source manifest is incomplete.")
    except (OSError, RuntimeError) as error:
        print(error, file=sys.stderr)
        return 1

    backup_dir = Path(tempfile.mkdtemp(prefix="frozen-sources-"))
    flag_enabled = False
    generation_completed = False
    try:
        for path in original_files:
            if path.is_file():
                backup = backup_dir / "snapshot" / path.relative_to(ROOT)
                backup.parent.mkdir(parents=True, exist_ok=True)
                shutil.copy2(path, backup)
        set_codegen(build_file, True)
        flag_enabled = True
        print("Setting enable_codegen=true to enable KSP generation.")
        for path in original_files:
            path.unlink(missing_ok=True)

        subprocess.run(["./gradlew", f":{module_name}:clean", f":{module_name}:kspCommonMainKotlinMetadata", "-PregenerateFrozenSources=true"], cwd=ROOT, check=True)
        generated = collect_generated(module, set(original_files))
        if not generated:
            raise RuntimeError("KSP generated no Kotlin sources; refusing an empty snapshot.")
        for source, destination in generated:
            destination.parent.mkdir(parents=True, exist_ok=True)
            shutil.copy2(source, destination)
        MANIFEST.write_text("".join(f"{path.relative_to(ROOT)}\n" for _, path in generated))
        generation_completed = True
        subprocess.run([sys.executable, str(ROOT / "scripts/frozen-sources-fingerprint.py"), "--write"], cwd=ROOT, check=True)
        print("Restored enable_codegen=false.")
        set_codegen(build_file, False)
        flag_enabled = False
        return 0
    except (OSError, RuntimeError, subprocess.CalledProcessError) as error:
        print(f"Regeneration failed: {error}", file=sys.stderr)
        if not generation_completed:
            restore_snapshot(backup_dir, original_manifest)
        return 1
    finally:
        if flag_enabled:
            set_codegen(build_file, False)
            print("Restored enable_codegen=false.")
        shutil.rmtree(backup_dir, ignore_errors=True)


if __name__ == "__main__":
    raise SystemExit(main())
