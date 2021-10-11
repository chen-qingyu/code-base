#include <stdio.h>

int plus(int a, int b);  // a + b
int minus(int a, int b); // a - b
int mult(int a, int b);  // a * b
int div(int a, int b);   // a / b

static int negative(int a); // -a

int main(void)
{
    int test_data[] = {1, 1, 0, -1, 0, 1, 3, 5, 4, 2};
    int test_data_size = sizeof(test_data) / sizeof(test_data[0]);

    printf("\ntest plus:\n");
    for (int i = 1; i < test_data_size; ++i)
    {
        printf("%d + %d = %d\n", test_data[i - 1], test_data[i], plus(test_data[i - 1], test_data[i]));
    }
    printf("\ntest minus:\n");
    for (int i = 1; i < test_data_size; ++i)
    {
        printf("%d - %d = %d\n", test_data[i - 1], test_data[i], minus(test_data[i - 1], test_data[i]));
    }
    printf("\ntest mult:\n");
    for (int i = 1; i < test_data_size; ++i)
    {
        printf("%d * %d = %d\n", test_data[i - 1], test_data[i], mult(test_data[i - 1], test_data[i]));
    }
    printf("\ntest div:\n");
    for (int i = 1; i < test_data_size; ++i)
    {
        printf("%d / %d = %d\n", test_data[i - 1], test_data[i], div(test_data[i - 1], test_data[i]));
    }

    return 0;
}

int plus(int a, int b)
{
    while (b != 0)
    {
        int carry = (a & b) << 1;
        a = a ^ b;
        b = carry;
    }
    return a;
}

int minus(int a, int b)
{
    return plus(a, negative(b));
}

int mult(int a, int b)
{
    int x = a < 0 ? negative(a) : a;
    int y = b < 0 ? negative(b) : b;
    int res = 0;
    while (y != 0)
    {
        if ((y & 1) == 1)
        {
            res = plus(res, x);
        }
        x <<= 1;
        y >>= 1;
    }
    return (a ^ b) >= 0 ? res : negative(res);
}

int div(int a, int b)
{
    if (b == 0)
    {
        printf("Error: divide by zero!\n");
        return -1;
    }
    int x = a < 0 ? negative(a) : a;
    int y = b < 0 ? negative(b) : b;
    int result = 0;
    for (int i = 31; i >= 0; i--)
    {
        if ((x >> i) >= y)
        {
            result = plus(result, 1 << i);
            x = minus(x, y << i);
        }
    }
    return (a ^ b) >= 0 ? result : -result;
}

static int negative(int a)
{
    return plus(~a, 1);
}
