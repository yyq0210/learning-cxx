#include "../exercise.h"
#include <vector>

// READ: std::vector <https://zh.cppreference.com/w/cpp/container/vector_bool>
// READ: 模板特化 <https://zh.cppreference.com/w/cpp/language/template_specialization>

// TODO: 将下列 `?` 替换为正确的代码
int main(int argc, char **argv) {
    std::vector<bool> vec(100, true);// TODO: 正确调用构造函数
    ASSERT(vec[0], "Make this assertion pass.");
    ASSERT(vec[99], "Make this assertion pass.");
    ASSERT(vec.size() == 100, "Make this assertion pass.");
    // NOTICE: 平台相关！注意 CI:Ubuntu 上的值。
    std::cout << "sizeof(std::vector<bool>) = " << sizeof(std::vector<bool>) << std::endl;
    ASSERT(sizeof(vec) == 40, "Fill in the correct value.");
    {
        vec[20] = false;
        ASSERT(!vec[20], "Fill in `vec[20]` or `!vec[20]`.");
    }
    {
        vec.push_back(false);
        ASSERT(vec.size() == 101, "Fill in the correct value.");
        ASSERT(!vec[100], "Fill in `vec[100]` or `!vec[100]`.");
    }
    {
        auto ref = vec[30];
        ASSERT(ref, "Fill in `ref` or `!ref`");
        ref = false;
        ASSERT(!ref, "Fill in `ref` or `!ref`");
        // THINK: WHAT and WHY?
        ASSERT(!vec[30], "Fill in `vec[30]` or `!vec[30]`.");
    }
    return 0;
}
/*
关键知识点
std::vector<bool> 是特化版本：
标准库对 bool 类型做了空间优化特化
每个 bool 值只占1个bit（而不是1个byte）
因此不能直接返回 bool&（因为无法取单个bit的地址）
auto ref = vec[30] 的实际类型：
vec[30] 返回的是 std::vector<bool>::reference 代理对象
auto 会推导出这个代理类型（而不是 bool）
这个代理对象相当于一个"指向bit的引用"
---------------------------------------------------------
为什么不是 vec[30]？
因为：
ref = false 已经修改了第30个元素的值
ref 是代理引用（不是独立变量），修改会直接影响vector
因此 vec[30] 现在确实是 false
*/
