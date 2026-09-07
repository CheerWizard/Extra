# Frozen Extra sources

Extra checks its production generated KSP sources into `extra/src/commonMain` and its test-only
fixtures into `extra/src/commonTest`. Normal builds keep `ExtraProcessor.FREEZE_VERSION` enabled,
so building Extra or a client project does not regenerate those sources.

## Normal development

You usually do not need to run the regeneration script. The pre-commit and pre-push hooks run a
fast fingerprint check without changing files. GitHub Actions runs the same check on pushes and
pull requests.

Install the shared hooks once in each clone:

```shell
scripts/install-git-hooks.sh
```

The hooks are already installed when `git config core.hooksPath` prints `.githooks`.

## When regeneration is required

Run regeneration after changing anything that affects generated Extra sources, including:

- ExtraProcessor, its helper processors, or templates;
- annotations or annotated Extra models;
- primitive or math types involved in generation;
- `extra/build.gradle.kts`, including the Extra release version;
- `extra-gen/build.gradle.kts` or relevant dependency versions.

Use:

```shell
scripts/regenerate-sources.sh
```

The script temporarily unfreezes Extra, replaces the manifest-owned generated files, restores
the freeze, exposes test fixtures to KSP only for the regeneration task, compiles Extra and the
JMH sources, and updates the committed fingerprints. It keeps a temporary backup and restores
the previous snapshot if generation or verification fails.

Review and commit the resulting generated-source, manifest, and fingerprint changes together
with the source change.

## If Git blocks a commit or push

The hook prints:

```text
Frozen Extra sources are stale.
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
