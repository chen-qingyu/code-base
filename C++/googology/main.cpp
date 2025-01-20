#include <boost/multiprecision/cpp_int.hpp>
#include <iostream>
#include <pyincpp.hpp>

using boost::multiprecision::cpp_int;
using pyincpp::Int;

// same algorithm with pyincpp::Int::pow()
cpp_int fastpow(const cpp_int& base, const cpp_int& exp)
{
    cpp_int b(base), e(exp), p(1);
    while (!e.is_zero())
    {
        if (e & 1 == 1)
        {
            p *= b;
        }
        b *= b;
        e /= 2;
    }
    return p;
}

// same algorithm with pyincpp::Int::ackermann()
cpp_int ackermann(const cpp_int& m, const cpp_int& n)
{
    switch (m.convert_to<int>())
    {
        case 0:
            return n + 1;
        case 1:
            return n + 2;
        case 2:
            return n * 2 + 3;
        case 3:
            return fastpow(2, n + 3) - 3;
        default:
            return n == 0 ? ackermann(m - 1, 1) : ackermann(m - 1, ackermann(m, n - 1));
    }
}

int main()
{
    cpp_int x = ackermann(4, 2);
    std::cout << "A(4, 2) = " << x << " (" << x.str().size() << " digits)\n";
    // (19729 digits)

    Int y = Int::ackermann(4, 2);
    std::cout << "A(4, 2) = " << y << " (" << y.digits() << " digits)\n";
    // (19729 digits)

    x = fastpow(7, 823543);
    std::cout << "7^^3 = " << x << " (" << x.str().size() << " digits)\n";
    // (695975 digits) ~15s, calc faster, output slower

    y = Int::pow(7, 823543);
    std::cout << "7^^3 = " << y << " (" << y.digits() << " digits)\n";
    // (695975 digits) ~12s, calc slower, output faster
}
