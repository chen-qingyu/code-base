#include <stdio.h>

long long fac(int); //用long long类型通常最大可储存20的阶乘

int main(void)
{
    int n;

    puts("Please enter a integer to calculate the factorial (otherwise to exit).\n");
    while (scanf("%d", &n)) //输入非整数则退出
    {
        if (n < 0) //增加程序健壮性
        {
            puts("Please enter a positive integer.\n");
            continue;
        }
        if (n > 20) //增加程序健壮性
        {
            printf("%d! is too huge to calculate. >_<\n\n", n);
            continue;
        }
        printf("%d! = %lld\n\n", n, fac(n));
    }
    puts("\nBye~");

    return 0;
}

long long fac(int n)
{
    if (n == 0) //基例(0! == 1)
    {
        return 1;
    }
    else //链条
    {
        return n * fac(n - 1);
    }
}
