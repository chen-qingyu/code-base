#include <math.h>  // sqrt()
#include <stdio.h> // printf()
#include <time.h>  // clock() clock_t CLOCKS_PER_SEC

double my_sqrt(const double x)
{
    if (x <= 0)
    {
        return (x < 0) ? NAN : 0;
    }

    double res = x;
    double tmp;
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

typedef double (*fn)(const double);

double test_time(fn func, double x)
{
    clock_t start, end;
    int loop = 1000000;

    start = clock();
    for (int i = 0; i < loop; ++i)
    {
        func(x);
    }
    end = clock();

    return (double)(end - start) / CLOCKS_PER_SEC;
}

int main(int argc, char const *argv[])
{
    printf("sqrt(): %.16lf\tmy_sqrt(): %.16lf\n", sqrt(-1), my_sqrt(-1));
    printf("sqrt(): %.16lf\tmy_sqrt(): %.16lf\n", sqrt(0), my_sqrt(0));
    printf("sqrt(): %.16lf\tmy_sqrt(): %.16lf\n", sqrt(0.01), my_sqrt(0.01));
    printf("sqrt(): %.16lf\tmy_sqrt(): %.16lf\n", sqrt(1), my_sqrt(1));
    printf("sqrt(): %.16lf\tmy_sqrt(): %.16lf\n", sqrt(2), my_sqrt(2));
    printf("sqrt(): %.16lf\tmy_sqrt(): %.16lf\n", sqrt(4), my_sqrt(4));
    printf("sqrt(): %.16lf\tmy_sqrt(): %.16lf\n", sqrt(100), my_sqrt(100));
    printf("sqrt(): %.16lf\tmy_sqrt(): %.16lf\n", sqrt(999999), my_sqrt(999999));
    printf("\n");

    // test time
    printf("test time\n");
    double time;

    time = test_time(sqrt, 100);
    printf("sqrt(): %lf (%.3lfs)\n", sqrt(100), time); // sqrt(): 10.000000 (0.004s)

    time = test_time(my_sqrt, 100);
    printf("my_sqrt(): %lf (%.3lfs)\n", my_sqrt(100), time); // my_sqrt(): 10.000000 (0.068s)

    time = test_time(sqrt, 1);
    printf("sqrt(): %lf (%.3lfs)\n", sqrt(1), time); // sqrt(): 1.000000 (0.003s)

    time = test_time(my_sqrt, 1);
    printf("my_sqrt(): %lf (%.3lfs)\n", my_sqrt(1), time); // my_sqrt(): 1.000000 (0.006s)

    time = test_time(sqrt, 999999);
    printf("sqrt(): %lf (%.3lfs)\n", sqrt(999999), time); // sqrt(): 999.999500 (0.004s)

    time = test_time(my_sqrt, 999999);
    printf("my_sqrt(): %lf (%.3lfs)\n", my_sqrt(999999), time); // my_sqrt(): 999.999500 (0.168s)

    return 0;
}
