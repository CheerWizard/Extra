1.0.19

  ## Additions

  - Added new client, server, HTTP, and benchmark modules.
  - Added a redesigned ECS querying and component-storage system.
  - Added frozen generated sources to reduce build-time code generation.
  - Added automated regeneration tooling, documentation, Git hooks, fingerprints, and CI verification.
  - Added `ExtraBridge`, `ExtraBridgeData`, and `ExtraBridgeEnum` annotations for generating the complete Kotlin/C++ JNI bridge, allowing developers to implement only the C++ code that interacts with the library exposed to Kotlin after code generation.
  - Expanded collection, math, serialization, and native-buffer functionality.
  - Added broader regression and ECS test coverage.

  ## Removals

  - Removed legacy profiling and memory-management APIs.
  - Removed test fixtures and benchmark code from production sources.
  - Removed manual performance tests from unit-test source sets.
  - Removed obsolete generated artifacts and development files.

  ## Breaking Changes

  - Significant ECS and query API restructuring.
  - Component storage and registration behavior has changed.
  - Some previously internal ECS state is now publicly accessible for generated client code.
  - Legacy profiler and memory APIs are no longer available.
  - Generated-source layout and regeneration workflow have changed.
  - Test fixtures are no longer included in production artifacts.

  ## Bug Fixes

  - Fixed generated component code failing outside the main module.
  - Fixed serialization and collection handling for generated structures.
  - Fixed several primitive, unsigned, nested, and structure-of-arrays generation issues.
  - Fixed query correctness, lifecycle, filtering, sorting, and iteration edge cases.
  - Fixed cross-platform file and native-buffer inconsistencies.
  - Fixed stale or duplicate generated-source behavior.

  ## Performance

  - Reduced normal KSP workload by freezing Extra’s generated sources.
  - Improved ECS querying and storage access paths.
  - Expanded primitive-list operations and optimized math utilities.
  - Moved performance measurement to a dedicated forked JMH environment.

  ## Testing

  - Added regression tests for queries, component storage, serialization, lists, and native buffers.
  - Added comparative JMH benchmarks.
  - Verified production, test, and benchmark compilation.
  - Verified production artifacts exclude test fixtures.
  - Added commit, push, and CI checks for stale generated sources.
