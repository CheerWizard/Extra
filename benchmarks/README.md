# ECS JMH benchmarks

The benchmark compares equivalent Extra and Fleks workloads in forked JVMs at 10,000 and
100,000 entities.

Run the full benchmark:

```shell
./gradlew :benchmarks:jmh
```

Run the short harness smoke test:

```shell
./gradlew :benchmarks:jmhSmoke
```

The full run writes JSON to `benchmarks/build/results/jmh/results.json`. It uses two forks, five
one-second warm-up iterations, ten one-second measurement iterations, and the JMH GC profiler.

Scores are nanoseconds per complete workload invocation. Divide `Score` and normalized `B/op` by
the `entityCount` parameter for per-entity values. For `createRemove`, divide by twice the entity
count. The mixed workload performs 6.5 logical operations per entity.

Invocation setup is outside measured time for destructive single-operation benchmarks. The
`sceneCreation`, `createRemove`, and `mixed` benchmarks intentionally include ECS construction.
