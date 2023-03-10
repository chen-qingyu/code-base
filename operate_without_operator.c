#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

int negative(const int a);              // -a
int plus(const int a, const int b);     // a + b
int minus(const int a, const int b);    // a - b
int multiply(const int a, const int b); // a * b
int divide(const int a, const int b);   // a / b

int main(void)
{
    assert(0 == negative(0));
    assert(1 == negative(-1));
    assert(-1 == negative(1));

    assert(0 == plus(0, 0));
    assert(1 == plus(0, 1));
    assert(1 == plus(1, 0));
    assert(2 == plus(1, 1));
    assert(-2 == plus(-1, -1));
    assert(0 == plus(1, -1));

    assert(0 == minus(0, 0));
    assert(-1 == minus(0, 1));
    assert(1 == minus(1, 0));
    assert(0 == minus(1, 1));
    assert(0 == minus(-1, -1));
    assert(2 == minus(1, -1));

    assert(0 == multiply(0, 0));
    assert(0 == multiply(0, 1));
    assert(0 == multiply(1, 0));
    assert(1 == multiply(1, 1));
    assert(1 == multiply(-1, -1));
    assert(-1 == multiply(1, -1));

    assert(0 == divide(0, 1));
    assert(1 == divide(1, 1));
    assert(1 == divide(-1, -1));
    assert(-1 == divide(1, -1));
    assert(0 == divide(1, 2));
    assert(2 == divide(2, 1));

    printf("Test OK.\n");

    return 0;
}

int plus(const int a, const int b)
{
    int x = a, y = b;
    while (y != 0)
    {
        int carry = (x & y) << 1;
        x = x ^ y;
        y = carry;
    }
    return x;
}

int minus(const int a, const int b)
{
    return plus(a, negative(b));
}

int multiply(const int a, const int b)
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

int divide(const int a, const int b)
{
    if (b == 0)
    {
        fprintf(stderr, "Error: divide by zero!\n");
        exit(EXIT_FAILURE);
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

int negative(const int a)
{
    return plus(~a, 1);
}
