/*
 * file_name: JsonParse.h
 * file_detail:json parse helper
 * created by silver0511
 */
#ifndef __RX_JSONPARSER_H__
#define __RX_JSONPARSER_H__

#include <string>
#include <cstdio>
#include <type_traits>
#include <iostream>
#include "rapidjson/document.h"
#include "rapidjson/reader.h"
#include "rapidjson/stringbuffer.h"
#include "rapidjson/writer.h"
#include "rapidjson/filereadstream.h"
#include "rapidjson/error/en.h"
#include "stdafx.h"

RELAX_NAMESPACE_BEGIN

typedef rapidjson::Value RJsonValue;
typedef rapidjson::Document RJDocument;
typedef rapidjson::Document::AllocatorType RJAllocType;
typedef rapidjson::SizeType RJ_SIZE_TYPE;
typedef rapidjson::Value::ConstValueIterator RJConstIterator;
typedef rapidjson::Value::ConstMemberIterator RJConstMemberIterator;
typedef rapidjson::Value::Object    RJObject;
typedef rapidjson::Value::Array     RJArray;

/**
 * 创建一个空的根(对象)
 * 用于用户从字符串解码
 */
#define RJ_CREATE_EMPTY_DOCUMENT(ROOT_NAME) \
    RJDocument ROOT_NAME; \

/**
 * 创建根(对象)
 */
#define RJ_CREATE_O_DOCUMENT(ROOT_NAME, ALLOC_NAME) \
    RJDocument ROOT_NAME(rapidjson::kObjectType); \
    RJAllocType& ALLOC_NAME = ROOT_NAME.GetAllocator(); \

/**
 * 创建根(数组)
 */
#define RJ_CREATE_A_DOCUMENT(ROOT_NAME, ALLOC_NAME) \
    RJDocument ROOT_NAME(rapidjson::kArrayType); \
    RJAllocType& ALLOC_NAME = ROOT_NAME.GetAllocator(); \

/**
 * 创建子(对象)
 */
#define RJ_CREATE_OBJECT(VALUE_NAME) \
    RJsonValue VALUE_NAME(rapidjson::kObjectType); \

/**
 * 创建子(数组)
 */
#define RJ_CREATE_ARRAY(VALUE_NAME) \
    RJsonValue VALUE_NAME(rapidjson::kArrayType); \

class JsonParse
{
public:
    JsonParse(){};
    ~JsonParse(){};

    /**
     * 添加节点信息, json_value[key] = value
     * 支持 K_ID类型:[int, unsigned, bool, double, int64_t, uint64_t, int8_t, uint8_t, int16_t, uint16_t]
     * @param json_value 需要加入的JSON节点
     * @param key 添加的KEY字符串
     * @param value 添加的value
     * @param allocator_type 分配器[GetAllocator()]
     * @return 添加成功或者失败[true or false]
     */
    template<typename K_ID>
    static bool add(RJsonValue &json_value, const char* key, const K_ID &value, RJAllocType& allocator_type)
    {
        if(!json_value.IsObject())
        {
            return false;
        }

        if(has(json_value, key))
        {
            json_value.RemoveMember(key);
        }

        json_value.AddMember<K_ID>(RJsonValue(key, allocator_type).Move(),
                                   value, allocator_type);
        return true;
    }

    /**
     * 添加节点字符串信息, json_value[key] = value
     * @param json_value 需要加入的JSON节点
     * @param key 添加的KEY字符串
     * @param value 添加的value字符串
     * @param allocator_type 分配器[GetAllocator()]
     * @return 添加成功或者失败[true or false]
     */
    static bool add(RJsonValue &json_value, const char* key, const std::string &value, RJAllocType& allocator_type)
    {
        if(!json_value.IsObject())
        {
            return false;
        }

        if(has(json_value, key))
        {
            json_value.RemoveMember(key);
        }

        rapidjson::Value l_name(rapidjson::kStringType);
        l_name.SetString(key, allocator_type);
        rapidjson::Value l_value(rapidjson::kStringType);
        l_value.SetString(value.c_str(), (int)value.size(), allocator_type);
        json_value.AddMember(l_name, l_value, allocator_type);
        return true;
    }

    /**
     * 添加子节点信息, json_value[key] = value
     * @param json_value 需要加入的JSON节点
     * @param key 添加的KEY字符串
     * @param value 添加的RJsonValue类型value
     * @param allocator_type 分配器[GetAllocator()]
     * @return 添加成功或者失败[true or false]
     */
    static bool add(RJsonValue &json_value, const char* key, RJsonValue &value, RJAllocType& allocator_type)
    {
        if (!json_value.IsObject())
        {
            return false;
        }

        if (has(json_value, key))
        {
            json_value.RemoveMember(key);
        }

        json_value.AddMember(RJsonValue(key, allocator_type).Move(), value, allocator_type);
        return true;
    }

