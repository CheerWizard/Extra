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
#pragma once

#include <cstddef>
#include <cstdint>
#include <cstring>
#include <string>
#include <array>
#include <vector>
#include <unordered_map>

#define EXTRA_STRUCT struct __attribute__((packed))

template<typename T>
inline T ExtraNextPrimitive(const uint8_t*& p) {
    T value;
    std::memcpy(&value, p, sizeof(T));
    p += sizeof(T);
    return value;
}

template<typename T>
inline void ExtraPushPrimitive(const T& value, uint8_t*& p) {
    std::memcpy(p, &value, sizeof(T));
    p += sizeof(T);
}

struct ExtraString {
    int32_t length = 0;
    const char* data = nullptr;
};

inline ExtraString ExtraNextString(const uint8_t*& p) {
    ExtraString s;
    s.length = ExtraNextPrimitive<int32_t>(p);
    s.data = reinterpret_cast<const char*>(p);
    p += s.length;
    return s;
}

inline void ExtraPushString(const ExtraString& s, uint8_t*& p) {
    ExtraPushPrimitive<int32_t>(s.length, p);
    std::memcpy(p, s.data, s.length);
    p += s.length;
}

struct ExtraString16 {
    int32_t length = 0;
    const uint16_t* data = nullptr;
};

inline ExtraString16 ExtraNextString16(const uint8_t*& p) {
    ExtraString16 s;
    s.length = ExtraNextPrimitive<int32_t>(p);
    s.data = reinterpret_cast<const uint16_t*>(p);
    p += s.length * sizeof(uint16_t);
    return s;
}

inline void ExtraPushString16(const ExtraString16& s, uint8_t*& p) {
    ExtraPushPrimitive<int32_t>(s.length, p);
    std::memcpy(p, s.data, s.length * sizeof(uint16_t));
    p += s.length * sizeof(uint16_t);
}

template<typename T>
struct ExtraArray {
    int32_t length;
    const T* data;
};

using ExtraByteArray   = ExtraArray<uint8_t>;
using ExtraShortArray  = ExtraArray<int16_t>;
using ExtraChar16Array = ExtraArray<uint16_t>;
using ExtraIntArray    = ExtraArray<int32_t>;
using ExtraLongArray   = ExtraArray<int64_t>;
using ExtraFloatArray  = ExtraArray<float>;
using ExtraDoubleArray = ExtraArray<double>;

template<typename T>
inline ExtraArray<T> ExtraNextArray(const uint8_t*& p) {
    ExtraArray<T> a;
    a.length = ExtraNextPrimitive<int32_t>(p);
    a.data   = reinterpret_cast<const T*>(p);
    p += sizeof(T) * a.length;
    return a;
}

template<typename T>
inline void ExtraPushArray(const ExtraArray<T>& a, uint8_t*& p) {
    ExtraPushPrimitive<int32_t>(a.length, p);
    std::memcpy(p, a.data, sizeof(T) * a.length);
    p += sizeof(T) * a.length;
}

template<typename T>
struct ExtraList {
    int32_t count;
    const uint8_t* data;
};

template<typename T, typename NextFn>
inline ExtraList<T> ExtraNextList(const uint8_t*& p, NextFn next) {
    ExtraList<T> list;
    list.count = ExtraNextPrimitive<int32_t>(p);
    list.data  = p;
    for (int32_t i = 0; i < list.count; i++) next(p);
    return list;
}

template<typename T, typename PushFn>
inline void ExtraPushList(const ExtraList<T>& list, uint8_t*& p, PushFn push) {
    ExtraPushPrimitive<int32_t>(list.count, p);
    const uint8_t* r = list.data;
    for (int32_t i = 0; i < list.count; i++) push(r, p);
}

template<typename K, typename V>
struct ExtraMap {
    int32_t count;
    const uint8_t* data;
};

template<typename K, typename V, typename NextKeyFn, typename NextValueFn>
inline ExtraMap<K, V> ExtraNextMap(const uint8_t*& p, NextKeyFn nextKey, NextValueFn nextValue) {
    ExtraMap<K, V> map;
    map.count = ExtraNextPrimitive<int32_t>(p);
    map.data  = p;
    for (int32_t i = 0; i < map.count; i++) { nextKey(p); nextValue(p); }
    return map;
}

template<typename K, typename V, typename PushKeyFn, typename PushValueFn>
inline void ExtraPushMap(const ExtraMap<K, V>& map, uint8_t*& p, PushKeyFn pushKey, PushValueFn pushValue) {
    ExtraPushPrimitive<int32_t>(map.count, p);
    const uint8_t* r = map.data;
    for (int32_t i = 0; i < map.count; i++) { pushKey(r, p); pushValue(r, p); }
}