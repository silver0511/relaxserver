/*
 * file_name: test_rjson.h
 * file_detail:test json interface
 * created by silver0511
 */

#include "rjson/JsonParser.h"
#include "gtest-1.7.0/include/gtest/gtest.h"
#include "fakeit/single_header/gtest/fakeit.hpp"

using namespace fakeit;
USING_RELAX_NAMESPACE

unsigned long get_time()
{
    struct timeval now;
    gettimeofday(&now,NULL);
    unsigned long tv_sec = now.tv_sec;
//    unsigned long tv_usec = now.tv_usec;
    return tv_sec * 1000000 + now.tv_usec;
}

string json_encode()
{
    //根对象
    RJ_CREATE_O_DOCUMENT(l_document, l_allocator)
    string str;
    str = "i am parent str";
    JsonParse::add(l_document, "parent_str", str, l_allocator);
    JsonParse::add<int8_t>(l_document, "parent_int8", (int8_t)8, l_allocator);
    JsonParse::add<uint8_t>(l_document, "parent_uint8", (uint8_t)-1, l_allocator);
    JsonParse::add<int16_t>(l_document, "parent_int16", (int16_t)16, l_allocator);
    JsonParse::add<uint16_t>(l_document, "parent_uint16", (uint16_t)-2, l_allocator);
    JsonParse::add<int>(l_document, "parent_int", 111, l_allocator);
    JsonParse::add<unsigned>(l_document, "parent_unsigned", (unsigned)222, l_allocator);
    JsonParse::add<bool>(l_document, "parent_bool", true, l_allocator);
    JsonParse::add<double>(l_document, "parent_double", 333.33f, l_allocator);
    JsonParse::add<int64_t>(l_document, "parent_int64", (int64_t)131239129381290, l_allocator);
    JsonParse::add<uint64_t>(l_document, "parent_uint64_t", (uint64_t)-2, l_allocator);

    //内嵌对象1
    RJ_CREATE_OBJECT(child_object)
    str = "i am child str";
    JsonParse::add(child_object, "child_str", str, l_allocator);
    JsonParse::add<int64_t>(child_object, "child_int64", (int64_t)7342342777, l_allocator);

    //内嵌数组2->内嵌对象1
    RJ_CREATE_ARRAY(child_array1)
    for(int i = 0; i < 100; i++)
    {
        JsonParse::push<int>(child_array1, i, l_allocator);
    }
    JsonParse::add(child_object, "child_array1", child_array1, l_allocator);

    //内嵌数组1
    RJ_CREATE_ARRAY(child_array)
    str = "i am child array str";
    JsonParse::push(child_array, str, l_allocator);
    JsonParse::push<uint64_t>(child_array, (uint64_t)349234283, l_allocator);

    //内嵌数组2->内嵌数组1
    RJ_CREATE_ARRAY(child_array2)
    str = "i am child array2 str";
    JsonParse::push(child_array2, str, l_allocator);
    JsonParse::push<uint64_t>(child_array2, (uint64_t)88888888, l_allocator);
    JsonParse::push(child_array, child_array2, l_allocator);

    //内嵌对象2->内嵌数组1
    RJ_CREATE_OBJECT(child_obj2)
    str = "i am child4 str";
    JsonParse::add(child_obj2, "child4_str", str, l_allocator);
    JsonParse::add<int64_t>(child_obj2, "child4_int64", (int64_t)4234121211313, l_allocator);
    JsonParse::push(child_array, child_obj2, l_allocator);
    JsonParse::push<uint8_t>(child_array, (uint8_t)-10, l_allocator);
    JsonParse::push<int16_t>(child_array, (int16_t)27, l_allocator);

    //内嵌数组1->根对象
    JsonParse::add(l_document, "child_array", child_array, l_allocator);
    //内嵌对象1->根对象
    JsonParse::add(l_document, "child_obj", child_object, l_allocator);

    std::string out_json = "";
    JsonParse::to_string(l_document, out_json);
    return out_json;
}

