#include <stdio.h>

static inline double mod(const double x, const double m)
{
    return x - (int)(x / m) * m;
}

static inline double lcg(double* r)
{
    const static double m = 256, a = 17, c = 233;
    *r = mod(a * (*r) + c, m);
    return *r / m;
}

// yield a pseudo-random number of [0, 1) use Linear Congruential Generator
double my_rand()
{
    static double seed = 0.0;
    return lcg(&seed);
}

int main(void)
{
    printf("random numbers:\n");
    for (int i = 0; i < 10; i++)
    {
        printf("%.2lf ", my_rand());
    }

    return 0;
}
