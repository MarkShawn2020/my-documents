# cpp howto

1. [grammar relative](#grammar-relative)
   1. [compare between strings](#compare-between-strings)
   2. [`optional`](#optional)
2. [what's `stdafx.h` (预编译头)](#whats-stdafxh-预编译头)
3. [how to call C++ functions in C](#how-to-call-c-functions-in-c)

## grammar relative

### compare between strings

cpp++ {cmd=true} const auto s1="hello world"; const auto s2="hello";

// equal by pointer ? s1 == s2

// equal by compare (char by char) s1.compare(s2) == 0 // equal !s1.compare(s2) // equal

s1.compare(s2) != 0 // not equal s1.compare(s2) // not equal

// contain s1.find(s2) != std::string::npos // contains s1.contains(s2) // contains, C++23

```

see:

- [Differences between C++ string == and compare()? - Stack Overflow](https://stackoverflow.com/questions/9158894/differences-between-c-string-and-compare)

- [Comparing two strings in C++ - GeeksforGeeks](https://www.geeksforgeeks.org/comparing-two-strings-cpp/)

### `optional`

cpp++ {cmd}
#include <string>
#include <functional>
#include <iostream>
#include <optional>

// optional can be used as the return type of a factory that may fail
std::optional<std::string> create(bool b) {
    if (b)
        return "Godzilla";
    return {};
}

// std::nullopt can be used to create any (empty) std::optional
auto create2(bool b) {
    return b ? std::optional<std::string>{"Godzilla"} : std::nullopt;
}

// std::reference_wrapper may be used to return a reference
auto create_ref(bool b) {
    static std::string value = "Godzilla";
    return b ? std::optional<std::reference_wrapper<std::string>>{value}
             : std::nullopt;
}

int main()
{
    std::cout << "create(false) returned "
              << create(false).value_or("empty") << '\n';

    // optional-returning factory functions are usable as conditions of while and if
    if (auto str = create2(true)) {
        std::cout << "create2(true) returned " << *str << '\n';
    }

    if (auto str = create_ref(true)) {
        // using get() to access the reference_wrapper's value
        std::cout << "create_ref(true) returned " << str->get() << '\n';
        str->get() = "Mothra";
        std::cout << "modifying it changed it to " << str->get() << '\n';
    }
}
```

see:

- [std::optional - cppreference.com](https://en.cppreference.com/w/cpp/utility/optional)

## what's `stdafx.h` (预编译头)

ref:

- [Visual Studio 中头文件 stdafx.h 的作用 - yhjoker - 博客园](https://www.cnblogs.com/yhjoker/p/8110684.html)

## how to call C++ functions in C

ref:

- [How to call C++ function from C? - Stack Overflow](https://stackoverflow.com/questions/2744181/how-to-call-c-function-from-c)

- [(23 条消息) C++与 C 之间相互接口和库函数调用\_OSKernelLAB(gatieme)-CSDN 博客](https://blog.csdn.net/gatieme/article/details/52730680)
