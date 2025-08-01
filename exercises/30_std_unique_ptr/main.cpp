#include "../exercise.h"
#include <cstring>
#include <memory>
#include <string>
#include <vector>

// READ: `std::unique_ptr` <https://zh.cppreference.com/w/cpp/memory/unique_ptr>

std::vector<std::string> RECORDS;

class Resource {
    std::string _records;

public:
    void record(char record) {
        _records.push_back(record);
    }

    ~Resource() {
        RECORDS.push_back(_records);
    }
};

using Unique = std::unique_ptr<Resource>;
Unique reset(Unique ptr) {
    if (ptr) ptr->record('r');
    return std::make_unique<Resource>();
}
Unique drop(Unique ptr) {
    if (ptr) ptr->record('d');
    return nullptr;
}
Unique forward(Unique ptr) {
    if (ptr) ptr->record('f');
    return ptr;
}

int main(int argc, char **argv) {
    std::vector<std::string> problems[3];

    drop(forward(reset(nullptr)));
    problems[0] = std::move(RECORDS);

    forward(drop(reset(forward(forward(reset(nullptr))))));
    problems[1] = std::move(RECORDS);

    drop(drop(reset(drop(reset(reset(nullptr))))));
    problems[2] = std::move(RECORDS);

    // ---- 不要修改以上代码 ----

    std::vector<const char *> answers[]{
        {"fd"},
        // TODO: 分析 problems[1] 中资源的生命周期，将记录填入 `std::vector`
        // NOTICE: 此题结果依赖对象析构逻辑，平台相关，提交时以 CI 实际运行平台为准
        {"d", "ffr"},
        {"d", "d", "r"},
    };

    // ---- 不要修改以下代码 ----

    for (auto i = 0; i < 3; ++i) {
        ASSERT(problems[i].size() == answers[i].size(), "wrong size");
        for (auto j = 0; j < problems[i].size(); ++j) {
            // std::cout << problems[i][j].c_str() << ' ';
            ASSERT(std::strcmp(problems[i][j].c_str(), answers[i][j]) == 0, "wrong location");
        }
        // std::cout << std::endl;
    }

    return 0;
}

/*
生命周期关键点
所有权转移：
unique_ptr 通过移动语义转移所有权
每次函数返回时，要么转移所有权，要么销毁对象
析构时机：
当 unique_ptr 被重新赋值（如 reset()）
当 unique_ptr 离开作用域
显式调用 reset()
记录顺序：
函数调用时先记录操作字符
析构时才会将记录存入全局变量
*/
