#include "stdio.h"
#include "random"
#include "assert.h"
// #include "cstdlib"
#include "bitset"
#include "iostream"
using namespace std;

int lr(int a)
{
    int c = (a >> 1) << 1;
    bitset<66> a1(a);
    bitset<66> c1(c);

    cout << a << "(" << a1 << ") -> " << c << "(" << c1 << ")\n";
    return c;
}

void disp_double(int a)
{
    bitset<64> a1(a);
    double a_d = (double)a;
    bitset<64> a_d1(a_d);
    cout << "int: " << a << "(" << a1 << "),  \ndouble: " << a_d << "(" << a_d1 << ")\n";
}

int main()
{
    int MAX_TRY = 1;
    for (int i = 0; i < MAX_TRY; i++)
    {

        int x = random();
        int y = random();
        int z = random();
        double dx = (double)x;
        double dy = (double)y;
        double dz = (double)z;

        double s1 = dx + dy + dz;
        double s2 = dz + dy + dx;
        // printf("dx: %f, dy: %f, dz: %f, s1: %f, s2: %f\n", dx, dy, dz, s1, s2);
        // printf(s1 == s2 ? "passed" : "faild\n");

        disp_double(x);
        // disp_double(y);
        // disp_double(z);

        // printf("i: %d, x: %d, y: %d, z: %d\n", i, x, y, z);

        // for (int j = -3; j < 3; j++)
        {
            // assert(lr(j) <= j);
        }

        if (x < 0)
        {
            break;
        }
    }

    return 0;
}
