#include "cstdio"
#include "cstring"

struct indices
{
    std::size_t i, j, k;
};

struct my_array_view
{
    double &operator[](indices x);
};

int main()
{
    auto letters = view::iota('a', 'g');
    std::cout << letters << '\n';
};