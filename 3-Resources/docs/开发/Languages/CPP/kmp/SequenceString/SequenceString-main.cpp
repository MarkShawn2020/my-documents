#include "SequenceString.c"

int main()
{

    SString T1, T2;
    Str_Assign(T1, "hello");
    Str_Assign(T2, "world");
    Str_Print(T1);
    Str_Print(T2);
    printf("%d\n", Str_Compare(T1, T2));
    return 0;
}
