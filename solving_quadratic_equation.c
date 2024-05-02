#include <math.h>
#include <stdio.h>

int main(void)
{
    double a, b, c;
    printf("Please enter the quadratic equation coefficients a, b, c:\n");
    scanf("%lf %lf %lf", &a, &b, &c);
    if (a == 0 && b == 0)
    {
        printf("The coefficients are invalid.\n");
        return 0;
    }

    printf("The equation: %.2lfx^2%+.2lfx%+.2lf = 0\n", a, b, c);

    if (a == 0) // and b != 0
    {
        printf("The equation has a real root:\n");
        printf("x = %.2lf\n", -c / b);
        return 0;
    }
    // else a != 0

    double delta = b * b - 4 * a * c;
    double m = -b / (2 * a);
    double n = sqrt(fabs(delta)) / (2 * a);
    if (delta < 0)
    {
        printf("The equation has two different plural roots:\n");
        printf("x1 = %.2lf%+.2lfi, x2 = %.2lf%+.2lfi\n", m, n, m, -n);
    }
    else if (delta == 0)
    {
        printf("The equation has two identical real roots:\n");
        printf("x1 = x2 = %.2lf\n", m);
    }
    else // delta > 0
    {
        printf("The equation has two different real roots:\n");
        printf("x1 = %.2lf, x2 = %.2lf\n", m + n, m - n);
    }

    return 0;
}
