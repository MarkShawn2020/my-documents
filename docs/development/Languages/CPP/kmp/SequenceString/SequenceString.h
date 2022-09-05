#ifndef SEQUENCESTRING_H
#define SEQUENCESTRING_H
#include "../general/base.h"

#define MAX_STRING_LENGTH 255

typedef unsigned char SString[MAX_STRING_LENGTH + 1];

Status Str_Assign(SString T, const char *ch);

/**
 * @brief 比较两个字符串的大小，小于返回-1，大于返回1，相等返回0
 *
 * @param T1
 * @param T2
 * @return int
 */
int Str_Compare(SString T1, SString T2);

/**
 * @brief SString内部数据的打印
 *
 * @param T
 * @param blank 每个字符间的空格，默认0
 */
void Str_Print(SString T, int blank);

#endif
