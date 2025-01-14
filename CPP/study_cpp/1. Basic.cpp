#include <cmath>
#include <iostream>
#include <string>

using std::cin;
using std::cout;
using std::endl;
using std::string;

// 函数模板
template <typename T>
void print(T beginPtr, T endPtr)
{
    while (beginPtr != endPtr)
    {
        cout << *beginPtr;
        ++beginPtr;
    }
    cout << endl;
}

void test_1()
{
    int intArr[] = {1, 2, 3, 4, 5};
    char chrArr[] = {'a', 'b', 'c', 'd', 'e'};

    print(intArr, intArr + sizeof(intArr) / sizeof(int));
    print(chrArr, chrArr + sizeof(chrArr) / sizeof(char));
}

// 可修改字符串对象
void test_2()
{
    string str = "Hello World!";
    cout << str << endl;
    str[str.length() - 1] = '~';
    cout << str << endl;
}

// 构造与析构
class Super
{
public:
    Super(int id)
    {
        this->id = id;
        cout << "call Super(" << id << ")" << endl;
    }
    ~Super()
    {
        cout << "call ~Super() for " << id << endl;
    }
    virtual void hello() = 0;
    int getId()
    {
        return id;
    }

private:
    int id;
};

class Sub : public Super
{
public:
    Sub(int id, string name) : Super(id)
    {
        this->name = name;
        cout << "call Sub(" << id << ", " << name << ")" << endl;
    }
    ~Sub()
    {
        cout << "call ~Sub() for " << getId() << ", " << name << endl;
    }
    void hello()
    {
        cout << "#" << getId() << ": " << name << "\n";
    }

private:
    string name;
};

void test_3()
{
    Sub c(0, "CQY");
    c.hello();
    Sub *z = new Sub(1, "ZQ");
    z->hello();
    delete z;
}

// 运算符重载
class Complex
{
public:
    Complex()
    {
        real = 0;
        imag = 0;
    }

    Complex(int real, int imag)
    {
        this->real = real;
        this->imag = imag;
    }

    Complex add(const Complex &c)
    {
        return Complex(real + c.real, imag + c.imag);
    }

    Complex operator+(const Complex &c)
    {
        return Complex(real + c.real, imag + c.imag);
    }

    void print()
    {
        cout << real << "+" << imag << "i" << endl;
    }

private:
    int real;
    int imag;
};

void test_4()
{
    Complex v1(3, 4);
    Complex v2(5, 6);
    Complex v3(1, 1);
    Complex v4, v5;

    v4 = v1.add(v2).add(v3);
    v4.print();
    v5 = v1 + v2 + v3;
    v5.print();
}

// 运算符重载综合运用——分数类
class Rational
{
public:
    Rational(int num, int den)
    {
        if (den == 0)
        {
            throw std::runtime_error("Error: Zero denominator.");
        }

        this->num = num;
        this->den = den;
        normalize();
    }

    // a/b + c/d == (a*d+b*c) / b*d
    Rational operator+(Rational rhs)
    {
        normalize();
        return Rational(num * rhs.den + den * rhs.num, den * rhs.den);
    }

    Rational operator-(Rational rhs)
    {
        normalize();
        rhs.num = -rhs.num;
        return operator+(rhs);
    }

    Rational operator*(Rational rhs)
    {
        normalize();
        return Rational(num * rhs.num, den * rhs.den);
    }

    Rational operator/(Rational rhs)
    {
        normalize();
        int temp = rhs.num;
        rhs.num = rhs.den;
        rhs.den = temp;
        return operator*(rhs);
    }

private:
    // 1. 确保分母为正 2/-8 => -2/8
    // 2. 欧几里得算法 -2/8 => -1/4
    void normalize()
    {
        if (den < 0)
        {
            num = -num;
            den = -den;
        }

        int a = num > 0 ? num : -num;
        int b = den > 0 ? den : -den;

        // 求最大公约数 gcd(a, b) == gcd(b, a % b)
        while (b > 0)
        {
            int t = a % b;
            a = b;
            b = t;
        }

        num /= a;
        den /= a;
    }

    int num; // 分子
    int den; // 分母

    friend std::ostream &operator<<(std::ostream &os, Rational r);
};

std::ostream &operator<<(std::ostream &os, Rational r)
{
    r.normalize();
    if (r.num % r.den == 0)
    {
        os << r.num / r.den;
    }
    else
    {
        os << r.num << "/" << r.den;
    }
    return os;
}

void test_5()
{
    Rational val1(2, 16); // 2 / 16
    Rational val2(7, 8);  // 7 / 8
    cout << val1 << " + " << val2 << " = " << val1 + val2 << endl;

    Rational val3(0, 1);   // 0 / 1
    Rational val4(10, -5); // 10 / -5
    cout << val3 << " + " << val4 << " = " << val3 + val4 << endl;

    try
    {
        Rational val5(1, 0);  // 1 / 0
        Rational val6(1, 10); // 1 / 10
        cout << val5 << " + " << val6 << " = " << val5 + val6 << endl;
    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << '\n';
    }
}

// 动态数组
void test_6()
{
    int n;
    cout << "Please enter the length of the array: ";
    cin >> n;
    int *arr = new int[n];

    for (int i = 0; i < n; i++)
    {
        arr[i] = i;
    }

    for (int i = 0; i < n; i++)
    {
        cout << "arr[" << i << "]: " << arr[i] << endl;
    }

    delete[] arr;
}

// 野指针与空指针
void test_7()
{
    int *p = new int(255);
    cout << *p << endl;

    cout << p << endl; // 有效指针
    delete p;
    cout << p << endl; // 野指针
    p = NULL;
    cout << p << endl; // 空指针
}

// 引用
void swap(int &a, int &b)
{
    int tmp = a;
    a = b;
    b = tmp;
}

void test_8()
{
    int a = 1;
    int b = 2;
    cout << "Before swap: a = " << a << ", b = " << b << endl;
    swap(a, b);
    cout << "After swap: a = " << a << ", b = " << b << endl;
}

// string.c_str()
void test_9()
{
    string s = "hello";
    const char *ps = s.c_str();
    const char *ps2 = s.data();
    cout << "origin string: " << s << endl;
    cout << "origin c_str: " << ps << endl;
    cout << "origin data: " << ps2 << endl;

    s[0] = 'H';
    s += "!";
    cout << "modified string: " << s << endl;
    cout << "origin c_str: " << ps << endl;
    cout << "origin data: " << ps2 << endl;
}

// 哇
void test_10()
{
    cout << int() << endl;
    cout << double() << endl;
    cout << char() << endl;
    cout << string() << endl;
}

int main()
{
    // test_1(); // 函数模板
    // test_2(); // 可修改字符串对象
    // test_3(); // 构造与析构
    // test_4(); // 运算符重载
    // test_5(); // 运算符重载综合运用——分数类
    // test_6(); // 动态数组
    // test_7(); // 野指针与空指针
    // test_8(); // 引用
    // test_9(); // string.c_str()
    // test_10(); // 哇

    return 0;
}
