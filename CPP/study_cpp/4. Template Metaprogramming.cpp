#include <iostream>

// 类型判断标识

struct number_tag
{
    static const bool is_number = true;
    static const bool is_boolean = false;
    static const bool is_symbol = false;
    static const bool is_pair = false;
    static const bool is_null = false;
};

struct boolean_tag
{
    static const bool is_number = false;
    static const bool is_boolean = true;
    static const bool is_symbol = false;
    static const bool is_pair = false;
    static const bool is_null = false;
};

struct pair_tag
{
    static const bool is_number = false;
    static const bool is_boolean = false;
    static const bool is_symbol = false;
    static const bool is_pair = true;
    static const bool is_null = false;
};

struct null_tag
{
    static const bool is_number = false;
    static const bool is_boolean = false;
    static const bool is_symbol = false;
    static const bool is_pair = false;
    static const bool is_null = true;
};

// 基本数据类型

template <int N, int D = 1>
struct number
{
    static const int num = N;
    static const int den = D;

    using tag = number_tag;
    using type = number<N, D>;
};

template <bool Flag>
struct boolean
{
    static const bool value = Flag;

    using tag = boolean_tag;
    using type = boolean<Flag>;
};

template <typename T, typename U>
struct pair
{
    using tag = pair_tag;
    using type = pair<T, U>;

    using fst_ = typename T::type;
    using snd_ = typename U::type;
};

struct null
{
    using tag = null_tag;
    using type = null;
};

// 组合数据类型

template <typename... T>
struct list;

template <typename T>
struct list<T> : public pair<T, null>
{
};

template <typename T, typename... X>
struct list<T, X...> : public pair<T, list<X...>>
{
};

// 基本操作函数

template <typename T>
using is_number = boolean<T::tag::is_number>;

template <typename T>
using is_boolean = boolean<T::tag::is_boolean>;

template <typename T>
using is_pair = boolean<T::tag::is_pair>;

template <typename T>
using is_null = boolean<T::tag::is_null>;

template <typename X>
struct fst
{
    using type = typename X::type::fst_;
    using tag = typename type::tag;
};

template <typename X>
struct snd
{
    using type = typename X::type::snd_;
    using tag = typename type::tag;
};

template <typename T, typename U>
struct cons : public pair<T, U>
{
};

// 流程控制

template <typename Flag, typename True, typename False>
struct if_else_impl : public True
{
};

template <typename True, typename False>
struct if_else_impl<boolean<false>, True, False> : public False
{
};

template <typename Flag, typename True, typename False>
struct if_else : public if_else_impl<typename Flag::type, True, False>
{
};

// 常用函数

template <typename a, typename b>
struct and_ : public boolean<(a::type::value && b::type::value)>
{
};

template <typename a, typename b>
struct or_ : public boolean<(a::type::value || b::type::value)>
{
};

template <typename a>
struct not_ : public boolean<(!a::type::value)>
{
};

namespace impl
{
template <int n0, int d0, int n1, int d1>
using add = number<n0 * d1 + n1 * d0, d0 * d1>;

template <int n0, int d0, int n1, int d1>
using sub = number<n0 * d1 - n1 * d0, d0 * d1>;

template <int n0, int d0, int n1, int d1>
using is_greater = boolean<(n0 * d1 > d0 * n1)>;

template <int n0, int d0, int n1, int d1>
using is_less = boolean<(n0 * d1 < d0 * n1)>;
}; // namespace impl

template <typename a, typename b>
struct add : public impl::add<a::type::num, a::type::den, b::type::num, b::type::den>
{
};

template <typename a, typename b>
struct sub : public impl::sub<a::type::num, a::type::den, b::type::num, b::type::den>
{
};

template <typename a, typename b>
struct mul : public number<a::type::num * b::type::num, a::type::den * b::type::den>
{
};

template <typename a, typename b>
struct div_ : public number<a::type::num * b::type::den, a::type::den * b::type::num>
{
};

template <typename a, typename b>
struct is_greater : public impl::is_greater<a::type::num, a::type::den, b::type::num, b::type::den>
{
};

template <typename a, typename b>
struct is_less : public impl::is_less<a::type::num, a::type::den, b::type::num, b::type::den>
{
};

template <typename a>
struct abs_ : public if_else<is_greater<a, number<0>>, a, number<-a::type::num, a::type::den>>
{
};

template <typename a, typename b, typename tagA, typename tagB>
struct is_equal_impl : public boolean<false>
{
};

template <typename a, typename b>
struct is_equal_impl<a, b, number_tag, number_tag> : public boolean<(a::type::num == b::type::num && a::type::den == b::type::den)>
{
};

template <typename a, typename b>
struct is_equal : public is_equal_impl<a, b, typename a::tag, typename b::tag>
{
};

template <typename a, typename b>
struct not_equal : public not_<is_equal<a, b>>
{
};

template <typename items>
struct length
{
    using type = typename if_else<is_null<items>,
                                  number<0>,
                                  add<number<1>, length<snd<items>>>>::type;
    using tag = typename type::tag;
};

template <typename items, typename n>
struct list_ref
{
    using type = typename if_else<is_equal<n, number<0>>,
                                  fst<items>,
                                  list_ref<snd<items>, sub<n, number<1>>>>::type;
    using tag = typename type::tag;
};

// 输入输出

template <typename T>
struct display_impl
{
    static std::ostream& display(std::ostream& os, number_tag)
    {
        if (T::type::den == 1)
        {
            return os << T::type::num;
        }
        else
        {
            return os << static_cast<double>(T::type::num) / static_cast<double>(T::type::den);
        }
    }

    static std::ostream& display(std::ostream& os, boolean_tag)
    {
        return os << (T::type::value == true ? "true" : "false");
    }

    static std::ostream& display(std::ostream& os, null_tag)
    {
        return os << "null";
    }

    static std::ostream& display(std::ostream& os, pair_tag)
    {
        os << "(";
        display_impl<fst<T>>::display(os);
        os << ", ";
        display_impl<snd<T>>::display(os);
        os << ")";
        return os;
    }

    static std::ostream& display(std::ostream& os)
    {
        return display(os, typename T::tag());
    }
};

template <typename T>
void display(std::ostream& os = std::cout)
{
    display_impl<T>::display(os) << std::endl;
};

int main(void)
{
    using my_list = list<number<0>, number<1, 10>, number<1>, number<2>, pair<number<233>, number<999>>, boolean<false>>;
    display<my_list>();
    return 0;
}
