# Extra client

`extra-client` adapts Ktor client requests and responses to the direction-neutral primitives in `extra-http`. Applications inject and configure their own `HttpClient` and engine.

```kotlin
val scene = client.get("https://example.test/scene")
    .decodeNativeBuffer { decodeScene() }

client.post("https://example.test/scene") {
    setNativeBufferBody(scene.encode())
}
```

`bodyAsNativeBuffer()` incrementally assembles a response into one `NativeBuffer` without first creating a full-body `ByteArray`. This is required by current generated decoders, which consume a contiguous buffer.

For incrementally processable payloads, `forEachNativeBufferChunk()` uses one reusable `NativeBuffer`. The chunk is valid only while its callback is running.

JSON and other formats remain available through the normal Ktor client `ContentNegotiation` plugin.