    /**
     * 获取子节点信息
     * 支持 K_ID类型:[int, unsigned, bool, double, int64_t, uint64_t, int8_t, uint8_t, int16_t, uint16_t]
     * @param json_value 需要获取的JSON根节点
     * @param key KEY字符串
     * @return K_ID 默认返回0
     */
    template<typename K_ID>
    static K_ID get(RJsonValue &json_value, const char* key)
    {
        if(!json_value.IsObject())
        {
            return 0;
        }

        auto l_iter = json_value.FindMember(key);
        if(l_iter == json_value.MemberEnd())
        {
            return 0;
        }

        K_ID l_out_value;
        if(!get_value<K_ID>(l_iter->value, l_out_value))
        {
            return 0;
        }
        return l_out_value;
    }

    /**
     * 获取子节点信息[字符串]
     * @param json_value 需要获取的JSON根节点
     * @param key KEY字符串
     * @param out_value 返回的字符串引用
     * @return 是否存在[true or false]
     */
    static bool get(RJsonValue &json_value, const char* key, OUT std::string &out_value)
    {
        if(!json_value.IsObject())
        {
            return false;
        }

        auto l_iter = json_value.FindMember(key);
        if(l_iter == json_value.MemberEnd())
        {
            return false;
        }

        if(!l_iter->value.IsString())
        {
            return false;
        }

        out_value = l_iter->value.GetString();
        return true;
    }

    /**
     * 获取子节点信息[RJsonValue]
     * 注意:外部必须通过引用去接，否则会swap原本的dom结构
     * 例子:RJsonValue &p = get(...);
     * @param json_value 需要获取的JSON根节点
     * @param key KEY字符串
     * @return RJsonValue类型子节点
     */
    static RJsonValue& get(RJsonValue &json_value, const char* key)
    {
        if(!json_value.IsObject())
        {
            return get_null();
        }

        auto l_iter = json_value.FindMember(key);
        if(l_iter == json_value.MemberEnd())
        {
            return get_null();
        }
        return l_iter->value;
    }


    /**
     * 移除某一个节点
     * @param json_value 需要获取的JSON根节点
     * @param key KEY字符串
     * @return 是否移除成功[true or false]
     */
    static bool remove(RJsonValue &json_value, const char* key)
    {
        if(!json_value.IsObject())
        {
            return false;
        }

        return json_value.EraseMember(key);
    }

    /**
     * 添加节点信息, json_value[index] = value
     * 支持 K_ID类型:[int, unsigned, bool, double, int64_t, uint64_t, int8_t, uint8_t, int16_t, uint16_t]
     * @param json_value 需要加入的JSON节点[数组类型:json_value.IsArray()]
     * @param value 添加的value
     * @param allocator_type 分配器[GetAllocator()]
     * @return 添加成功或者失败[true or false]
     */
    template<typename K_ID>
    static bool push(RJsonValue &json_value, const K_ID &value, RJAllocType& allocator_type)
    {
        if(!json_value.IsArray())
        {
            return false;
        }

        json_value.PushBack<K_ID>(value, allocator_type);

        return true;
    }

    /**
     * 添加节点字符串信息, json_value[index] = value
     * @param json_value 需要加入的JSON节点[数组类型:json_value.IsArray()]
     * @param value 添加的value
     * @param allocator_type 分配器[GetAllocator()]
     * @return 添加成功或者失败[true or false]
     */
    static bool push(RJsonValue &json_value, const std::string &value, RJAllocType& allocator_type)
    {
        if(!json_value.IsArray())
        {
            return false;
        }

        rapidjson::Value l_value(rapidjson::kStringType);
        l_value.SetString(value.c_str(), value.size(), allocator_type);
        json_value.PushBack(l_value, allocator_type);

        return true;
    }

    /**
     * 添加节点信息, json_value[index] = value
     * @param json_value 需要加入的JSON节点[数组类型:json_value.IsArray()]
     * @param value 添加的value[RJsonValue类型]
     * @param allocator_type 分配器[GetAllocator()]
     * @return 添加成功或者失败[true or false]
     */
    static bool push(RJsonValue &json_value, RJsonValue &value, RJAllocType& allocator_type)
    {
        if(!json_value.IsArray())
        {
            return false;
        }

        json_value.PushBack(value, allocator_type);
        return true;
    }

