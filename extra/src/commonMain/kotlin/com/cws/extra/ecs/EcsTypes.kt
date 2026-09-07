package com.cws.extra.ecs

import com.cws.extra.math.operators.clamp

const val ComponentNull = -1
const val EntityNull = -1
const val RegistrationIndexNull = -1

inline fun <reified T> ComponentId() = T::class.hashCode() and 0x7FFFFFFF // subtract negative part to use it as index in array

inline fun validatePercentage(percentage: Float): Float = clamp(0f, 1f, percentage)
