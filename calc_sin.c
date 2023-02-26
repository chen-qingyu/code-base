#include <stdio.h>

double sin(double x)
{
    double t = x, s = x;
    for (int i = 1; i < 1000; i++)
    {
        t *= -1 * x * x / ((2 * i) * (2 * i + 1));
        s += t;
    }
    return s;
}

int main(void)
{
    double x;
    printf("x = ");
    scanf("%lf", &x);

    printf("sin(x) = %lf\n", sin(x));

    return 0;
}
