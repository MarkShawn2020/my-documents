#ifndef SEQUENCESTRING_C
#define SEQUENCESTRING_C
#include "./SequenceString.h"

Status Str_Assign(SString T, const char *ch)
{
    int ch_len = strlen(ch);
    if (ch_len > MAX_STRING_LENGTH)
        return ERROR;

    T[0] = ch_len;
    for (int i = 0; i < ch_len; i++)
    {
        T[i + 1] = ch[i];
    }
    return OK;
}

int Str_Compare(SString T1, SString T2)
{
    int i = 1, j = 1;
    while (i <= T1[0] && j <= T2[0])
    {
        if (T1[i] > T2[i])
            return 1;
        if (T1[i] < T2[i])
            return -1;
        ++i, ++j;
    }
    return T1[0] > T2[0] ? 1 : T1[0] < T2[0] ? -1
                                             : 0;
}

void Str_Print(SString T, int blank)
{
    for (int i = 0; i < T[0]; i++)
    {
        printf("%c", T[i + 1]);
        for (int j = 0; j < blank; j++)
            printf(" ");
    }
    printf("\n");
}

void Str_Print(SString T)
{
    Str_Print(T, 0);
}

#endif
