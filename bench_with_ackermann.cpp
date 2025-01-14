#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/catch_test_macros.hpp>

#include "../sources/pyincpp.hpp"
#include <boost/multiprecision/cpp_int.hpp>

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

TEST_CASE("bench boost with Ackermann function", "[ack]")
{
    REQUIRE(pyincpp::Int::ackermann(2, 1'000'000'000).digits() == 10);
    BENCHMARK(std::format("mul ({})", typeid(pyincpp::Int).name()))
    {
        return pyincpp::Int::ackermann(2, 1'000'000'000);
    };
    REQUIRE(ackermann(2, 1'000'000'000).str().size() == 10);
    BENCHMARK(std::format("mul ({})", typeid(cpp_int).name()))
    {
        return ackermann(2, 1'000'000'000);
    };

    REQUIRE(pyincpp::Int::ackermann(3, 10000).digits() == 3012);
    BENCHMARK(std::format("pow ({})", typeid(pyincpp::Int).name()))
    {
        return pyincpp::Int::ackermann(3, 10000);
    };
    REQUIRE(ackermann(3, 10000).str().size() == 3012);
    BENCHMARK(std::format("pow ({})", typeid(cpp_int).name()))
    {
        return ackermann(3, 10000);
    };

    REQUIRE(pyincpp::Int::ackermann(4, 2).digits() == 19729);
    BENCHMARK(std::format("tetration ({})", typeid(pyincpp::Int).name()))
    {
        return pyincpp::Int::ackermann(4, 2);
    };
    REQUIRE(ackermann(4, 2).str().size() == 19729);
    BENCHMARK(std::format("tetration ({})", typeid(cpp_int).name()))
    {
        return ackermann(4, 2);
    };
}

/*
`xmake config -m release && xmake build bench && xmake run bench --benchmark-no-analysis -i [ack]`

-------------------------------------------------------------------------------
bench boost with Ackermann function
-------------------------------------------------------------------------------
benches\bench_with_ackermann.cpp(44)
...............................................................................

benchmark name                            samples    iterations          mean
-------------------------------------------------------------------------------
mul (class pyincpp::Int)                       100            22      865.5 ns
mul (class boost::multiprecision::
number<struct boost::
multiprecision::backends::
cpp_int_backend<0,0,1,0,class std::
allocator<unsigned long> >,1>)                 100           644    28.6242 ns
pow (class pyincpp::Int)                       100             1    410.969 us
pow (class boost::multiprecision::
number<struct boost::
multiprecision::backends::
cpp_int_backend<0,0,1,0,class std::
allocator<unsigned long> >,1>)                 100             1     26.747 us
tetration (class pyincpp::Int)                 100             1    21.8918 ms
tetration (class boost::
multiprecision::number<struct
boost::multiprecision::backends::
cpp_int_backend<0,0,1,0,class std::
allocator<unsigned long> >,1>)                 100             1    210.056 us

===============================================================================
*/
