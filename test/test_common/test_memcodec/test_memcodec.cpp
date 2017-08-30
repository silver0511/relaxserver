/*
 * file_name: test_memcodec.cpp
 * file_detail:test MemCodec.h interface
 * created by silver0511
 */

#include "common/BaseFun.h"
#include "common/MemCodec.h"

USING_RELAX_NAMESPACE

struct S_BASE_PACKAGE
{
public:
    S_BASE_PACKAGE()
    {

    }
    virtual ~S_BASE_PACKAGE(){};
    int encode(ubyte *buffer, ulong buf_len)
    {
        try
        {
            MemCodec mem_codec(buffer, buf_len, ICodec::WRITE);
            int result = codec(mem_codec);
            if(result < 0)
            {
                printf("encode failed");
            }

            return result;
        }
        catch (int value)
        {
            printf("encode exception");
            return value;
        }

    }

    int decode(ubyte *buffer, ulong buf_len)
    {
        try
        {
            MemCodec mem_codec(buffer, buf_len, ICodec::READ);
            int result = codec(mem_codec);
            if(result < 0)
            {
                printf("decode failed");
            }

            return result;
        }
        catch (int value)
        {
            printf("decode exception");
            return value;
        }
    }
public:
    virtual int codec(ICodec &codec) = 0;
};

struct TEST_PACKAGE_RQ : public S_BASE_PACKAGE
{
public:
    bool bool_value;
    byte byte_value;
    ubyte ubyte_value;
    short short_value;
    ushort ushort_value;
    int int_value;
    uint uint_value;
    int64 int64_value;
    uint64 uint64_value;
    float float_value;
    double double_value;
    char char_value[512];
    wchar_t  wchar_value[512];
    ubyte ubyte_array[10];
    uint ubyte_arr_len;
    string string_value;
    wstring wstring_value;

    TEST_PACKAGE_RQ()
    {
        zero_memory(char_value, 512);
        zero_memory(wchar_value, sizeof(wchar_t) * 512);
        zero_memory(ubyte_array, 10);
    }
    virtual int codec(ICodec &codec)
    {
        int offset = 0;
        offset += codec.codec(bool_value);
        offset += codec.codec(byte_value);
        offset += codec.codec(ubyte_value);
        offset += codec.codec(short_value);
        offset += codec.codec(ushort_value);
        offset += codec.codec(int_value);
        offset += codec.codec(uint_value);
        offset += codec.codec(int64_value);
        offset += codec.codec(uint64_value);
        offset += codec.codec(float_value);
        offset += codec.codec(double_value);
        offset += codec.codec(char_value);
        offset += codec.codec(wchar_value);
        offset += codec.codec(ubyte_array, ubyte_arr_len);
        offset += codec.codec(string_value);
        offset += codec.codec(wstring_value);
        printf("===========pos:%d==============\n", codec.get_pos());
        return offset;
    }

    void get_dump()
    {
        printf("bool_value:%d, byte_value:%d, ubyte_value:%d, short_value:%d, "
                       "ushort_value:%d, int_value:%d, uint_value:%lld, int64_value:%lld, "
                       "uint64_value:%llu, float_value:%f, double_value:%lf, "
                       "char_value:%s, string_value:%s, ",
        bool_value, byte_value, ubyte_value, short_value, ushort_value, int_value, uint_value,
        int64_value, uint64_value, float_value, double_value, char_value, string_value.c_str());
        printf("ubyte_array:{");
        for(int i = 0; i < ubyte_arr_len; i++)
        {
            printf("%d", ubyte_array[i]);
            if(i < ubyte_arr_len - 1)
            {
                printf(",");
            }
        }
        printf("}, ");
        printf("wchar_value:%ls, wstring_value:%ls \n\n\n", wchar_value, wstring_value.c_str());
//        wcout << "wchar_value:" << wchar_value << " wstring_value:" << wstring_value.c_str() << endl << endl;
    }
};

int main()
{
//    ios_base::sync_with_stdio(false);
//    wcout.imbue(locale(""));
    setlocale(LC_ALL, "en_US.UTF-8");
    TEST_PACKAGE_RQ test_package_rq_encode;
    test_package_rq_encode.bool_value = true;
    test_package_rq_encode.byte_value = -127;
    test_package_rq_encode.ubyte_value = 255;
    test_package_rq_encode.short_value = -23456;
    test_package_rq_encode.ushort_value = 65530;
    test_package_rq_encode.int_value = -123456;
    test_package_rq_encode.uint_value = 123456;
    test_package_rq_encode.int64_value = -123456789;
    test_package_rq_encode.uint64_value = 123456789;
    test_package_rq_encode.float_value = -123456.789;
    test_package_rq_encode.double_value = 123456789.1234;
    const char *char_value = "我是char_value。";
    memcpy_safe((char *)char_value, strlen(char_value), test_package_rq_encode.char_value, 512);
    const wchar_t *wchar_value = L"我是wchar_value。";
    memcpy(test_package_rq_encode.wchar_value, wchar_value, wcslen(wchar_value) * sizeof(wchar_t));
    ubyte ubyte_array[10] = {0,1,2,3,4,5,6,7,8,9};
    memcpy(test_package_rq_encode.ubyte_array, ubyte_array, 10);
    test_package_rq_encode.ubyte_arr_len = 10;
    test_package_rq_encode.string_value = "我是string_value。";
    test_package_rq_encode.wstring_value= L"我是wstring_value。";
    ubyte encode_buffer[4096] = {0};
    int encode_len = test_package_rq_encode.encode(encode_buffer, 4096);
    printf("encoded:%d \n", encode_len);
    test_package_rq_encode.get_dump();
    ubyte *decode_buffer = new ubyte[encode_len];
    zero_memory(decode_buffer, encode_len);
    memcpy(decode_buffer, encode_buffer, encode_len);
    TEST_PACKAGE_RQ test_package_rq_decode;
    int decode_len = test_package_rq_decode.decode(decode_buffer, encode_len);
    printf("\ndecoded:%d \n", decode_len);
    test_package_rq_decode.get_dump();
    getchar();
    return 1;
}