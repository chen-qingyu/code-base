#include <assert.h>
#include <stdbool.h>
#include <stdio.h>

bool is_prime(const int n) // assert n >= 0
{
    if (n == 0 || n == 1)
    {
        return false; // 0 and 1 is not prime
    }

    for (int i = 2; i * i <= n; i++)
    {
        if (n % i == 0)
        {
            return false;
        }
    }

    return true;
}

// 对n进行质因数分解，结果放在f数组里
void prime_factors(const int n, int f[])
{
    if (is_prime(n) || n == 0 || n == 1)
    {
        return; // 只分解合数
    }

    int x = n, k = 0;
    for (int i = 2; i * i <= x; i++)
    {
        while (x % i == 0)
        {
            f[k++] = i;
            x /= i;
        }
    }
    if (x != 0 && x != 1)
    {
        f[k++] = x;
    }
}

int main()
{
    assert(is_prime(0) == false);
    assert(is_prime(1) == false);
    assert(is_prime(2) == true);
    assert(is_prime(3) == true);
    assert(is_prime(4) == false);
    assert(is_prime(6) == false);
    assert(is_prime(12) == false);
    assert(is_prime(13) == true);
    assert(is_prime(100) == false);

    int f[5];
    prime_factors(0, f);   // []
    prime_factors(1, f);   // []
    prime_factors(2, f);   // []
    prime_factors(3, f);   // []
    prime_factors(4, f);   // [2, 2]
    prime_factors(6, f);   // [2, 3]
    prime_factors(12, f);  // [2, 2, 3]
    prime_factors(13, f);  // []
    prime_factors(100, f); // [2, 2, 5, 5]

    printf("Test OK.\n");

    return 0;
}
