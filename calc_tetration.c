#include <math.h>
#include <stdio.h>

int main(void)
{
    double x, tetration;
    x = sqrt(2);
    tetration = x;
    printf("The x: %lf\n\n", x);
    for (int i = 1; i < 10; ++i)
    {
        for (int j = 0; j < 10; ++j)
        {
            tetration = pow(x, tetration);
        }
        printf("%d0th tetration: %lf\n", i, tetration);
    }
    getchar();

    return 0;
}
