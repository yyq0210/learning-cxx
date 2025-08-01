#include "../exercise.h"

// READ: 有 cv 限定符的成员函数 <https://zh.cppreference.com/w/cpp/language/member_functions>

struct Fibonacci {
    int numbers[11];
    // TODO: 修改方法签名和实现，使测试通过
    int get(int i) const{
        return numbers[i];
    }

};

int main(int argc, char **argv) {
    Fibonacci constexpr FIB{{0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55}};
    ASSERT(FIB.get(10) == 55, "fibonacci(10) should be 55");
    std::cout << "fibonacci(10) = " << FIB.get(10) << std::endl;
    return 0;
}
/*
修改点：
在 get 方法的签名后添加了 const 限定符，使其成为一个常量成员函数。这样，get 方法就可以被 const 对象（如 FIB）调用。
由于 get 方法不修改任何成员变量，因此可以安全地声明为 const。
为什么需要这样修改：
FIB 被声明为 constexpr，这意味着它是一个编译时常量对象，其所有成员都是 const 的。
在 C++ 中，const 对象只能调用 const 成员函数，以确保不会修改对象的状态。
原代码中的 get 方法没有 const 限定符，因此不能被 const 对象 FIB 调用，导致编译错误。
添加 const 限定符后，get 方法可以被 const 对象调用，从而通过测试。
*/