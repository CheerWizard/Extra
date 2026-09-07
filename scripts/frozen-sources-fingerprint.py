#!/usr/bin/env python3
import argparse
import hashlib
from pathlib import Path


ROOT = Path(__file__).resolve().parent.parent
STATE_DIR = ROOT / "scripts" / "frozen-sources"
MANIFEST = STATE_DIR / "generated-files.txt"
FINGERPRINT = STATE_DIR / "inputs.sha256"


def input_files() -> list[Path]:
    generated = {
        (ROOT / line).resolve()
        for line in MANIFEST.read_text().splitlines()
        if line
    }
    candidates = [
        ROOT / "extra/build.gradle.kts",
        ROOT / "extra-gen/build.gradle.kts",
        ROOT / "gradle/libs.versions.toml",
    ]
    candidates.extend((ROOT / "extra-gen/src").rglob("*"))
    candidates.extend((ROOT / "extra/src/commonMain").rglob("*"))
    candidates.extend((ROOT / "extra/src/commonTest/kotlin/com/cws/extra/test").rglob("*"))
    return sorted(
        path for path in candidates
        if path.is_file() and path.resolve() not in generated
    )


def hash_files(paths: list[Path]) -> str:
    digest = hashlib.sha256()
    for path in paths:
        relative = path.relative_to(ROOT).as_posix().encode()
        digest.update(len(relative).to_bytes(4, "big"))
        digest.update(relative)
        content = path.read_bytes()
        digest.update(len(content).to_bytes(8, "big"))
        digest.update(content)
    return digest.hexdigest()


def generated_files() -> list[Path]:
    return [
        ROOT / line
        for line in MANIFEST.read_text().splitlines()
        if line
    ]


def main() -> int:
    parser = argparse.ArgumentParser()
    parser.add_argument("--write", action="store_true")
    args = parser.parse_args()
    actual_inputs = hash_files(input_files())
    actual_outputs = hash_files(generated_files())
    if args.write:
        FINGERPRINT.write_text(
            f"inputs {actual_inputs}\noutputs {actual_outputs}\n"
        )
        print(f"Updated {FINGERPRINT.relative_to(ROOT)}")
        return 0

    expected = FINGERPRINT.read_text().splitlines() if FINGERPRINT.exists() else []
    actual = [f"inputs {actual_inputs}", f"outputs {actual_outputs}"]
    if actual != expected:
        print("Frozen Extra sources are stale.")
        print("Run: scripts/regenerate-sources.sh")
        return 1
    print("Frozen Extra source fingerprint is current.")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
