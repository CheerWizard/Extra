# Extra HTTP

`extra-http` contains the direction-neutral, multiplatform bridge between `NativeBuffer` and Ktor HTTP channels.

It owns:

- `NativeBufferWireFormat` and its HTTP media type parameters.
- `NativeBufferContent`, used as either a client request or server response body.
- `ByteWriteChannel.writeNativeBuffer()` for bounded production.
- `ByteReadChannel.readNativeBuffer()` for aggregate reception.
- `ByteReadChannel.forEachNativeBufferChunk()` for allocation-conscious incremental consumption.

The module depends only on Ktor HTTP and I/O APIs. It does not depend on Ktor Client, Ktor Server, or a platform network engine.
