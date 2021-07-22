#include <stdio.h>

int cir(int n, int p)
{
    int k = 0;
    for (int i = 2; i <= n; i++)
    {
        k = (k + p) % i;
    }
    return k + 1;
}

int main(void)
{
    int n; // 总人数
    int p; // 退出序号
    scanf("%d %d", &n, &p);
    printf("%d\n", cir(n, p)); // 最后剩下的人的原始序号
    return 0;
}
