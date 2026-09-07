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
package com.cws.extra.memory

// use this annotation to generate C/C++ bridge for current interface
// all function under this annotated class will get generated version on C++ side
@Target(AnnotationTarget.CLASS)
@Retention(AnnotationRetention.SOURCE)
annotation class ExtraBridge(
    val libName: String,
    val transport: Transport = Transport.ALL
) {

    enum class Transport {
        // generate only JNI transport layer
        JNI,
        // generate only C-interop transport layer
        CINTEROP,
        // generate ALL transport layers
        ALL;
    }

}

// use this annotation to generate encodings for annotated class and use it for bridge
@Target(AnnotationTarget.CLASS)
@Retention(AnnotationRetention.SOURCE)
annotation class ExtraBridgeData

// use this annotation to generate encodings for annotated SoA class and use it for bridge
@Target(AnnotationTarget.CLASS)
@Retention(AnnotationRetention.SOURCE)
annotation class ExtraBridgeDataSoA

// use this annotation to generate encodings for annotated enum and use it for bridge
@Target(AnnotationTarget.CLASS)
@Retention(AnnotationRetention.SOURCE)
annotation class ExtraBridgeEnum

// use this annotation to generate encodings for annotated class
@Target(AnnotationTarget.CLASS)
@Retention(AnnotationRetention.SOURCE)
annotation class ExtraData

// use this annotation to generate encodings for annotated SoA class
@Target(AnnotationTarget.CLASS)
@Retention(AnnotationRetention.SOURCE)
annotation class ExtraDataSoA

// use this annotation to generate encodings for annotated enum
@Target(AnnotationTarget.CLASS)
@Retention(AnnotationRetention.SOURCE)
annotation class ExtraEnum

// use this annotation for fixed size data types, like static arrays or static string
@Target(AnnotationTarget.FIELD)
@Retention(AnnotationRetention.SOURCE)
annotation class ExtraFixedSize(
    val size: Int,
)

// use this annotation to say generator to output String as UTF-16 encoded type
@Target(AnnotationTarget.FIELD)
@Retention(AnnotationRetention.SOURCE)
annotation class ExtraStringUtf16

// use this annotation to generate SoA implementation with collections-like methods for target class
@Target(AnnotationTarget.CLASS)
@Retention(AnnotationRetention.SOURCE)
annotation class ExtraList

// use this annotation to generate components storage for annotated class used in ECS
@Target(AnnotationTarget.CLASS)
@Retention(AnnotationRetention.SOURCE)
annotation class ExtraComponent(
    // range in [0f, 1f]
    // default = 0.2f (20%)
    // describes what % of entity capacity this component will initially occupy
    // useful for optimizing preallocation of components by types
    // Example:
    // Transform - usually is 0.9f-1f (90%-100%), used almost on every entity
    // SoundSource - can be 0.2f-0.3f (20%-30%), not used frequently in scene
    // Animation - can be 0.1f-0.15f (10%-15%), used rarely, mostly for characters or enemies
    val entityCountPercentage: Float = 0.2f
)