#include "vector"
using namespace std;

int H = 5;

vector<int> X, Y, Z;

void disp()
{
    for (int h = H; h > 0; --h)
        printf("%d %d %d\n", (int)X.size() >= h ? X[h - 1] : 0,
               (int)Y.size() >= h ? Y[h - 1] : 0, (int)Z.size() >= h ? Z[h - 1] : 0);

    printf("X Y Z\n\n");
}

template <typename T>
void move(vector<T> &X, vector<T> &Z)
{
    // printf("X: %d, Y: %d, Z: %d\n", X.size(), Y.size(), Z.size());
    Z.push_back(X.back());
    X.pop_back();
    disp();
}

template <typename T>
void hanoi(int n, vector<T> &X, vector<T> &Y, vector<T> &Z)
{
    if (n == 1)
        move(X, Z);
    else
    {
        hanoi(n - 1, X, Z, Y); // X上的n-1个移到Y上
        move(X, Z);
        hanoi(n - 1, Y, X, Z); // Y上的n-1个移到Z上
    }
}

int main()
{
    // init
    for (int h = 1; h <= H; ++h)
        X.push_back(h);

    // algo
    hanoi(H, X, Y, Z);

    return 0;
}
