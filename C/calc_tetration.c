#include <math.h>
#include <stdio.h>

int main(void)
{
    double x = sqrt(2);
    printf("The x: %lf\n\n", x);

    double tetration = x;
    for (int i = 0; i < 100; ++i)
    {
        if (i % 10 == 0)
        {
            printf("%dth tetration: %lf\n", i, tetration);
        }
        tetration = pow(x, tetration);
    }

    return 0;
}
