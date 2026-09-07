# Extra maintenance TODO

- [x] Freeze all generated Extra module sources in `extra/src/commonMain`; when `FREEZE_VERSION`
  is enabled, `ExtraProcessor` returns immediately for the `extra` project. Disable the switch
  only while deliberately refreshing the checked-in generated sources. Use
  `scripts/regenerate-sources.sh` for that maintenance operation. Git commit/push
  hooks and CI verify the frozen-input fingerprint. See `scripts/frozen-sources/README.md`.
- [x] Remove obsolete packages from the `extra` module. The unused `com.cws.extra.profiler`
  package has been removed.
- [x] Move performance benchmarks out of test source sets and into the dedicated `benchmarks`
  JMH module. Run `./gradlew :benchmarks:jmhSmoke` for a short verification or
  `./gradlew :benchmarks:jmh` for the full suite.
