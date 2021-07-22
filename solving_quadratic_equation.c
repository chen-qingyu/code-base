#include <math.h>
#include <stdio.h>

int main(void)
{
    double a, b, c, delta, x1, x2, m, n, i, j;
    printf("请输入一元二次方程的三个系数：\n");
    scanf("%lf %lf %lf", &a, &b, &c);

    if (fabs(a) <= 1e-6)
    {
        printf("输入错误：系数a不能为零！\n");
    }
    else
    {
        delta = b * b - 4 * a * c;
        m = -b / (2 * a);
        n = sqrt(fabs(delta)) / (2 * fabs(a));
        i = m + n;
        j = m - n;

        if (delta < 0)
        {
            printf("方程有两个不同的复数根：\n");
            printf("%.2lf + %.2lfi\n%.2lf - %.2lfi\n", m, n, m, n);
        }
        else
        {
            if (i == j)
            {
                printf("方程有两个相同的实数根：\n");
                printf("%.2lf\n%.2lf\n", i, i);
            }
            else
            {
                x1 = (i > j) ? i : j;
                x2 = (i > j) ? j : i;
                printf("方程有两个不同的实数根：\n");
                printf("%.2lf\n%.2lf\n", x1, x2);
            }
        }
        return 0;
    }
}