    /**
     * 获取当前节点的大小
     * @param json_value 需要获取的JSON节点[数组类型:json_value.IsArray()]
     * @return 数组大小，不存在返回-1
     */
    static RJ_SIZE_TYPE count(RJsonValue &json_value)
    {
        if(!json_value.IsArray())
        {
            return -1;
        }

        return json_value.Size();
    }

    /**
     * 从JSON数组中获取子节点信息
     * 支持 K_ID类型:[int, unsigned, bool, double, int64_t, uint64_t, int8_t, uint8_t, int16_t, uint16_t]
     * @param json_value 需要获取的JSON根节点[数组类型:json_value.IsArray()]
     * @param index 数组索引地址
     * @return K_ID 默认返回0
     */
    template<typename K_ID>
    static K_ID at(RJsonValue &json_value, int index)
    {
        if(!json_value.IsArray())
        {
            return 0;
        }

        if(index < 0 || index >= json_value.Size())
        {
            return 0;
        }
        K_ID l_out_value;
        if(!get_value<K_ID>(json_value[index], l_out_value))
        {
            return 0;
        }
        return l_out_value;
    }

    /**
     * 从JSON数组中获取子节点字符串信息
     * @param json_value 需要获取的JSON根节点[数组类型:json_value.IsArray()]
     * @param index 数组索引地址
     * @param out_value 返回的字符串引用
     * @return 是否存在[true or false]
     */
    static bool at(RJsonValue &json_value, int index, OUT std::string &out_value)
    {
        if(!json_value.IsArray())
        {
            return false;
        }

        if(index < 0 || index >= json_value.Size())
        {
            return false;
        }

        if(!json_value[index].IsString())
        {
            return false;
        }

        out_value = json_value[index].GetString();
        return true;
    }

    /**
     * 获取子节点信息[RJsonValue]
     * 注意:外部必须通过引用去接，否则会swap原本的dom结构
     * 例子:RJsonValue &p = at(...);
     * @param json_value 需要获取的JSON根节点[数组类型:json_value.IsArray()]
     * @param index 数组索引地址
     * @return RJsonValue类型子节点
     */
    static RJsonValue& at(RJsonValue &json_value, int index)
    {
        if(!json_value.IsArray())
        {
            return get_null();
        }

        if(index < 0 || index >= json_value.Size())
        {
            return get_null();
        }

        return json_value[index];
    }

    /**
     * 删除子节点[RJsonValue]
     * @param json_value 需要获取的JSON根节点[数组类型:json_value.IsArray()]
     * @param index 数组索引地址
     * @return 是否删除成功[true or false]
     */
    static bool erase(RJsonValue &json_value, int index)
    {
        if(!json_value.IsArray())
        {
            return false;
        }

        if(index < 0 || index >= json_value.Size())
        {
            return false;
        }

        RJsonValue::ConstValueIterator l_beg = json_value.Begin();
//        RJsonValue::ConstValueIterator l_end = json_value.End();
        json_value.Erase(l_beg + index);

        return true;
    }

    /**
     * 解析成JSON对象
     * @param json_document 通过RJ_CREATE_EMPTY_DOCUMENT宏创建的空对象,返回给外部使用
     * @param data 需要解析的json字符串
     * @return 是否解析成功[true or false]
     */
    static bool parse(OUT RJDocument &json_document, const char* data)
    {
        if(NULL == data)
        {
            return false;
        }

        json_document.Parse<0>(data);
        bool l_has_error = json_document.HasParseError();
        if(l_has_error)
        {
            fprintf(stderr, "\nparse Error(offset %u): %s\n",
                    (unsigned)json_document.GetErrorOffset(),
                    rapidjson::GetParseError_En(json_document.GetParseError()));
        }

        if(json_document.IsNull())
        {
            l_has_error = true;
        }

        return !l_has_error;
    }

    /**
     * 解析成JSON对象
     * @param json_document 通过RJ_CREATE_EMPTY_DOCUMENT宏创建的空对象,返回给外部使用
     * @param file_name 需要解析的json字符串对应的文件地址
     * @return 是否解析成功[true or false]
     */
    static bool parse_file(OUT RJDocument &json_document, const char* file_name)
    {
        if(NULL == file_name)
        {
            return false;
        }

        FILE* l_fp = fopen(file_name, "rb");
        if(!l_fp)
        {
            return false;
        }

        fseek(l_fp, 0, SEEK_END);
        int l_buf_len = ftell(l_fp);
        fseek(l_fp, 0, SEEK_SET);

        printf("file_name = %s, read size = %d \n", file_name, l_buf_len);

        char *l_buf = (char*)malloc(sizeof(char) * l_buf_len);
        rapidjson::FileReadStream l_is(l_fp, l_buf, l_buf_len);
        json_document.ParseStream(l_is);
        fclose(l_fp);
        free(l_buf);

        bool l_has_error = json_document.HasParseError();
        if(l_has_error)
        {
            fprintf(stderr, "\nparse_file Error(offset %u): %s\n",
                    (unsigned)json_document.GetErrorOffset(),
                    rapidjson::GetParseError_En(json_document.GetParseError()));
        }

        if(json_document.IsNull())
        {
            l_has_error = true;
        }

        return !l_has_error;
    }

