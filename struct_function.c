#include <stdio.h>

int max(int a, int b)
{
    return a > b ? a : b;
}

int min(int a, int b)
{
    return a < b ? a : b;
}

int pow2(int x)
{
    return x * x;
}

// 结构体
typedef struct
{
    int (*max)(int, int); //函数指针
    int (*min)(int, int);
    int (*pow2)(int);
} class;

// 初始化函数指针
void init(class *data)
{
    data->max = max;
    data->min = min;
    data->pow2 = pow2;
}

int main(void)
{
    int a, b, c;
    class TestClass;

    init(&TestClass); // “构造函数”

    a = TestClass.max(233, 1111); // “方法调用”
    b = TestClass.min(233, 1111);
    c = TestClass.pow2(5);

    printf("result:\nmax: %d\nmin: %d\npow2: %d", a, b, c);
    return 0;
}
