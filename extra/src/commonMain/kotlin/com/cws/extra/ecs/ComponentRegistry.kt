package com.cws.extra.ecs

import kotlin.math.roundToInt

/**
 * Global registry for component types and their storage factories.
 */
object ComponentRegistry {

    private const val TAG = "ComponentRegistry"
    private const val INITIAL_CAPACITY = 32

    private var componentKeys = arrayOfNulls<String>(INITIAL_CAPACITY)
    private var componentIds = IntArray(INITIAL_CAPACITY)
    private var entityCountPercentages = FloatArray(INITIAL_CAPACITY)
    @PublishedApi
    internal var componentStorageFactories = arrayOfNulls<(entityCount: Int) -> ComponentStorage>(INITIAL_CAPACITY)
    private var size = 0
    @PublishedApi
    internal var capacity = INITIAL_CAPACITY

    fun createComponentsState(
        entityCount: Int = EntityPool.DEFAULT_ENTITY_COUNT,
    ) = ComponentsState(
        entityCount = entityCount,
        keys = createKeys(),
        pools = createPools(entityCount),
        storages = createStorages(entityCount),
    )

    fun createKeys(): Array<String> = componentKeys.filterNotNull().toTypedArray()

    fun createPools(entityCount: Int): Array<ComponentPool?> {
        return Array(capacity) { i ->
            if (componentStorageFactories[i] != null) {
                ComponentPool(
                    entityCount = entityCount,
                    componentCount = (entityCount.toFloat() * entityCountPercentages[i]).roundToInt(),
                )
            } else {
                null
            }
        }
    }

    inline fun createStorages(
        entityCount: Int,
        update: (ComponentStorage?) -> Unit = {}
    ): Array<ComponentStorage?> {
        return Array(capacity) { i ->
            val storage = componentStorageFactories[i]?.invoke(entityCount)
            update(storage)
            storage
        }
    }

    inline fun createStorage(
        index: Int,
        entityCount: Int,
        update: (ComponentStorage?) -> Unit = {}
    ): ComponentStorage? {
        val storage = componentStorageFactories[index]?.invoke(entityCount)
        update(storage)
        return storage
    }

    fun register(
        componentKey: String,
        componentId: Int,
        entityCountPercentage: Float,
        componentStorageFactory: (entityCount: Int) -> ComponentStorage
    ) {
        if (size >= capacity * 0.75) {
            resize()
        }

        // linear probing for open addressing, since the component storages may collide on same index
        var index = componentId % capacity
        while (componentStorageFactories[index] != null) {
            if (componentIds[index] == componentId) {
                componentKeys[index] = componentKey
                componentStorageFactories[index] = componentStorageFactory
                entityCountPercentages[index] = entityCountPercentage
                return
            }
            index = (index + 1) % capacity
        }

        componentKeys[index] = componentKey
        componentIds[index] = componentId
        componentStorageFactories[index] = componentStorageFactory
        entityCountPercentages[index] = entityCountPercentage
        size++
    }

    inline fun <reified T> register(
        componentKey: String,
        entityCountPercentage: Float,
        noinline factory: (entityCount: Int) -> ComponentStorage
    ) {
        register(componentKey, ComponentId<T>(), entityCountPercentage, factory)
    }

    fun getRegistrationIndex(componentId: Int): Int {
        // linear probing for open addressing, since the component storages may collide on same index
        var index = componentId % capacity
        while (componentStorageFactories[index] != null) {
            if (componentIds[index] == componentId) {
                break
            }
            index = (index + 1) % capacity
        }
        return index
    }

    inline fun <reified T> getRegistrationIndex(): Int = getRegistrationIndex(ComponentId<T>())

    @PublishedApi
    internal fun isRegisteredIndex(index: Int): Boolean = index in componentStorageFactories.indices && componentStorageFactories[index] != null

    @PublishedApi
    internal fun getRegistrationIndexByKey(componentKey: String): Int {
        if (componentKey.isEmpty()) return RegistrationIndexNull
        componentKeys.forEachIndexed { i, key ->
            if (componentKey == key) return i
        }
        return RegistrationIndexNull
    }

    private fun resize() {
        val oldComponentKeys = componentKeys
        val oldComponentIds = componentIds
        val oldEntityCountPercentages = entityCountPercentages
        val oldStorageFactories = componentStorageFactories

        capacity *= 2
        componentKeys = arrayOfNulls(capacity)
        componentIds = IntArray(capacity)
        entityCountPercentages = FloatArray(capacity)
        componentStorageFactories = arrayOfNulls(capacity)
        size = 0

        for (i in 0 until oldStorageFactories.size) {
            val key = oldComponentKeys[i]
            val factory = oldStorageFactories[i]
            if (key != null && factory != null) {
                register(key, oldComponentIds[i], oldEntityCountPercentages[i], factory)
            }
        }
    }

}
