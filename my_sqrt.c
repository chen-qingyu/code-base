#include <math.h>  // sqrtf()
#include <stdio.h> // printf()
#include <time.h>  // clock() clock_t CLOCKS_PER_SEC

float my_sqrt(const float x)
{
    if (x <= 0)
    {
        return (x < 0) ? NAN : 0;
    }

    float res = x;
    float tmp;
    while (1)
    {
        tmp = (res + x / res) / 2; // Newton Iterative Method

        if (tmp == res) // for speed and accuracy
        {
            return res;
        }
        res = tmp;
    }

    return -1; // normally unreachable
}

float fast_sqrt(const float x)
{
    if (x <= 0)
    {
        return (x < 0) ? NAN : 0;
    }

    unsigned int bits = 0;
    bits = *((int*)&x);
    bits = (bits >> 1) + 0x1fbb4f2e;
    return *((float*)&bits);
}

typedef float (*fn)(const float);

float test_time(fn func, float x)
{
    clock_t start, end;
    int loop = 1000000;

    start = clock();
    for (int i = 0; i < loop; ++i)
    {
        func(x);
    }
    end = clock();

    return (float)(end - start) / CLOCKS_PER_SEC;
}

int main(int argc, char const* argv[])
{
    printf("sqrtf(): %9.5f\tmy_sqrt(): %9.5f\tfast_sqrt(): %9.5f\n", sqrtf(-1), my_sqrt(-1), fast_sqrt(-1));
    printf("sqrtf(): %9.5f\tmy_sqrt(): %9.5f\tfast_sqrt(): %9.5f\n", sqrtf(0), my_sqrt(0), fast_sqrt(0));
    printf("sqrtf(): %9.5f\tmy_sqrt(): %9.5f\tfast_sqrt(): %9.5f\n", sqrtf(0.01), my_sqrt(0.01), fast_sqrt(0.01));
    printf("sqrtf(): %9.5f\tmy_sqrt(): %9.5f\tfast_sqrt(): %9.5f\n", sqrtf(1), my_sqrt(1), fast_sqrt(1));
    printf("sqrtf(): %9.5f\tmy_sqrt(): %9.5f\tfast_sqrt(): %9.5f\n", sqrtf(2), my_sqrt(2), fast_sqrt(2));
    printf("sqrtf(): %9.5f\tmy_sqrt(): %9.5f\tfast_sqrt(): %9.5f\n", sqrtf(4), my_sqrt(4), fast_sqrt(4));
    printf("sqrtf(): %9.5f\tmy_sqrt(): %9.5f\tfast_sqrt(): %9.5f\n", sqrtf(100), my_sqrt(100), fast_sqrt(100));
    printf("sqrtf(): %9.5f\tmy_sqrt(): %9.5f\tfast_sqrt(): %9.5f\n", sqrtf(999999), my_sqrt(999999), fast_sqrt(999999));
    printf("\n");

    printf("sqrtf(): %f (%.3fs)\n", sqrtf(100), test_time(sqrtf, 100));
    printf("my_sqrt(): %f (%.3fs)\n", my_sqrt(100), test_time(my_sqrt, 100));
    printf("fast_sqrt(): %f (%.3fs)\n", fast_sqrt(100), test_time(fast_sqrt, 100));
    printf("\n");

    printf("sqrtf(): %f (%.3fs)\n", sqrtf(1), test_time(sqrtf, 1));
    printf("my_sqrt(): %f (%.3fs)\n", my_sqrt(1), test_time(my_sqrt, 1));
    printf("fast_sqrt(): %f (%.3fs)\n", fast_sqrt(1), test_time(fast_sqrt, 1));
    printf("\n");

    printf("sqrtf(): %f (%.3fs)\n", sqrtf(999999), test_time(sqrtf, 999999));
    printf("my_sqrt(): %f (%.3fs)\n", my_sqrt(999999), test_time(my_sqrt, 999999));
    printf("fast_sqrt(): %f (%.3fs)\n", fast_sqrt(999999), test_time(fast_sqrt, 999999));
    printf("\n");

    // sqrtf():  -1.#IND0      my_sqrt():   1.#QNAN    fast_sqrt():   1.#QNAN
    // sqrtf():   0.00000      my_sqrt():   0.00000    fast_sqrt():   0.00000
    // sqrtf():   0.10000      my_sqrt():   0.10000    fast_sqrt():   0.10021
    // sqrtf():   1.00000      my_sqrt():   1.00000    fast_sqrt():   0.98168
    // sqrtf():   1.41421      my_sqrt():   1.41421    fast_sqrt():   1.46335
    // sqrtf():   2.00000      my_sqrt():   2.00000    fast_sqrt():   1.96335
    // sqrtf():  10.00000      my_sqrt():  10.00000    fast_sqrt():   9.95683
    // sqrtf(): 999.99951      my_sqrt(): 999.99951    fast_sqrt(): 981.51794

    // sqrtf(): 10.000000 (0.003s)
    // my_sqrt(): 10.000000 (0.059s)
    // fast_sqrt(): 9.956831 (0.003s)

    // sqrtf(): 1.000000 (0.003s)
    // my_sqrt(): 1.000000 (0.010s)
    // fast_sqrt(): 0.981677 (0.003s)

    // sqrtf(): 999.999512 (0.003s)
    // my_sqrt(): 999.999512 (0.134s)
    // fast_sqrt(): 981.517944 (0.003s)

    return 0;
}
