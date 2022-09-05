#ifndef KMP_C
#define KMP_C
#include "kmp.h"

Status Str_GetNext(SString T, int next[])
{

    int i = 1; // 当前主串匹配位
    int j = 0; // 模式串下标位，初始化为0
    next[0] = T[0];
    next[1] = 0;
    while (i < T[0])
    {
        if (j == 0 || T[i] == T[j])
        {
            ++i, ++j;
            next[i] = j;
        }
        else
        {
            j = next[j];
        }
    }
    return OK;
}

Status Str_GetNextVal(SString T, int nextval[])
{

    int i = 1; // 当前主串匹配位
    int j = 0; // 模式串下标位，初始化为0
    nextval[0] = T[0];
    nextval[1] = 0;
    while (i < T[0])
    {
        if (j == 0 || T[i] == T[j])
        {
            ++i, ++j;
            // 如果相等，则取其前驱【改进之处】
            nextval[i] = T[i] == T[j] ? nextval[j] : j;
        }
        else
        {
            j = nextval[j];
        }
    }
    return OK;
}
#endif
