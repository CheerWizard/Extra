#pragma once

#include <jni.h>
#include <cstdint>
#include <exception>

struct JniByteArrayScope {
    JNIEnv* env;
    jbyteArray array;
    jbyte* elements;

    JniByteArrayScope(JNIEnv* e, jbyteArray arr) : env(e), array(arr) {
        jboolean isCopy = JNI_FALSE;
        elements = env->GetByteArrayElements(array, &isCopy);
    }

    ~JniByteArrayScope() {
        if (elements != nullptr) {
            env->ReleaseByteArrayElements(array, elements, JNI_ABORT);
        }
    }
};

template<typename T>
T JniDecode(JNIEnv* env, jobject byteBuffer, jbyteArray byteArray) {
    if (byteBuffer) {
        void* ptr = env->GetDirectBufferAddress(byteBuffer);
        if (ptr) {
            uint8_t* bytes = static_cast<uint8_t*>(ptr);
            try {
                return T::Decode(bytes);
            } catch (const std::exception& e) {
                jclass exceptionClass = env->FindClass("java/lang/RuntimeException");
                if (exceptionClass) env->ThrowNew(exceptionClass, e.what());
            }
        }
        else {
            jclass exceptionClass = env->FindClass("java/lang/IllegalArgumentException");
            if (exceptionClass) env->ThrowNew(exceptionClass, "ByteBuffer must be direct!");
        }
    }

    else if (byteArray) {
        JniByteArrayScope scope(env, byteArray);
        if (scope.elements) {
            uint8_t* bytes = reinterpret_cast<uint8_t*>(scope.elements);
            try {
                return T::Decode(bytes);
            } catch (const std::exception& e) {
                jclass exClass = env->FindClass("java/lang/RuntimeException");
                if (exClass) env->ThrowNew(exClass, e.what());
            }
        } else {
            jclass exceptionClass = env->FindClass("java/lang/IllegalArgumentException");
            if (exceptionClass) env->ThrowNew(exceptionClass, "ByteArray elements could not be accessed!");
        }
    }

    else {
        jclass exceptionClass = env->FindClass("java/lang/IllegalArgumentException");
        if (exceptionClass) env->ThrowNew(exceptionClass, "Either ByteBuffer or ByteArray must be not null!");
    }

    return {};
}