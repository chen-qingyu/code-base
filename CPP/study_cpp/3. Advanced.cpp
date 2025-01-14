#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <list>
#include <memory>
#include <string>
#include <typeinfo>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::list;
using std::make_unique;
using std::string;
using std::unique_ptr;
using std::vector;

#if 0 // 加快编译速度

// 多态
class A
{
public:
    void print()
    {
        cout << "A" << endl;
    }
    virtual void vprint()
    {
        cout << "virtual A" << endl;
    }
};

class B : public A
{
public:
    void print()
    {
        cout << "B" << endl;
    }
    virtual void vprint()
    {
        cout << "virtual B" << endl;
    }
};

class C : public B
{
public:
    void print()
    {
        cout << "C" << endl;
    }
    virtual void vprint()
    {
        cout << "virtual C" << endl;
    }
};

class D : public A
{
public:
    void print()
    {
        cout << "D" << endl;
    }
    virtual void vprint()
    {
        cout << "virtual D" << endl;
    }
};

void test_1()
{
    A a;
    B b;
    C c;
    D d;

    A *pa = &a;
    pa->print();
    pa->vprint();
    pa = &b;
    pa->print();
    pa->vprint();
    pa = &c;
    pa->print();
    pa->vprint();
    pa = &d;
    pa->print();
    pa->vprint();
}

// 经典模板
template <class T, class F>
void map(T start, T end, F func)
{
    for (; start != end; ++start)
    {
        *start = func(*start);
    }
}

int cube(int x)
{
    return x * x * x;
}

string wow(string s)
{
    return (s += "!");
}

void test_2()
{
    int a[5] = {1, 2, 3, 4, 5};
    string b[3] = {"hello", "yeah", "wow"};

    for (const auto &i : a)
    {
        cout << i << " ";
    }
    cout << " | ";
    for (const auto &s : b)
    {
        cout << s << " ";
    }
    cout << endl;

    map(a, a + 5, cube);
    map(b, b + 3, wow);

    for (const auto &i : a)
    {
        cout << i << " ";
    }
    cout << " | ";
    for (const auto &s : b)
    {
        cout << s << " ";
    }
    cout << endl;
}

// 子类初始化构造探析
class Base
{
protected:
    int a;

public:
    Base() : a(1) { cout << "Base construct default " << a << endl; };
    Base(int _a) : a(_a) { cout << "Base construct " << a << endl; };
    ~Base() { cout << "Base deconstruct " << a << endl; }
};
class Derive : Base
{
    int b;

public:
    Derive() : b(2) { cout << "Derive construct default " << b << endl; };
    Derive(int _a, int _b) : Base(_a), b(_b) { cout << "Derive construct " << b << endl; };
    ~Derive() { cout << "Derive deconstruct " << b << endl; }
};

void test_3()
{
    Derive a;
    Derive b(3, 4);
}

// CPU流水线加速
void test_4()
{
    // 生成数据
    const int SIZE = 32768;
    int a[SIZE], b[SIZE];
    for (int i = 0; i < SIZE; ++i)
    {
        a[i] = b[i] = std::rand() % 256;
    }
    clock_t start, end;
    const int LOOP = 5000;
    printf("LOOP: %d\n", LOOP);

    // 未排序
    start = clock();
    for (int l = 0; l < LOOP; l++)
    {
        long long sum_a = 0;
        for (int i = 0; i < SIZE; i++)
        {
            if (a[i] > 127)
            {
                sum_a += a[i];
            }
        }
    }
    end = clock();
    cout << "Time consumed in unsorted summation: " << (double)(end - start) / CLOCKS_PER_SEC << "s" << endl; // 1.05s

    // 排序后
    start = clock();
    std::sort(b, b + SIZE);
    for (int l = 0; l < LOOP; l++)
    {
        long long sum_b = 0;
        for (int i = 0; i < SIZE; ++i)
        {
            if (b[i] > 127)
            {
                sum_b += b[i];
            }
        }
    }
    end = clock();
    cout << "Time consumed in sorting and sorted summation: " << (double)(end - start) / CLOCKS_PER_SEC << "s" << endl; // 0.35s

    /*
    随机+循环+条件就利用了CPU流水线的动态预测机制。
    数组排序后，动态分支预测结合之前的结果做出判断准确率非常高，而未排序时完全随机和静态分支预测差不多了，因此准确率一般。
    分支预测失败就意味着流水线排空，废弃已经进行IF和ID的指令，然后再选择正确的指令，整个过程在目前CPU来说要来浪费10-20个时钟周期，这样耗时就上来了。
    */
}

// 拷贝构造
class TestA
{
public:
    int a;
    TestA(int _a = 10) : a(_a){};
};

class TestB : public TestA
{
public:
    int &b = a;
    TestB &operator=(const TestB &rhs)
    {
        a = rhs.a;
        return *this;
    }
};

void test_5()
{
    TestB o1, o2;
    cout << o1.a << " " << o1.b << endl;
    o1.a = 233;
    cout << o1.a << " " << o1.b << endl;
    cout << endl;

    o1.a = 999;
    o2 = o1;
    o2 = o2;
    cout << o2.a << " " << o2.b << endl;
    cout << endl;

    o1.b = 1024;
    o1 = o1;
    o2 = o1;
    o2 = o2;
    cout << o2.a << " " << o2.b << endl;
    cout << endl;
}

// type

class TESTCLASS
{
};

