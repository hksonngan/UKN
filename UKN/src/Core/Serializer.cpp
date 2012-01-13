//
//  Serializer.cpp
//  Project Unknown
//
//  Created by Robert Bu on 12/14/11.
//  Copyright (c) 2011 heizi. All rights reserved.
//

#include "UKN/Serializer.h"
#include "UKN/Stream.h"

namespace ukn {
    
    BinarySerializer::BinarySerializer(const StreamPtr& stream):
    mSerializeStream(stream) {
        if(!mSerializeStream) {
            mSerializeStream = new MemoryStream();
        }
    }
    
    
    // int32
    template<>
    void SerializeHelper::FromString<int32>(const ukn_string& str, int32* val) {
        ukn_assert(val);
        sscanf(str.c_str(), "%d", val);
    }
    
    template<>
    ukn_string SerializeHelper::ToString<int32>(int32* val) {
        return any_to_string(*val);
    }
    
    template<>
    int32 SerializeHelper::DefaultValue<int32>() {
        return 0;
    }
    
    // uint32
    template<>
    SerializableTypeId SerializeHelper::GetTypeId<int32>() {
        return STI_INT;
    }
    
    template<>
    void SerializeHelper::FromString<uint32>(const ukn_string& str, uint32* val) {
        ukn_assert(val);
        sscanf(str.c_str(), "%u", val);
    }
    
    template<>
    ukn_string SerializeHelper::ToString<uint32>(uint32* val) {
        return any_to_string(*val);
    }
    
    template<>
    uint32 SerializeHelper::DefaultValue<uint32>() {
        return 0;
    }
    
    template<>
    SerializableTypeId SerializeHelper::GetTypeId<uint32>() {
        return STI_UINT;
    }
    
    // float
    template<>
    void SerializeHelper::FromString<float>(const ukn_string& str, float* val) {
        ukn_assert(val);
        sscanf(str.c_str(), "%f", val);
    }
    
    template<>
    ukn_string SerializeHelper::ToString<float>(float* val) {
        return any_to_string(*val);
    }
    
    template<>
    float SerializeHelper::DefaultValue<float>() {
        return 0.f;
    }
    
    template<>
    SerializableTypeId SerializeHelper::GetTypeId<float>() {
        return STI_FLOAT;
    }
    
    // double
    template<>
    void SerializeHelper::FromString<double>(const ukn_string& str, double* val) {
        ukn_assert(val);
        sscanf(str.c_str(), "%lf", val);
    }
    
    template<>
    ukn_string SerializeHelper::ToString<double>(double* val) {
        return any_to_string(*val);
    }
    
    template<>
    double SerializeHelper::DefaultValue<double>() {
        return 0.0;
    }
    
    template<>
    SerializableTypeId SerializeHelper::GetTypeId<double>() {
        return STI_DOUBLE;
    }
    
    // char
    template<>
    void SerializeHelper::FromString<char>(const ukn_string& str, char* val) {
        ukn_assert(val);
        sscanf(str.c_str(), "%c", val);
    }
    
    template<>
    ukn_string SerializeHelper::ToString<char>(char* val) {
        return any_to_string(*val);
    }
    
    template<>
    char SerializeHelper::DefaultValue<char>() {
        return 0.0;
    }
    
    template<>
    SerializableTypeId SerializeHelper::GetTypeId<char>() {
        return STI_CHAR;
    }
    
    // long
    template<>
    void SerializeHelper::FromString<long>(const ukn_string& str, long* val) {
        ukn_assert(val);
        sscanf(str.c_str(), "%ld", val);
    }
    
    template<>
    ukn_string SerializeHelper::ToString<long>(long* val) {
        return any_to_string(*val);
    }
    
    template<>
    long SerializeHelper::DefaultValue<long>() {
        return 0;
    }
    
    template<>
    SerializableTypeId SerializeHelper::GetTypeId<long>() {
        return STI_ULONG;
    }
    
    // unsigned long
    template<>
    void SerializeHelper::FromString<unsigned long>(const ukn_string& str, unsigned long* val) {
        ukn_assert(val);
        sscanf(str.c_str(), "%lu", val);
    }
    
    template<>
    ukn_string SerializeHelper::ToString<unsigned long>(unsigned long* val) {
        return any_to_string(*val);
    }
    
    template<>
    unsigned long SerializeHelper::DefaultValue<unsigned long>() {
        return 0;
    }
    
    template<>
    SerializableTypeId SerializeHelper::GetTypeId<unsigned long>() {
        return STI_ULONG;
    }
    
    // int64
    template<>
    void SerializeHelper::FromString<int64>(const ukn_string& str, int64* val) {
        ukn_assert(val);
        sscanf(str.c_str(), "%lld", val);
    }
    
    template<>
    ukn_string SerializeHelper::ToString<int64>(int64* val) {
        return any_to_string(*val);
    }
    
    template<>
    int64 SerializeHelper::DefaultValue<int64>() {
        return 0;
    }
    
    template<>
    SerializableTypeId SerializeHelper::GetTypeId<int64>() {
        return STI_INT64;
    }
    
    // uint64
    template<>
    void SerializeHelper::FromString<uint64>(const ukn_string& str, uint64* val) {
        ukn_assert(val);
        sscanf(str.c_str(), "%llu", val);
    }
    
    template<>
    ukn_string SerializeHelper::ToString<uint64>(uint64* val) {
        return any_to_string(*val);
    }
    
    template<>
    uint64 SerializeHelper::DefaultValue<uint64>() {
        return 0;
    }
    
    template<>
    SerializableTypeId SerializeHelper::GetTypeId<uint64>() {
        return STI_INT64;
    }
    
    // string
    template<>
    void SerializeHelper::FromString<String>(const ukn_string& str, String* val) {
        ukn_assert(val);
        *val = string_to_wstring(str);
    }
    
    template<>
    ukn_string SerializeHelper::ToString<String>(String* val) {
        return wstring_to_string(*val);
    }
    
    template<>
    String SerializeHelper::DefaultValue<String>() {
        return String();
    }
    
    template<>
    SerializableTypeId SerializeHelper::GetTypeId<String>() {
        return STI_STRING;
    }
    
} // namespace ukn
