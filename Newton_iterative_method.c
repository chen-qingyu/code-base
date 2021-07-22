#include <math.h>
#include <stdio.h>

#define N 100

double newton(double x)
{
    double result = 1;
    for (int i = 0; i < N; i++)
    {
        result = (result + (x / result)) / 2;
    }
    return result;
}

int main(void)
{
    double x;
    printf("Please input a number: ");
    scanf("%lf", &x);
    printf("newton:\t%lf\n", newton(x));
    printf("sqrt:\t%lf\n", sqrt(x));
    return 0;
}
