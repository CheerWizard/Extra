#!/usr/bin/env bash
set -euo pipefail

repo_root="$(cd "$(dirname "${BASH_SOURCE[0]}")/.." && pwd)"
cd "$repo_root"
git config core.hooksPath scripts/git-hooks
echo "Installed repository hooks from scripts/git-hooks."
