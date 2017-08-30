/*
 * file_name: test_sensitive.cpp
 * file_detail:test Sensitive.h interface
 * created by silver0511
 */

#include "common/Sensitive.h"

USING_RELAX_NAMESPACE

int main()
{
    Sensitive sensitive;
    string in_text = "我你她fuck司法局圣诞快乐附件螺蛳粉放得开见风使毛泽东舵";
    string out_text;
    sensitive.replace(in_text, out_text);
    printf("sensitive in_text:%s, out_text:%s \n", in_text.c_str(), out_text.c_str());
    getchar();
    return 1;
}