#include <stdio.h>

double my_mod(const double x, const double m)
{
    return x - (int)(x / m) * m;
}

double my_rand_gen(double *r)
{
    const static double m = 256, a = 17, c = 233;
    *r = my_mod(a * (*r) + c, m);
    return *r / m;
}

// yield 0-1 random number
double my_rand()
{
    static double seed = 0.5;
    return my_rand_gen(&seed);
}

int main(void)
{
    printf("print 50 random numbers:\n");
    for (int i = 1; i <= 50; i++)
    {
        printf("%.2lf ", my_rand());
        if (i % 10 == 0)
        {
            printf("\n");
        }
    }
    return 0;
}
