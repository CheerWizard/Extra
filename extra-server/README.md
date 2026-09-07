# Extra server

`extra-server` adapts Ktor server calls to the direction-neutral primitives in `extra-http`. It is a JVM library and does not choose or start a Ktor engine.

```kotlin
routing {
    get("/scene") {
        val encoded = scene.encode()
        call.respondNativeBuffer(encoded)
    }

    post("/scene") {
        val scene = call.receiveDecodedNativeBuffer { decodeScene() }
        // Use scene...
    }
}
```

The adapter writes through a reusable bounded staging array. Ktor applies backpressure and HTTP/TCP performs network packet framing. `NativeBuffer` memory boundary is intentionally not transmitted because it is a local allocation policy.

Ktor JSON or any other `ContentNegotiation` format can be installed alongside these explicit binary functions without additional configuration.
