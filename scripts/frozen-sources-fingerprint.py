#!/usr/bin/env python3
import argparse
import hashlib
import re
from pathlib import Path


ROOT = Path(__file__).resolve().parent.parent
STATE_DIR = ROOT / "scripts" / "frozen-sources"
MANIFEST = STATE_DIR / "generated-files.txt"
FINGERPRINT = STATE_DIR / "inputs.sha256"
SETTINGS = ROOT / "settings.gradle.kts"


def project_name() -> str:
    match = re.search(r'^\s*rootProject\.name\s*=\s*["\']([^"\']+)["\']', SETTINGS.read_text(), re.MULTILINE)
    if match is None:
        raise RuntimeError(f"Could not find rootProject.name in {SETTINGS}.")
    return match.group(1).lower()


def check_enable_codegen(module: str) -> bool:
    build_file = ROOT / module / "build.gradle.kts"
    if not build_file.is_file():
        print(f"Missing codegen configuration file: {build_file}.")
        return False
    pattern = re.compile(
        r'^\s*arg\("enable_codegen",\s*"(true|false)"\)\s*$',
        re.MULTILINE,
    )
    matches = pattern.findall(build_file.read_text())
    if any(value == "true" for value in matches):
        print(f"{build_file.relative_to(ROOT)} must keep enable_codegen=false for committed/release sources.")
        print("Run scripts/regenerate-sources.sh to generate sources and restore the flag.")
        return False
    return True


def input_files(module: str) -> list[Path]:
    generated = {
        (ROOT / line).resolve()
        for line in MANIFEST.read_text().splitlines()
        if line
    }
    automation = (ROOT / "scripts").resolve()
    candidates = [
        ROOT / "settings.gradle.kts",
        ROOT / "build.gradle.kts",
        ROOT / "gradle.properties",
        ROOT / "gradle",
        ROOT / module / "build.gradle.kts",
        ROOT / module / "src",
    ]
    extra_gen = ROOT / "extra-gen"
    if extra_gen.is_dir():
        candidates.extend([extra_gen / "build.gradle.kts", extra_gen / "src"])
    expanded = []
    for path in candidates:
        expanded.extend(path.rglob("*") if path.is_dir() else [path])
    return sorted(
        path for path in expanded
        if path.is_file()
        and path.resolve() not in generated
        and automation not in path.resolve().parents
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
    try:
        module = project_name()
    except (OSError, RuntimeError) as error:
        print(error)
        return 1
    if not check_enable_codegen(module):
        return 1
    actual_inputs = hash_files(input_files(module))
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
        print("Frozen generated sources are stale.")
        print("Run: scripts/regenerate-sources.sh")
        return 1
    print("Frozen generated-source fingerprint is current.")
    return 0


if __name__ == "__main__":
    raise SystemExit(main())