void test_6()
{
    int a = 1;
    double b = 1.5;
    decltype(a) aa = 2;
    decltype(b) bb = 2.5;
    double c = 3.5;
    decltype((c)) d = c; // 引用
    decltype(c) &e = c;  // 引用
    cout << d << " " << e << endl;
    c = 9.9;
    cout << d << " " << e << endl;
    cout << endl;

    decltype(a) *pa = &a;
    decltype(b) *pb = &b;
    auto pclass1 = new TESTCLASS();
    auto *pclass2 = new TESTCLASS();
    cout << typeid(aa).name() << endl;
    cout << typeid(bb).name() << endl;
    cout << typeid(d).name() << endl;
    cout << typeid(e).name() << endl;
    cout << typeid(pa).name() << endl;
    cout << typeid(pb).name() << endl;
    cout << endl;
    cout << typeid(typeid(pa).name()).name() << endl;
    cout << typeid("").name() << endl;
    cout << typeid("1").name() << endl;
    cout << typeid("12").name() << endl;
    cout << typeid("123").name() << endl;
    cout << typeid('\0').name() << endl;
    cout << typeid('*').name() << endl;
    cout << typeid(string()).name() << endl;
    cout << typeid(string("*")).name() << endl;
    cout << typeid(vector<int>()).name() << endl;
    cout << typeid(vector<int>{1, 2, 3}).name() << endl;
    cout << typeid(TESTCLASS).name() << endl;
    cout << typeid(TESTCLASS()).name() << endl;
    cout << typeid(pclass1).name() << endl;
    cout << typeid(pclass2).name() << endl;
    /*
g++:
    i
    d
    d
    d
    Pi
    Pd

    PKc
    A1_c
    A2_c
    A3_c
    A4_c
    c
    c
    FNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEEvE
    NSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE
    FSt6vectorIiSaIiEEvE
    St6vectorIiSaIiEE
    9TESTCLASS
    F9TESTCLASSvE
    P9TESTCLASS
    P9TESTCLASS

VS2019:
    int
    double
    double
    double
    int *
    double *

    char const *
    char const [1]
    char const [2]
    char const [3]
    char const [4]
    char
    char
    class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> > __cdecl(void)
    class std::basic_string<char,struct std::char_traits<char>,class std::allocator<char> >
    class std::vector<int,class std::allocator<int> > __cdecl(void)
    class std::vector<int,class std::allocator<int> >
    class TESTCLASS
    class TESTCLASS __cdecl(void)
    class TESTCLASS *
    class TESTCLASS *
    */
}

// template myfind
template <typename InputIt, typename T>
InputIt myfind(InputIt begin, InputIt end, const T &value)
{
    for (; begin != end; ++begin)
    {
        if (*begin == value)
        {
            return begin;
        }
    }
    return end;
}

void test_7()
{
    vector<int> vi = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    list<string> ls = {"hello", "world", "!"};

    int tofindi = 4;
    if (myfind(vi.begin(), vi.end(), tofindi) != vi.end())
    {
        cout << tofindi << " found!" << endl;
    }
    else
    {
        cout << tofindi << " not found!" << endl;
    }

    string tofinds = "hi";
    if (myfind(ls.begin(), ls.end(), tofinds) != ls.end())
    {
        cout << tofinds << " found!" << endl;
    }
    else
    {
        cout << tofinds << " not found!" << endl;
    }

    tofinds = "!";
    if (myfind(ls.begin(), ls.end(), tofinds) != ls.end())
    {
        cout << tofinds << " found!" << endl;
    }
    else
    {
        cout << tofinds << " not found!" << endl;
    }
}

#endif

// unique_ptr
class Demo
{
private:
    int i;

public:
    Demo(int i) : i(i) { cout << "Demo(" << i << ") constructed." << endl; }
    ~Demo() { cout << "Demo(" << i << ") destructed." << endl; }
    void print() { cout << "Demo(" << i << ")::print()" << endl; }
};

void test_8()
{
    // unique_ptr<Demo> ptr1(new Demo()); // Old
    auto ptr1 = make_unique<Demo>(1); // std::unique_ptr<Demo, std::default_delete<Demo>> ptr1
    ptr1->print();
    cout << ptr1.get() << endl;

    auto ptr2 = std::move(ptr1);
    ptr2->print();
    cout << ptr1.get() << "\t" << ptr2.get() << endl;

    auto ptr3 = ptr2.release(); // Demo *ptr3
    ptr3->print();
    cout << ptr1.get() << "\t" << ptr2.get() << "\t" << ptr3 << endl;

    auto ptr4 = unique_ptr<Demo>(ptr3);
    ptr4->print();
    cout << ptr1.get() << "\t" << ptr2.get() << "\t" << ptr3 << "\t" << ptr4.get() << endl;

    auto ptr5 = make_unique<Demo>(2); // std::unique_ptr<Demo, std::default_delete<Demo>> ptr5
    ptr5->print();
    cout << ptr1.get() << "\t" << ptr2.get() << "\t" << ptr3 << "\t" << ptr4.get() << "\t" << ptr5.get() << endl;

    ptr5.swap(ptr4);
    cout << "after ptr5.swap(ptr4):" << endl;
    cout << ptr1.get() << "\t" << ptr2.get() << "\t" << ptr3 << "\t" << ptr4.get() << "\t" << ptr5.get() << endl;

    ptr4.reset();
    cout << "after ptr4.reset():" << endl;
    cout << ptr1.get() << "\t" << ptr2.get() << "\t" << ptr3 << "\t" << ptr4.get() << "\t" << ptr5.get() << endl;

    // ptr5 deletes its stored pointer when it goes out of scope.
}

int main(int argc, char const *argv[])
{
    // test_1(); // 多态
    // test_2(); // 经典模板
    // test_3(); // 子类初始化构造探析
    // test_4(); // CPU流水线加速
    // test_5(); // 拷贝构造
    // test_6(); // type
    // test_7(); // template myfind
    test_8(); // unique_ptr

    return 0;
}
