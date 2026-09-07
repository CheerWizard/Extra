/*
 * Copyright 2026 CheerWizard
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     https://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
package com.cws.extra.server

import com.cws.extra.client.bodyAsNativeBuffer
import com.cws.extra.client.decodeNativeBuffer
import com.cws.extra.client.forEachNativeBufferChunk
import com.cws.extra.client.setNativeBufferBody
import com.cws.extra.ecs.Scene
import com.cws.extra.ecs.decodeScene
import com.cws.extra.ecs.encode
import com.cws.extra.memory.Endian
import com.cws.extra.memory.MemoryLayout
import com.cws.extra.memory.NativeBuffer
import com.cws.extra.memory.getInt
import com.cws.extra.memory.getLong
import com.cws.extra.memory.setInt
import com.cws.extra.memory.setLong
import io.ktor.client.request.get
import io.ktor.client.request.post
import io.ktor.client.statement.bodyAsText
import io.ktor.http.ContentType
import io.ktor.http.HttpStatusCode
import io.ktor.server.response.respondText
import io.ktor.server.routing.get
import io.ktor.server.routing.post
import io.ktor.server.routing.routing
import io.ktor.server.testing.testApplication
import kotlin.test.BeforeTest
import kotlin.test.Test
import kotlin.test.assertContentEquals
import kotlin.test.assertEquals
import kotlin.test.assertFailsWith
import kotlin.test.assertSame
import kotlin.test.assertTrue

class NativeBufferTransportTest {

    @BeforeTest
    fun registerComponents() {
        ExtraComponents.registerAll()
    }

    @Test
    fun `server response is assembled without one giant ByteArray`() = testApplication {
        val bytes = patternedBytes(256 * 1024 + 37)
        val source = NativeBuffer(bytes, memoryLayout = MemoryLayout.KOTLIN, endian = Endian.BIG)
        application {
            routing {
                get("/buffer") {
                    call.respondNativeBuffer(source, chunkSize = 8191)
                }
            }
        }

        val received = client.get("/buffer").bodyAsNativeBuffer(chunkSize = 4093)

        assertEquals(source.limit, received.limit)
        assertEquals(Endian.BIG, received.endian)
        assertEquals(MemoryLayout.KOTLIN, received.memoryLayout)
        assertContentEquals(bytes, received.toByteArray())
    }

    @Test
    fun `KSP encoded Scene round trips through server and client`() = testApplication {
        val scene = Scene(entityCount = 32)
        val expectedEntity = scene.create(
            Movement(speed = 19.5f),
            Camera(fov = 83f),
        )
        val encoded = scene.encode(endian = Endian.BIG)
        application {
            routing {
                get("/scene") {
                    call.respondNativeBuffer(encoded, chunkSize = 5)
                }
            }
        }

        val decoded = client.get("/scene").decodeNativeBuffer { decodeScene() }

        assertTrue(decoded.hasEntity(expectedEntity))
        var matches = 0
        decoded.query<Movement, MovementList, Camera, CameraList>().forEach {
                entity,
                movements,
                movementIndex,
                cameras,
                cameraIndex,
            ->
            assertEquals(expectedEntity, entity)
            assertEquals(19.5f, movements.speed[movementIndex])
            assertEquals(83f, cameras.fov[cameraIndex])
            matches++
        }
        assertEquals(1, matches)
    }

    @Test
    fun `client NativeBuffer request is decoded and echoed by server`() = testApplication {
        application {
            routing {
                post("/echo") {
                    val received = call.receiveNativeBuffer(chunkSize = 3)
                    call.respondNativeBuffer(received, chunkSize = 5)
                }
            }
        }
        val source = NativeBuffer(16, endian = Endian.BIG).apply {
            setInt(0, 0x12345678)
            setLong(4, 0x0102030405060708L)
            setInt(12, -77)
        }

        val response = client.post("/echo") {
            setNativeBufferBody(source, chunkSize = 7)
        }
        val echoed = response.bodyAsNativeBuffer(chunkSize = 4)

        assertEquals(HttpStatusCode.OK, response.status)
        assertEquals(Endian.BIG, echoed.endian)
        assertContentEquals(source.toByteArray(), echoed.toByteArray())
        assertEquals(0x12345678, echoed.getInt(0))
        assertEquals(0x0102030405060708L, echoed.getLong(4))
        assertEquals(-77, echoed.getInt(12))
    }

    @Test
    fun `client chunk consumer receives ordered chunks using one buffer`() = testApplication {
        val bytes = patternedBytes(41)
        val source = NativeBuffer(bytes)
        application {
            routing {
                get("/chunks") {
                    call.respondNativeBuffer(source, chunkSize = 6)
                }
            }
        }
        val reconstructed = ByteArray(bytes.size)
        var firstChunk: NativeBuffer? = null
        var calls = 0

        client.get("/chunks").forEachNativeBufferChunk(chunkSize = 8) { offset, chunk ->
            if (firstChunk == null) {
                firstChunk = chunk
            } else {
                assertSame(firstChunk, chunk)
            }
            chunk.toByteArray().copyInto(reconstructed, offset.toInt())
            calls++
        }

        assertEquals(6, calls)
        assertContentEquals(bytes, reconstructed)
    }

    @Test
    fun `server chunk consumer handles streamed client request`() = testApplication {
        application {
            routing {
                post("/sum") {
                    var sum = 0L
                    var expectedOffset = 0L
                    var firstChunk: NativeBuffer? = null
                    call.forEachNativeBufferChunk(chunkSize = 11) { offset, chunk ->
                        assertEquals(expectedOffset, offset)
                        if (firstChunk == null) {
                            firstChunk = chunk
                        } else {
                            assertSame(firstChunk, chunk)
                        }
                        repeat(chunk.limit) { sum += chunk.getByte(it).toUByte().toLong() }
                        expectedOffset += chunk.limit
                    }
                    call.respondText("$expectedOffset:$sum")
                }
            }
        }
        val bytes = patternedBytes(103)
        val source = NativeBuffer(bytes)
        val expectedSum = bytes.sumOf { it.toUByte().toLong() }

        val response = client.post("/sum") {
            setNativeBufferBody(source, chunkSize = 13)
        }

        assertEquals("103:$expectedSum", response.bodyAsText())
    }

    @Test
    fun `empty NativeBuffer is supported`() = testApplication {
        val empty = NativeBuffer(0, endian = Endian.BIG)
        application {
            routing {
                get("/empty") {
                    call.respondNativeBuffer(empty)
                }
            }
        }

        val received = client.get("/empty").bodyAsNativeBuffer()

        assertEquals(0, received.limit)
        assertEquals(Endian.BIG, received.endian)
    }

    @Test
    fun `client rejects response larger than configured maximum`() = testApplication {
        val source = NativeBuffer(patternedBytes(128))
        application {
            routing {
                get("/too-large") {
                    call.respondNativeBuffer(source)
                }
            }
        }

        assertFailsWith<IllegalArgumentException> {
            client.get("/too-large").bodyAsNativeBuffer(maxSize = 64)
        }
    }

    @Test
    fun `client rejects a non NativeBuffer content type`() = testApplication {
        application {
            routing {
                get("/json") {
                    call.respondText("{}", ContentType.Application.Json)
                }
            }
        }

        assertFailsWith<IllegalArgumentException> {
            client.get("/json").bodyAsNativeBuffer()
        }
    }

    private fun patternedBytes(size: Int): ByteArray = ByteArray(size) { index ->
        ((index * 31 + index / 7) and 0xff).toByte()
    }

    private fun NativeBuffer.toByteArray(): ByteArray =
        copyToByteArray(ByteArray(limit), 0, limit)
}
