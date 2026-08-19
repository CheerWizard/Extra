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
package com.cws.extra.ecs

import com.cws.extra.test.COMPONENT_ID
import com.cws.extra.test.Camera
import com.cws.extra.test.Movement
import com.cws.extra.test.cameras
import com.cws.extra.test.movements
import kotlin.test.BeforeTest
import kotlin.test.Test
import kotlin.test.assertEquals
import kotlin.test.assertFalse
import kotlin.test.assertNotNull
import kotlin.test.assertTrue

class ComponentStorageTest {

    private lateinit var scene: Scene

    @BeforeTest
    fun setup() {
        // Safe bounded allocation context
        scene = Scene(capacity = 32)
    }

    @Test
    fun `test generated scene extension properties resolve to correct primitive lists`() {
        val entity = scene.createEntity()

        // Add through the standard generic scene API
        scene.add(entity, Movement(speed = 45.0f))
        scene.add(entity, Camera(fov = 90.0f))

        // 1. Verify that the sugar extensions can read data directly from the scene context
        val movementList = scene.movements
        val cameraList = scene.cameras

        assertNotNull(movementList)
        assertNotNull(cameraList)
        assertEquals(1, movementList.size)
        assertEquals(1, cameraList.size)

        // 2. Look up the index via storage to verify data values match up perfectly
        val movementStorage = scene.registry[Movement.COMPONENT_ID]
        val moveIdx = movementStorage.index(entity)

        assertEquals(45.0f, movementList.speed[moveIdx])
    }

    @Test
    fun `test storage add method type safety guards against invalid casts`() {
        val entity = scene.createEntity()
        val movementStorage = scene.registry[Movement.COMPONENT_ID]

        // Crucial test: Pass an illegal component type (Camera) into MovementStorage
        // The generated 'val c = component as? Movement ?: return' block should catch this safely
        movementStorage.add(entity, Camera(fov = 60.0f))

        // Verify that the operation was cleanly ignored and no components were registered
        assertFalse(movementStorage.has(entity))
        assertEquals(0, scene.movements.size)
    }

    @Test
    fun `test component addition overwrites existing values instead of appending duplicates`() {
        val entity = scene.createEntity()

        // 1. Initial assignment
        scene.add(entity, Movement(speed = 10.0f))
        val initialMoveIdx = scene.registry[Movement.COMPONENT_ID].index(entity)
        assertEquals(1, scene.movements.size)
        assertEquals(10.0f, scene.movements.speed[initialMoveIdx])

        // 2. Re-assign/Update the component for the exact same entity
        // This should trigger the generated 'else { list[componentIndex] = c }' block
        scene.add(entity, Movement(speed = 25.0f))
        val updatedMoveIdx = scene.registry[Movement.COMPONENT_ID].index(entity)

        // 3. Structural validation
        assertEquals(1, scene.movements.size, "List size must NOT grow when updating an existing component")
        assertEquals(initialMoveIdx, updatedMoveIdx, "The entity's data slot index must remain identical")
        assertEquals(25.0f, scene.movements.speed[updatedMoveIdx], "The primitive value inside the list must update cleanly")
    }

    @Test
    fun `test cross storage removal safety does not corrupt neighboring lists`() {
        val entity = scene.createEntity()

        scene.add(entity, Movement(12.0f))
        scene.add(entity, Camera(45.0f))

        // Target only the movement storage for deletion
        val movementStorage = scene.registry[Movement.COMPONENT_ID]
        val cameraStorage = scene.registry[Camera.COMPONENT_ID]

        movementStorage.remove(entity)

        // Verify isolation boundaries
        assertFalse(movementStorage.has(entity))
        assertEquals(0, scene.movements.size)

        // Camera components must remain completely unbothered
        assertTrue(cameraStorage.has(entity))
        assertEquals(1, scene.cameras.size)
    }
}