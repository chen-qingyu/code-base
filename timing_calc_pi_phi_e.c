#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

double calc_pi_1(int n);
double calc_pi_2(int n);
double calc_pi_3(int n);
double calc_pi_4(int n);

double calc_phi_1(int _);
double calc_phi_2(int n);
double calc_phi_3(int n);

double calc_e_1(int n);
double calc_e_2(int n);
double calc_e_3(int n);

typedef double (*function_t)(int n);
void time_test(function_t function, const char *message, int n);

int main(void)
{
    printf("Calculate pi:\n");
    time_test(calc_pi_1, "Monte Carlo method", 1000);
    time_test(calc_pi_2, "Uniform sprinkling method", 1000);
    time_test(calc_pi_3, "Series summation", 1000);
    time_test(calc_pi_4, "Advanced series summation", 1000);
    printf("\n");

    printf("Calculate phi:\n");
    time_test(calc_phi_1, "Algebraic", 1000);
    time_test(calc_phi_2, "Fibonacci sequence", 1000);
    time_test(calc_phi_3, "Continued fraction", 1000);
    printf("\n");

    printf("Calculate e:\n");
    time_test(calc_e_1, "Definition", 1000);
    time_test(calc_e_2, "Series summation", 1000);
    time_test(calc_e_3, "Unknown advanced method", 1000);
    printf("\n");

    return 0;
}

double calc_pi_1(int n)
{
    int hits = 0;
    for (int i = 0; i < n; i++)
    {
        double x = (double)rand() / RAND_MAX;
        double y = (double)rand() / RAND_MAX;
        if (x * x + y * y < 1.0)
        {
            hits++;
        }
    }
    return (double)hits / n * 4;
}

double calc_pi_2(int n)
{
    int hits = 0;
    for (int x = 0; x * x < n; x++)
    {
        for (int y = 0; y * y < n; y++)
        {
            if (x * x + y * y < n)
            {
                hits++;
            }
        }
    }
    return (double)hits / n * 4;
}

double calc_pi_3(int n)
{
    double pi = 0, k = 1;
    for (int i = 0; i < n; i++)
    {
        pi += k / (2 * i + 1);
        k = -k;
    }
    return pi * 4;
}

double calc_pi_4(int n)
{
    double pi = 1, x = 1;
    for (int i = 1; i < n; i++)
    {
        x *= (double)i / (2 * i + 1);
        pi += x;
    }
    return pi * 2;
}

double calc_phi_1(int _)
{
    (void)_; // unused
    return (1 + sqrt(5)) / 2;
}

double calc_phi_2(int n)
{
    double t1 = 0, t2 = 1;
    for (int i = 0; i < n; ++i)
    {
        double next = t1 + t2;
        t1 = t2;
        t2 = next;
    }
    return t2 / t1;
}

double calc_phi_3(int n)
{
    return n == 0 ? 1.618 : 1 + 1 / calc_phi_3(n - 1);
}

double calc_e_1(int n)
{
    return pow(1 + 1.0 / n, n);
}

double calc_e_2(int n)
{
    double e = 1, x = 1;
    for (int i = 1; i < n; i++)
    {
        x *= 1.0 / i;
        e += x;
    }
    return e;
}

double calc_e_3(int n)
{
    int k = 0;
    n /= 2.718; // keep for loop count equals n as far as possible
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j <= RAND_MAX; j += rand())
        {
            k++;
        }
    }
    return (double)k / n;
}

void time_test(function_t function, const char *message, int n)
{
    struct timespec start, end;
    clock_gettime(CLOCK_MONOTONIC, &start);
    double result = function(n);
    clock_gettime(CLOCK_MONOTONIC, &end);
    time_t nanoseconds = end.tv_nsec - start.tv_nsec;

    printf("iteration: %d, result: %.14lf, duration: %5lld ns (%s)\n", n, result, nanoseconds, message);
}
