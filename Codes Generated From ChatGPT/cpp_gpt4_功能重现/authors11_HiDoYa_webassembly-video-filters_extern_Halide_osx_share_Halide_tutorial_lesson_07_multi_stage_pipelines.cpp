// 引入头文件
#include "Halide.h"
#include <stdio.h>

// 声明 Halide 命名空间
using namespace Halide;

int main() {
    // 定义 Halide::Func 对象，代表一个计算阶段
    Func gradient("gradient");
    
    // 定义 Var 对象，用作计算阶段中的变量
    Var x("x"), y("y");
    
    // 定义 Expr 对象 e，表示函数在 x, y 位置的值
    Expr e = x + y;
    
    // 将计算阶段与表达式关联
    gradient(x, y) = e;
    
    // 定义图像的宽度和高度
    int width = 512;
    int height = 512;

    // 通过 .realize() 方法实现对函数的计算
    Buffer<int32_t> output = gradient.realize({width, height});

    // 检测计算结果是否正确
    for (int j = 0; j < output.height(); j++) {
        for (int i = 0; i < output.width(); i++) {
            if (output(i, j) != i + j) {
                printf("输出位置 (%d, %d) 的像素值不正确: %d\n", i, j, output(i, j));
                return -1;
            }
        }
    }
    
    // 如果计算结果正确，输出成功信息
    printf("成功计算并检查了 %d x %d 的图像\n", width, height);

    return 0;
}
