#include <math.h>
#include <stdio.h>
#include <time.h>

double calc_polynomial_1(double a[], int n, double x);
double calc_polynomial_2(double a[], int n, double x);

// f(x) = a0 + a1*x + a2*x^2 + a3*x^3 + ... + an*x^n
typedef double (*function_t)(double a[], int n, double x);
void time_test(function_t function, const char* message, double a[], int n, double x);

int main(void)
{
    double a[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    double xs[] = {0, 1.1, 99};
    for (int i = 0; i < sizeof(xs) / sizeof(double); i++)
    {
        printf("f(%.1lf):\n", xs[i]);
        time_test(calc_polynomial_1, "Simple loop", a, sizeof(a) / sizeof(double), xs[i]);
        time_test(calc_polynomial_2, "Horner algorithm", a, sizeof(a) / sizeof(double), xs[i]);
        printf("\n");
    }

    return 0;
}

double calc_polynomial_1(double a[], int n, double x)
{
    double y = 0;
    for (int i = 0; i < n; i++)
    {
        y += a[i] * pow(x, i);
    }
    return y;
}

double calc_polynomial_2(double a[], int n, double x)
{
    double y = 0;
    for (int i = n - 1; i >= 0; i--)
    {
        y = a[i] + x * y;
    }
    return y;
}

void time_test(function_t function, const char* message, double a[], int n, double x)
{
    double result;

    clock_t start = clock();
    for (int i = 0; i < 1000000; i++)
    {
        result = function(a, n, x);
    }
    clock_t end = clock();

    printf("result: %lf, duration: %6.2lfms (%s)\n", result, (double)(end - start) / CLOCKS_PER_SEC * 1000, message);
}
