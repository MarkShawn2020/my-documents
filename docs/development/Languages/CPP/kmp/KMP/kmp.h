#ifndef KMP_H
#define KMP_H
#include "../SequenceString/SequenceString.c"

/**
 * @brief
 *
 * @param T         接受的原串
 * @param next   返回的Next数组
 * @return Status
 */
Status Str_GetNext(SString T, int next[]);

#endif