    /**
     * 把JSON对象转换成字符串
     * @param json_value 需要转换的json对象
     * @param out_value 转换之后的输出字符串
     * @return 是否转换成功[true or false]
     */
    static bool to_string(const RJsonValue& json_value, OUT std::string &out_value)
    {
        rapidjson::StringBuffer l_buffer;
        rapidjson::Writer<rapidjson::StringBuffer> l_writer(l_buffer);
        json_value.Accept(l_writer);
        out_value = l_buffer.GetString();
        return true;
    }

    /**
     * 判断是否空的JSON对象
     * @param json_value 需要判断的json对象
     * @return 是否为空[true or false]
     */
    static bool is_null(const RJsonValue &json_value)
    {
        return json_value.IsNull();
    }

    /**
     * 获取JsonValue的Object对象
     * @param json_value 需要获取的json对象
     * @return 对应的Object对象
     */
    static RJObject get_object(RJsonValue &json_value)
    {
        if(!json_value.IsObject())
        {
            return get_empty_obj_value().GetObject();
        }

        return json_value.GetObject();
    }

    /**
     * 获取JsonValue的Array对象
     * @param json_value 需要获取的json对象
     * @return 对应的Array对象
     */
    static RJArray get_array(RJsonValue &json_value)
    {
        if(!json_value.IsArray())
        {
            return get_empty_arr_value().GetArray();
        }

        return json_value.GetArray();
    }
private:
    /**
      * 获取节点信息
      * 支持类型K_ID:[int, unsigned, bool, double, int64_t, uint64_t, int8_t, uint8_t, int16_t, uint16_t]
      * 内部使用
      */
    template<typename K_ID>
    static bool get_value(RJsonValue &json_value, OUT K_ID &out_value)
    {
        bool l_result = true;
        if(std::is_same<K_ID, int>::value && json_value.IsInt())
        {
            out_value = json_value.GetInt();
        }
        else if(std::is_same<K_ID, unsigned>::value && json_value.IsUint())
        {
            out_value = json_value.GetUint();
        }
        else if(std::is_same<K_ID, bool>::value && json_value.IsBool())
        {
            out_value = json_value.GetBool();
        }
        else if(std::is_same<K_ID, double>::value && json_value.IsDouble())
        {
            out_value = json_value.GetDouble();
        }
        else if(std::is_same<K_ID, int64_t>::value && json_value.IsInt64())
        {
            out_value = json_value.GetInt64();
        }
        else if(std::is_same<K_ID, uint64_t>::value && json_value.IsUint64())
        {
            out_value = json_value.GetUint64();
        }
        else if(std::is_same<K_ID, int8_t>::value && json_value.IsInt())
        {
            out_value = (int8_t)json_value.GetInt();
        }
        else if(std::is_same<K_ID, uint8_t>::value && json_value.IsInt())
        {
            out_value = (uint8_t)json_value.GetInt();
        }
        else if(std::is_same<K_ID, int16_t>::value && json_value.IsInt())
        {
            out_value = (int16_t)json_value.GetInt();
        }
        else if(std::is_same<K_ID, uint16_t>::value && json_value.IsInt())
        {
            out_value = (uint16_t)json_value.GetInt();
        }
        else
        {
            l_result = false;
        }

        return l_result;
    }

    /**
      * 判断节点是否存在
      * 内部使用
      */
    static bool has(RJsonValue &json_value, const char* key)
    {
        return json_value.HasMember(key);
    }

    /**
      * 生成一个空的节点
      * 内部使用
      */
    static RJsonValue& get_null()
    {
        static RJsonValue s_null_value(rapidjson::kNullType);
        return s_null_value;
    }

    /** 生成一个empty object value
     * 内部使用
     */
    static RJsonValue& get_empty_obj_value()
    {
        static RJsonValue s_empty_obj_value(rapidjson::kObjectType);
        return s_empty_obj_value;
    }

    /** 生成一个empty array value
     * 内部使用
     */
    static RJsonValue& get_empty_arr_value()
    {
        static RJsonValue s_empty_arr_value(rapidjson::kArrayType);
        return s_empty_arr_value;
    }
};

RELAX_NAMESPACE_END

#endif //__RX_JSONPARSER_H__
