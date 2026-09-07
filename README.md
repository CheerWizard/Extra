# Extra

[![Maven Central](https://img.shields.io/maven-central/v/io.github.cheerwizard/extra)](https://search.maven.org/)
[![Kotlin Multiplatform](https://img.shields.io/badge/Kotlin-Multiplatform-blue.svg)](https://kotlinlang.org/)
[![License](https://img.shields.io/badge/License-Apache%202.0-green.svg)](LICENSE)

Extra is a Kotlin Multiplatform foundation for applications that need predictable memory,
binary data, native interoperability, and data-oriented runtime structures. It is designed for
game engines, rendering systems, native library bindings, servers, and other performance-sensitive
software that still wants a shared Kotlin API across platforms.

Kotlin gives application developers excellent productivity, but it intentionally does not provide
a portable abstraction for externally owned memory, GPU-compatible layouts, typed primitive
collections, or generated C++/JNI bindings. Extra fills that systems-programming gap while keeping
the public API Kotlin-first.

## What Extra provides

### Native memory and binary data

`NativeBuffer` is a cross-platform byte buffer that can be allocated on the Kotlin heap, backed by
external memory, or wrapped around an existing native address or `ByteArray`. It supports:

- Explicit position, limit, capacity, resize, copy, and release operations.
- Primitive and unsigned primitive reads and writes, including arrays.
- Little- and big-endian access.
- Kotlin, `STD140`, and `STD430` memory layouts for ordinary data and GPU buffers.
- Packed and aligned encodings for predictable interop with C, C++, graphics APIs, and files.

This makes the same data model usable in Kotlin, native code, and binary transport without
converting every value through temporary object graphs or whole-body byte arrays.

```kotlin
val buffer = NativeBuffer(
    capacity = 1024,
    memoryLayout = MemoryLayout.STD140,
    memoryBoundary = MemoryBoundary.EXTERNAL,
)

buffer.setFloat(0, 1.0f)
buffer.setInt(16, 42)
val value = buffer.getInt(16)
buffer.release()
```

### Code generation and native bridges

`extra-gen` is a KSP processor for generated binary encoders, decoders, typed list operations,
component storage, and native bridge code. It can generate Kotlin and C++ representations from
the same declarations.

Common annotations include:

- `@ExtraData`, `@ExtraDataSoA`, and `@ExtraEnum` for Kotlin binary serialization.
- `@ExtraList` for generated structure-of-arrays collection implementations.
- `@ExtraComponent` for generated ECS component storage.
- `@ExtraBridge`, `@ExtraBridgeData`, `@ExtraBridgeDataSoA`, and `@ExtraBridgeEnum` for Kotlin/C++
  bridge declarations and JNI or C-interop transport.
- `@ExtraFixedSize` and `@ExtraStringUtf16` for fields whose native representation needs explicit
  sizing or encoding.

For a native library binding, the developer describes the Kotlin-facing interface and data types,
runs code generation, and implements the C++ functions that actually call the target library.
Extra generates the repetitive Kotlin/C++ declarations, serialization code, and JNI transport.

```kotlin
@ExtraBridge("MyNativeLibrary")
interface MyNativeLibrary {
    fun create(config: CreateConfig): Long
    fun destroy(handle: Long)
}

@ExtraBridgeData
data class CreateConfig(
    val width: Int,
    val height: Int,
)
```

Generated sources can be committed and frozen for released libraries. Set `enable_codegen=true`
while developing or regenerating a module, then set it back to `false` before committing. The
included scripts and Git hooks check the flag and the generated-source fingerprint so downstream
projects do not repeatedly regenerate code shipped by their dependencies.

### Data-oriented collections and ECS

Extra includes resizable primitive lists for signed, unsigned, floating-point, boolean, byte, and
character values. It also includes vector and matrix list types designed for structure-of-arrays
access, with generated binary encoding and decoding operations.

The ECS provides:

- Integer entity identifiers and reusable entity pools.
- Explicit component registration and component storage.
- Generated component storage for efficient typed access.
- Queries over one to five component types.
- Filtering, sorting, limiting, reversing, shuffling, and iteration operations.
- Scene and component-state serialization through `NativeBuffer`.

```kotlin
val scene = Scene()
val entity = scene.create(Position(10f, 20f), Velocity(1f, 0f))

scene.query<Position, PositionList, Velocity, VelocityList>()
    .forEach { _, positions, positionIndex, velocities, velocityIndex ->
        positions.x[positionIndex] += velocities.x[velocityIndex]
    }
```

### Math for engine and graphics code

The math package contains float, int, and unsigned vector types, matrices, quaternions, generated
vector and matrix lists, and common operations such as clamp, dot, cross, normalize, length, lerp,
reflection, refraction, interpolation, transpose, determinant, and inverse.

The types integrate with Extra's memory layouts and generated encoders, which is useful when values
must move between simulation code, render queues, GPU buffers, and native graphics libraries.

### Concurrency, files, storage, and platform information

The core module also provides multiplatform building blocks for systems code:

- `RingBuffer` and lock-protected `ConcurrentRingBuffer`.
- A multiplatform `Thread` abstraction with start and join operations.
- File access with byte-array and `NativeBuffer` I/O, mapping, flushing, and scoped use.
- Typed `Preferences` storage for primitive values and strings.
- `PlatformInfo` for memory information, thread limits, process identity, and current thread data.

## Modules

| Module | Purpose |
| --- | --- |
| `extra` | Core memory, serialization, collections, math, ECS, concurrency, file, storage, and platform APIs. |
| `extra-gen` | KSP processor for Kotlin serialization, collections, ECS storage, and C++/JNI bridge generation. |
| `extra-http` | Ktor-independent client/server primitives for sending and receiving `NativeBuffer` data. |
| `extra-client` | Ktor client extensions for native-buffer requests, responses, aggregate decoding, and chunked reads. |
| `extra-server` | Ktor server extensions for native-buffer responses and decoded requests. JVM only. |
| `benchmarks` | Forked JMH comparisons for Extra ECS workloads. Not a runtime dependency. |

The HTTP modules keep binary transport explicit. JSON and other Ktor content negotiation formats can
be used alongside them when a human-readable or interoperable format is more appropriate.

## Supported targets

The core and multiplatform HTTP/client modules currently target:

- Android
- JVM desktop
- iOS device and simulator
- Linux x64
- macOS ARM64
- Windows MinGW x64
- JavaScript in the browser
- WebAssembly JavaScript in the browser

`extra-server` and `extra-gen` have narrower platform roles: the server adapter is JVM-oriented,
while the generator runs as a JVM/KSP build tool.

## Installation

Add the core library to a Kotlin Multiplatform module:

```kotlin
repositories {
    mavenCentral()
}

commonMain.dependencies {
    implementation("io.github.cheerwizard:extra:1.0.19")
}
```

Add the optional modules only when needed:

```kotlin
commonMain.dependencies {
    implementation("io.github.cheerwizard:extra-http:1.0.19")
    implementation("io.github.cheerwizard:extra-client:1.0.19")
}

jvmMain.dependencies {
    implementation("io.github.cheerwizard:extra-server:1.0.19")
}
```

To generate code in your own module, apply KSP and add `extra-gen`. Code generation is opt-in;
set the argument to `true` while developing your generated types:

```kotlin
plugins {
    alias(libs.plugins.ksp)
}

dependencies {
    add("kspCommonMainMetadata", "io.github.cheerwizard:extra-gen:1.0.19")
}

ksp {
    arg("project_name", project.name)
    arg("enable_codegen", "true")
}
```

Before publishing a library with generated sources, commit the generated output and set
`enable_codegen=false`. The frozen-source workflow in `scripts/` can regenerate, verify, and
fingerprint that snapshot.

## Why Extra matters in Kotlin

Kotlin is a strong language for expressing engine, application, and service logic, but many
projects still leave Kotlin at their boundaries: native APIs, GPU memory, binary protocols, and
high-throughput collections are implemented separately in C++, JVM code, or platform-specific
Kotlin. That creates duplicated data models and different alignment, ownership, and serialization
rules on every target.

Extra makes those boundaries explicit and reusable. A Kotlin declaration can define the data shape,
memory layout, generated collection operations, and native bridge, while platform-specific code is
limited to the part that genuinely depends on the target library or operating system. This keeps
shared code expressive without hiding the ownership and performance decisions that systems software
needs.

## Development

Run the test suite with:

```shell
./run_tests.sh
```

Run the ECS benchmark harness with:

```shell
./gradlew :benchmarks:jmhSmoke
```

The repository uses frozen generated sources. Install the local commit and push checks with:

```shell
scripts/install-git-hooks.sh
```

## License

Licensed under the Apache License, Version 2.0. See [LICENSE](LICENSE).
