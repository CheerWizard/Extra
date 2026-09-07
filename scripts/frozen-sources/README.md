# Frozen generated sources

This workflow stores generated sources in the repository and keeps code generation disabled in
normal builds. It derives the module name from the lowercased `rootProject.name` in
`settings.gradle.kts` and follows the conventional KMP `src/<sourceSet>/kotlin` and
`build/generated/ksp/metadata/<sourceSet>/kotlin` directories.

Copy the `scripts` folder into a project that uses Extra, keep its `enable_codegen` argument set to
`false` in the module build file, and run `scripts/install-git-hooks.sh` to install the included
commit and push checks. The module directory is expected to match the lowercased root project name.

The manifest contains repository-relative paths to every checked-in generated file. The fingerprint
script hashes all non-generated project files as inputs and hashes manifest files separately as
outputs.

## Normal development

You usually do not need to run the regeneration script. The pre-commit and pre-push hooks run a
fast fingerprint check without changing files. GitHub Actions runs the same check on pushes and
pull requests.

Install the shared hooks once in each clone:

```shell
scripts/install-git-hooks.sh
```

The hooks are already installed when `git config core.hooksPath` prints `scripts/git-hooks`.

## When regeneration is required

Run regeneration after changing anything that affects generated sources, including:

- the Extra processor, its helper processors, or templates;
- annotations or annotated models;
- types involved in generation;
- the configured codegen build file, including its release version;
- generator dependency build files or relevant dependency versions.

Use:

```shell
scripts/regenerate-sources.sh
```

The script temporarily sets `enable_codegen=true`, runs the module's KSP metadata task, discovers
generated Kotlin source sets and their conventional destinations, restores `enable_codegen=false`,
runs the module build, and updates the committed fingerprints. It keeps a temporary backup and
restores the previous snapshot if generation or verification fails.

Review and commit the resulting generated-source, manifest, and fingerprint changes together
with the source change.

## If Git blocks a commit or push

The hook prints:

```text
Frozen generated sources are stale.
Run: scripts/regenerate-sources.sh
```

Run that command, review its changes, stage them, and retry the commit or push. Hooks only verify;
they do not regenerate or stage files automatically.

You can run the fast check directly at any time:

```shell
scripts/frozen-sources-fingerprint.py
```

Local hooks can be bypassed with `--no-verify`, but the GitHub Actions check will still reject a
stale snapshot.
