#include <stdio.h>

unsigned int gcd(unsigned int a, unsigned int b)
{
    if (a < b) // let a >= b
    {
        unsigned int t = a;
        a = b;
        b = t;
    }

    while (b != 0) // a, b = b, a % b until b == 0
    {
        unsigned int t = b;
        b = a % b;
        a = t;
    }

    return a; // a is GCD
}

int main(void)
{
    unsigned int a, b;
    printf("Please input two positive integers: ");
    scanf("%u %u", &a, &b);

    unsigned int gcd_value = gcd(a, b);
    printf("GCD: %u\nLCM: %u\n", gcd_value, (a * b) / gcd_value); // LCM = (a * b) / GCD

    return 0;
}
