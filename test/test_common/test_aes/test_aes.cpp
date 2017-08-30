/*
 * file_name: test_aes.cpp
 * file_detail:test aes interface
 * created by silver0511
 */

#include "common/platform.h"
#include "common/aes.h"

USING_RELAX_NAMESPACE

int main()
{
    unsigned char key[] = "relax2017server1";
    string before_encode = "我是relax_server啦啦haha,miehaha, hello world";
    ulong input_length = before_encode.length();
    ubyte *input = new ubyte[before_encode.length()];
    zero_memory(input, input_length);
    memcpy(input, before_encode.c_str(), input_length);
    printf("before encode message is: %s length:%d\n", input, input_length);
    AES aes_encode(key);
    aes_encode.Cipher(input, input_length);
    ulong output_length = input_length;
    ubyte *output = new ubyte[output_length];
    zero_memory(output, output_length);
    memcpy(output, input, output_length);
    AES aes_decode(key);
    aes_decode.InvCipher(output, output_length);
    printf("decoded message is:%s length:%d\n", output, output_length);
    return 1;
}