void json_decode(RJDocument &doc, const char* data)
{
    JsonParse::parse(doc, data);
    //根对象解析
    string str_val = JsonParse::get(doc, "parent_str");
    EXPECT_EQ(str_val, "i am parent str");
    int int_val = JsonParse::get<int>(doc, "parent_int");
    EXPECT_EQ(int_val, 111);
    unsigned unsigned_val = JsonParse::get<unsigned>(doc, "parent_unsigned");
    EXPECT_EQ(unsigned_val, (unsigned)222);
    bool b_val = JsonParse::get<bool>(doc, "parent_bool");
    EXPECT_EQ(b_val, true);
    double double_val = JsonParse::get<double>(doc, "parent_double");
    EXPECT_EQ(double_val, 333.33f);
    int64_t  i64_val = JsonParse::get<int64_t>(doc, "parent_int64");
    EXPECT_EQ(i64_val, (int64_t)131239129381290);
    uint64_t  ui64_val = JsonParse::get<uint64_t>(doc, "parent_uint64_t");
    EXPECT_EQ(ui64_val, (uint64_t)-2);
    int8_t int8_val = JsonParse::get<int8_t>(doc, "parent_int8");
    EXPECT_EQ(int8_val, (int8_t)8);
    uint8_t uint8_val = JsonParse::get<uint8_t>(doc, "parent_uint8");
    EXPECT_EQ(uint8_val, (uint8_t)-1);
    int16_t int16_val = JsonParse::get<int16_t>(doc, "parent_int16");
    EXPECT_EQ(int16_val, (int16_t)16);
    uint16_t uint16_val = JsonParse::get<uint16_t>(doc, "parent_uint16");
    EXPECT_EQ(uint16_val, (uint16_t)-2);

    //内嵌对象1
    RJsonValue &child_object = JsonParse::get_child(doc, "child_obj");
    EXPECT_FALSE(child_object.IsNull());
    str_val = JsonParse::get(child_object, "child_str");
    EXPECT_EQ(str_val, "i am child str");
    i64_val = JsonParse::get<int64_t>(child_object, "child_int64");
    EXPECT_EQ(i64_val, (int64_t)7342342777);

    //内嵌数组2->内嵌对象1
    RJsonValue &child_array1 = JsonParse::get_child(child_object, "child_array1");
    //解析数组
    int i = 0;
    int data_count = JsonParse::count(child_array1);
    for (; i < data_count; ++i)
    {
        int_val = JsonParse::at<int>(child_array1, i);
        EXPECT_EQ(int_val, i);
    }

    i = 0;
    for (RJConstIterator iter = child_array1.Begin(); iter != child_array1.End(); ++iter)
    {
        EXPECT_EQ(iter->GetInt(), i);
        i++;
    }
    //c++11 support
    i = 0;
    for (auto &v : JsonParse::get_array(child_array1))
    {
        EXPECT_EQ(v.GetInt(), i);
        i++;
    }

    //内嵌数组1
    RJsonValue &child_array = JsonParse::get_child(doc, "child_array");
    EXPECT_FALSE(child_array.IsNull());
    str_val = JsonParse::at(child_array, 0);
    EXPECT_EQ(str_val, "i am child array str");
    ui64_val = JsonParse::at<uint64_t>(child_array, 1);
    EXPECT_EQ(ui64_val, (uint64_t)349234283);

    //内嵌数组2->内嵌数组1
    RJsonValue &child_array2 = JsonParse::at_child(child_array, 2);
    EXPECT_FALSE(child_array2.IsNull());
    str_val = JsonParse::at(child_array2, 0);
    EXPECT_EQ(str_val, "i am child array2 str");
    ui64_val = JsonParse::at<uint64_t>(child_array2, 1);
    EXPECT_EQ(ui64_val, (uint64_t)88888888);


    //内嵌对象2->内嵌数组1
    RJsonValue &child_obj2 = JsonParse::at_child(child_array, 3);
    EXPECT_FALSE(child_obj2.IsNull());
    str_val = JsonParse::get(child_obj2, "child4_str");
    EXPECT_EQ(str_val, "i am child4 str");
    i64_val = JsonParse::get<int64_t>(child_obj2, "child4_int64");
    EXPECT_EQ(i64_val, (int64_t)4234121211313);
    for(auto &v : JsonParse::get_object(child_obj2))
    {
        string ss_name = v.name.GetString();
        if(strncmp(ss_name.c_str(), "child4_str", ss_name.size()) == 0)
        {
            string ss_value = v.value.GetString();
            EXPECT_EQ(ss_value, "i am child4 str");
        }

        if(strncmp(ss_name.c_str(), "child4_int64", ss_name.size()) == 0)
        {
            EXPECT_EQ(v.value.GetInt64(), (int64_t)4234121211313);
        }
    }


    uint8_val = JsonParse::at<uint8_t>(child_array, 4);
    EXPECT_EQ(uint8_val, (uint8_t)-10);
    int16_val = JsonParse::at<int16_t>(child_array, 5);
    EXPECT_EQ(int16_val, (int16_t)27);
}

void *aaa(void* p)
{
    while(true)
    {
        string out_json = json_encode();
        RJ_CREATE_EMPTY_DOCUMENT(r_document)
        json_decode(r_document, out_json.c_str());
    }
}

//int main()
//{
//    unsigned long start_time = get_time();
//    string out_json = json_encode();
//    unsigned long end_time = get_time();
//    cout << "delta time encode: " << (end_time - start_time) << endl;
//    cout << out_json.c_str() << endl;
//
//
//
//    start_time = get_time();
//    RJ_CREATE_EMPTY_DOCUMENT(r_document)
//    json_decode(r_document, out_json.c_str());
//    end_time = get_time();
//    cout << "delta time decode: " << (end_time - start_time) << endl;
//
////    for(int i = 0; i < 1000; i++)
////    {
////        pthread_t lthread;
////        pthread_create(&lthread, NULL, aaa, 0);
////    }
//
//    getchar();
//    return 1;
//}

TEST(basic_check, test_rjson) {
    unsigned long start_time = get_time();
    string out_json = json_encode();
    unsigned long end_time = get_time();
    cout << endl << "delta time encode: " << (end_time - start_time) << endl;
    cout << out_json.c_str() << endl;



    start_time = get_time();
    RJ_CREATE_EMPTY_DOCUMENT(r_document)
    json_decode(r_document, out_json.c_str());
    end_time = get_time();
    cout << "delta time decode: " << (end_time - start_time) << endl;

//    for(int i = 0; i < 1000; i++)
//    {
//        pthread_t lthread;
//        pthread_create(&lthread, NULL, aaa, 0);
//    }
}