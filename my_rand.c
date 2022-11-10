#include <stdio.h>  // printf()
#include <stdlib.h> // rand() RAND_MAX
#include <time.h>   // clock() clock_t CLOCKS_PER_SEC

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

// yield a pseudo-random number of [0, 1) use my_rand_gen()
double my_rand()
{
    static double seed = 0.0;
    return my_rand_gen(&seed);
}

// yield a pseudo-random number of [0, 1) use rand()
double std_rand()
{
    return (double)rand() / RAND_MAX;
}

typedef double (*fn)();

double test_time(fn func)
{
    clock_t start, end;
    int loop = 1000000;

    start = clock();
    for (int i = 0; i < loop; ++i)
    {
        func();
    }
    end = clock();

    return (double)(end - start) / CLOCKS_PER_SEC;
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

    // test time
    printf("test time\n");
    double time;

    time = test_time(std_rand);
    printf("std_rand(): %lf (%.3lfs)\n", std_rand(), time); // std_rand(): 0.652608 (0.016s)

    time = test_time(my_rand);
    printf("my_rand(): %lf (%.3lfs)\n", my_rand(), time); // my_rand(): 0.855469 (0.018s)

    return 0;
}
