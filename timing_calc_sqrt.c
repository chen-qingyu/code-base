#include <math.h>
#include <stdio.h>
#include <time.h>

float calc_sqrt_1(float x);
float calc_sqrt_2(float x);
float calc_sqrt_3(float x);

typedef float (*function_t)(float x);
void time_test(function_t function, const char* message, float x);

int main(int argc, char const* argv[])
{
    float xs[] = {-1, 0, 1, 2, 100, 999999};
    for (int i = 0; i < sizeof(xs) / sizeof(float); i++)
    {
        printf("sqrt(%.1f):\n", xs[i]);
        time_test(calc_sqrt_1, "Newton's method", xs[i]);
        time_test(calc_sqrt_2, "Magic number", xs[i]);
        time_test(calc_sqrt_3, "Standard library", xs[i]);
        printf("\n");
    }

    return 0;
}

float calc_sqrt_1(float x)
{
    if (x <= 0)
    {
        return (x < 0) ? NAN : 0;
    }

    float res = x;
    float tmp;
    while (1)
    {
        tmp = (res + x / res) / 2;

        if (tmp == res) // for speed and accuracy
        {
            return res;
        }
        res = tmp;
    }

    return -1; // unreachable
}

float calc_sqrt_2(float x)
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

float calc_sqrt_3(float x)
{
    return sqrtf(x);
}

void time_test(function_t function, const char* message, float x)
{
    float result;

    clock_t start = clock();
    for (int i = 0; i < 1000000; i++)
    {
        result = function(x);
    }
    clock_t end = clock();

    printf("result: %f, duration: %6.2lfms (%s)\n", result, (double)(end - start) / CLOCKS_PER_SEC * 1000, message);
}
