#include "kmp.c"

int main()
{
    SString T;
    int next[MAX_STRING_LENGTH], nextval[MAX_STRING_LENGTH];
    Str_Assign(T, "abababcab");

    printf("input  : ");
    Str_Print(T, 1);

    Str_GetNext(T, next);
    printf("next   : ");
    for (int i = 1; i <= next[0]; i++)
        printf("%d ", next[i]);
    printf("\n");

    Str_GetNextVal(T, nextval);
    printf("nextval: ");
    for (int i = 1; i <= nextval[0]; i++)
        printf("%d ", nextval[i]);
    printf("\n");

    return 0;
}
