///*
// * Copyright 2026 CheerWizard
// *
// * Licensed under the Apache License, Version 2.0 (the "License");
// * you may not use this file except in compliance with the License.
// */
//package com.cws.extra.benchmarks
//
//import com.cws.extra.ecs.Scene
//import com.github.quillraven.fleks.Component
//import com.github.quillraven.fleks.ComponentType
//import com.github.quillraven.fleks.World
//import com.github.quillraven.fleks.configureWorld
//import org.openjdk.jmh.annotations.Benchmark
//import org.openjdk.jmh.annotations.BenchmarkMode
//import org.openjdk.jmh.annotations.Level
//import org.openjdk.jmh.annotations.Measurement
//import org.openjdk.jmh.annotations.Mode
//import org.openjdk.jmh.annotations.OutputTimeUnit
//import org.openjdk.jmh.annotations.Param
//import org.openjdk.jmh.annotations.Scope
//import org.openjdk.jmh.annotations.Setup
//import org.openjdk.jmh.annotations.State
//import org.openjdk.jmh.annotations.TearDown
//import org.openjdk.jmh.annotations.Warmup
//import org.openjdk.jmh.infra.Blackhole
//import java.util.concurrent.TimeUnit
//
//data class FleksMovement(val speed: Float) : Component<FleksMovement> {
//    companion object : ComponentType<FleksMovement>()
//    override fun type(): ComponentType<FleksMovement> = FleksMovement
//}
//
//data class FleksCamera(val fov: Float) : Component<FleksCamera> {
//    companion object : ComponentType<FleksCamera>()
//    override fun type(): ComponentType<FleksCamera> = FleksCamera
//}
//
//@State(Scope.Thread)
//open class ExtraState {
//    @Param("10000", "100000")
//    var entityCount: Int = 0
//
//    @Param(
//        "sceneCreation", "createEntities", "movementAllocation", "createWithMovement",
//        "addMovement", "addCamera", "removeMovement", "removeCamera", "removeEntities",
//        "createRemove", "mixed",
//    )
//    lateinit var operation: String
//
//    lateinit var scene: Scene
//
//    @Setup(Level.Trial)
//    fun registerComponents() = ExtraComponents.registerAll()
//
//    @Setup(Level.Invocation)
//    fun setupInvocation() {
//        if (operation == "sceneCreation" || operation == "movementAllocation" ||
//            operation == "createRemove" || operation == "mixed") return
//
//        scene = Scene(entityCount)
//        when (operation) {
//            "addMovement", "addCamera" -> repeat(entityCount) { scene.createEntity() }
//            "removeMovement", "removeEntities" -> repeat(entityCount) { scene.create(Movement(1f)) }
//            "removeCamera" -> repeat(entityCount) { scene.create(Camera(1f)) }
//        }
//    }
//}
//
//@State(Scope.Thread)
//open class FleksState {
//    @Param("10000", "100000")
//    var entityCount: Int = 0
//
//    @Param(
//        "sceneCreation", "createEntities", "movementAllocation", "createWithMovement",
//        "addMovement", "addCamera", "removeMovement", "removeCamera", "removeEntities",
//        "createRemove", "mixed",
//    )
//    lateinit var operation: String
//
//    lateinit var world: World
//
//    @Setup(Level.Invocation)
//    fun setupInvocation() {
//        if (operation == "sceneCreation" || operation == "movementAllocation" ||
//            operation == "createRemove" || operation == "mixed") return
//
//        world = configureWorld(entityCapacity = entityCount) {}
//        when (operation) {
//            "addMovement", "addCamera" -> repeat(entityCount) { world.entity() }
//            "removeMovement", "removeEntities" -> repeat(entityCount) {
//                world.entity { entity -> entity += FleksMovement(1f) }
//            }
//            "removeCamera" -> repeat(entityCount) {
//                world.entity { entity -> entity += FleksCamera(1f) }
//            }
//        }
//    }
//
//    @TearDown(Level.Invocation)
//    fun tearDownInvocation() {
//        if (::world.isInitialized) world.dispose()
//    }
//}
//
//@BenchmarkMode(Mode.AverageTime)
//@OutputTimeUnit(TimeUnit.NANOSECONDS)
//@Warmup(iterations = 5, time = 1)
//@Measurement(iterations = 10, time = 1)
//open class EcsComparisonBenchmark {
//
//    @Benchmark
//    fun extra(state: ExtraState, blackhole: Blackhole) {
//        val count = state.entityCount
//        when (state.operation) {
//            "sceneCreation" -> blackhole.consume(Scene(count))
//            "createEntities" -> repeat(count) { state.scene.createEntity() }
//            "movementAllocation" -> repeat(count) { blackhole.consume(ExtraMovement(1f)) }
//            "createWithMovement" -> repeat(count) { state.scene.create(ExtraMovement(1f)) }
//            "addMovement" -> repeat(count) { state.scene.add(it, ExtraMovement(1f)) }
//            "addCamera" -> repeat(count) { state.scene.add(it, ExtraCamera(1f)) }
//            "removeMovement" -> repeat(count) { state.scene.remove<ExtraMovement>(it) }
//            "removeCamera" -> repeat(count) { state.scene.remove<ExtraCamera>(it) }
//            "removeEntities" -> repeat(count) { state.scene.removeEntity(it) }
//            "createRemove" -> extraCreateRemove(count, blackhole)
//            "mixed" -> extraMixed(count, blackhole)
//            else -> error("Unknown operation ${state.operation}")
//        }
//    }
//
//    @Benchmark
//    fun fleks(state: FleksState, blackhole: Blackhole) {
//        val count = state.entityCount
//        when (state.operation) {
//            "sceneCreation" -> blackhole.consume(configureWorld(entityCapacity = count) {})
//            "createEntities" -> repeat(count) { state.world.entity() }
//            "movementAllocation" -> repeat(count) { blackhole.consume(FleksMovement(1f)) }
//            "createWithMovement" -> repeat(count) {
//                state.world.entity { entity -> entity += FleksMovement(1f) }
//            }
//            "addMovement" -> state.world.forEach { entity -> entity.configure { entity += FleksMovement(1f) } }
//            "addCamera" -> state.world.forEach { entity -> entity.configure { entity += FleksCamera(1f) } }
//            "removeMovement" -> state.world.family { all(FleksMovement) }.forEach { entity ->
//                entity.configure { entity -= FleksMovement }
//            }
//            "removeCamera" -> state.world.family { all(FleksCamera) }.forEach { entity ->
//                entity.configure { entity -= FleksCamera }
//            }
//            "removeEntities" -> state.world.forEach { state.world -= it }
//            "createRemove" -> fleksCreateRemove(count, blackhole)
//            "mixed" -> fleksMixed(count, blackhole)
//            else -> error("Unknown operation ${state.operation}")
//        }
//    }
//
//    private fun extraCreateRemove(count: Int, blackhole: Blackhole) {
//        val scene = Scene(count)
//        repeat(count) { scene.createEntity() }
//        repeat(count) { scene.removeEntity(it) }
//        blackhole.consume(scene)
//    }
//
//    private fun extraMixed(count: Int, blackhole: Blackhole) {
//        val scene = Scene(count)
//        repeat(count) { scene.createEntity() }
//        repeat(count) { entity ->
//            scene.add(entity, ExtraMovement(1f))
//            if (entity and 1 == 0) scene.add(entity, ExtraCamera(1f))
//        }
//        scene.query<ExtraMovement, ExtraMovementList>().forEach { _, movements, index ->
//            blackhole.consume(movements.speed[index])
//        }
//        scene.query<ExtraMovement, ExtraMovementList, ExtraCamera, ExtraCameraList>().forEach {
//                _, movements, movementIndex, cameras, cameraIndex ->
//            blackhole.consume(movements.speed[movementIndex])
//            blackhole.consume(cameras.fov[cameraIndex])
//        }
//        repeat(count) { entity ->
//            scene.remove<ExtraMovement>(entity)
//            if (entity and 1 == 0) scene.remove<ExtraCamera>(entity)
//        }
//        repeat(count) { scene.removeEntity(it) }
//        blackhole.consume(scene)
//    }
//
//    private fun fleksCreateRemove(count: Int, blackhole: Blackhole) {
//        val world = configureWorld(entityCapacity = count) {}
//        repeat(count) { world.entity() }
//        world.forEach { world -= it }
//        blackhole.consume(world)
//        world.dispose()
//    }
//
//    private fun fleksMixed(count: Int, blackhole: Blackhole) {
//        val world = configureWorld(entityCapacity = count) {}
//        repeat(count) {
//            world.entity { entity ->
//                entity += FleksMovement(1f)
//                if (entity.id and 1 == 0) entity += FleksCamera(1f)
//            }
//        }
//        val movement = world.family { all(FleksMovement) }
//        movement.forEach { blackhole.consume(it[FleksMovement].speed) }
//        world.family { all(FleksMovement, FleksCamera) }.forEach {
//            blackhole.consume(it[FleksMovement].speed)
//            blackhole.consume(it[FleksCamera].fov)
//        }
//        movement.forEach { entity ->
//            entity.configure {
//                entity -= FleksMovement
//                if (entity.id and 1 == 0) entity -= FleksCamera
//            }
//        }
//        world.forEach { world -= it }
//        blackhole.consume(world)
//        world.dispose()
//    }
//}
