#include <algorithm>
#include <cfloat>
#include <cmath>
#include <iostream>
#include <iterator>
#include <list>
#include <map>
#include <numeric>
#include <set>
#include <stack>
#include <string>
#include <vector>

using std::cin;
using std::cout;
using std::endl;
using std::list;
using std::map;
using std::set;
using std::string;
using std::vector;

template <typename T>
void print(const T &con)
{
    for (const auto &ele : con)
    {
        cout << ele << " ";
    }
    cout << endl;
}

#if 0 // 加快编译速度

// 顺序容器的基本操作
void test_1()
{
    vector<string> sv{"hello", "world"};          // size = 2 列表初始化
    sv.insert(sv.begin(), "###");                 // size = 3 等价于 push_front
    sv.insert(sv.end(), 3, "~");                  // size = 6 等价于连续 3 次 push_back
    sv.insert(sv.end(), {"one", "two", "three"}); // size = 9 范围插入
    sv.front() = "!!!";                           // size = 9 访问返回的是引用
    sv.erase(sv.end() - 2, sv.end());             // size = 7 删除最后两个元素

    for (string s : sv)
    {
        cout << s << endl;
    }
    cout << "sv.size: " << sv.size() << endl;
}

// vector的增长
void test_2()
{
    vector<int> iv;
    cout << "create an empty vector<int>..." << endl;
    cout << "size: " << iv.size() << ", capacity: " << iv.capacity() << endl;

    for (int i = 0; i < 20; ++i)
    {
        cout << "push_back..." << endl;
        iv.push_back(i);
        cout << "size: " << iv.size() << ", capacity: " << iv.capacity() << endl;
    }

    cout << "reserve: 50..." << endl;
    iv.reserve(50);
    cout << "size: " << iv.size() << ", capacity: " << iv.capacity() << endl;

    cout << "fill the vector..." << endl;
    while (iv.size() != iv.capacity())
    {
        iv.push_back(0);
    }
    cout << "size: " << iv.size() << ", capacity: " << iv.capacity() << endl;

    cout << "push_back..." << endl;
    iv.push_back(42);
    cout << "size: " << iv.size() << ", capacity: " << iv.capacity() << endl;
}

// string探析
void test_3()
{
    string s("Hello World~");
    s = s.substr(0, s.size() - 1); // 截取子串
    s.append("!");                 // s += "!"
    s.replace(6, 5, "CPP");        // 从[6]开始，删除五个字符，插入"CPP"
    cout << s << endl;
    cout << "-----------" << endl;

    auto idx = s.find("CPP");
    cout << idx << endl;
    idx = s.find("NOT");
    cout << ((idx == string::npos) ? "not found" : "found") << endl;
    cout << "-----------" << endl;

    cout << s.compare("Hello CPP!") << endl;
    cout << "-----------" << endl;

    s = "pi = 3.14";
    double pi;
    pi = std::stod(s.substr(s.find_first_of("+-.0123456789")));
    cout << pi << endl;
    cout << "-----------" << endl;
}

// 适配器
void test_4()
{
    std::stack<int>::container_type id; // deque
    id.push_front(1);
    id.push_front(2);
    id.push_front(3);
    std::stack<int> is;
    is.push(1);
    is.push(2);
    is.push(3);

    for (int i : id)
    {
        cout << i << endl;
    }
    cout << "--------" << endl;
    for (int i = 0; i < 3; ++i)
    {
        cout << is.top() << endl;
        is.pop();
    }
}

// 泛型只读算法
void test_5()
{
    vector<int> iv{1, 2, 3, 4, 5, 4, 3, 2, 1, 0, 1};
    cout << std::count(iv.cbegin(), iv.cend(), 1) << endl; // 1出现了3次
    cout << *std::find(iv.cbegin(), iv.cend(), 5) << endl; // find返回迭代器
    cout << (std::find(iv.cbegin(), iv.cend(), 10) == iv.cend() ? "not found" : "found") << endl;
    cout << std::accumulate(iv.cbegin(), iv.cend(), 0) << endl; // 累加求和

    cout << "--------" << endl;

    list<string> sl{"a", "b", "c", "a"};
    cout << std::count(sl.cbegin(), sl.cend(), "a") << endl;             // "a"出现了2次
    cout << std::accumulate(sl.cbegin(), sl.cend(), string("")) << endl; // 第三个参数决定类型

    cout << "--------" << endl;

    vector<double> dv{1.1, 2.2, 3.3};
    cout << std::accumulate(dv.cbegin(), dv.cend(), 0) << endl;   // 6
    cout << std::accumulate(dv.cbegin(), dv.cend(), 0.0) << endl; // 6.6

    cout << "--------" << endl;

    vector<const char *> ccv{"a", "bb"};
    list<const char *> ccl{"a", "bb", "ccc"};
    const char tmp[] = {'c', 'c', 'c', '\0'};
    ccv.push_back(tmp);
    cout << ("ccc" == tmp) << endl;                                     // false
    cout << (string("ccc") == tmp) << endl;                             // true
    cout << std::equal(ccv.cbegin(), ccv.cend(), ccl.cbegin()) << endl; // false 但其实内容是相等的
    for (const char *t : ccv)
    {
        cout << t << endl;
    }
    for (const char *t : ccl)
    {
        cout << t << endl;
    }
}

// 泛型写入算法
void test_6()
{
    cout << "origin vector:" << endl;
    vector<int> iv{1, 2, 3, 4, 5, 4, 3, 2, 1, 0, 1};
    print(iv);

    cout << "after fill:" << endl;
    std::fill(iv.begin(), iv.end(), 42);
    print(iv);

    cout << "after replace:" << endl;
    std::replace(iv.begin(), iv.end(), 42, 0);
    print(iv);
}

// 泛型排序算法
void test_7()
{
    cout << "origin vector:" << endl;
    vector<int> iv{1, 2, 3, 4, 5, 4, 3, 2, 1, 0, 1};
    print(iv);

    cout << "after sort:" << endl;
    std::sort(iv.begin(), iv.end());
    print(iv);

    cout << "after unique & erase:" << endl;
    auto to_erase = std::unique(iv.begin(), iv.end());
    iv.erase(to_erase, iv.end()); // erase不是泛型算法，而是容器操作，这里只是为了演示去重
    print(iv);
}

// 定制操作
bool isShorter(const string &s1, const string &s2)
{
    return s1.size() < s2.size();
}

void test_8()
{
    cout << "origin vector:" << endl;
    vector<string> sv{"bb", "aaa", "c", "-"};
    print(sv);

    cout << "after sort:" << endl;
    std::sort(sv.begin(), sv.end());
    print(sv);

    cout << "after sort by size:" << endl;
    std::sort(sv.begin(), sv.end(), isShorter);
    print(sv);
}

// lambda
void test_9()
{
    auto f = []
    { return 42; };
    cout << f() << endl;

    vector<string> sv{"bb", "aaa", "c", "-"};
    std::stable_sort(sv.begin(), sv.end(), [](const string & s1, const string & s2)
    { return s1.size() < s2.size(); }); // 按长度排序
    print(sv);

    vector<int> iv{1, -2, 3, -4, 5, -6};
    std::transform(iv.begin(), iv.end(), iv.begin(), [](int i) -> int
    { return i < 0 ? -i : i; }); // 转为非负数
    print(iv);
}

// 算法命名规范
void test_10()
{
    vector<int> iv{ -2, -1, 0, 1, 2};

    std::replace(iv.begin(), iv.end(), 0, 100); // 简单替换
    print(iv);
    std::replace_if(
        iv.begin(), iv.end(), [](int i)
    { return i > 10; },
    233); // 接受谓词
    print(iv);
    cout << endl;

    vector<int> iv2;
    std::replace_copy(iv.begin(), iv.end(), std::back_inserter(iv2), 233, 666); // 拷贝
    print(iv);
    print(iv2);
    cout << endl;

    vector<int> iv3;
    std::replace_copy_if(
        iv.begin(), iv.end(), std::back_inserter(iv3), [](int i)
    { return i > 10; },
    999); // 拷贝并且接受谓词
    print(iv);
    print(iv3);
    cout << endl;
}

// list特有的
void test_11()
{
    list<int> il{1, 2, 3, 4, 5, 4, 3, 2, 1, 0};

    il.sort(); // 排序（默认升序）
    print(il);

    il.unique(); // 去重（erase删除了）
    print(il);

    il.reverse(); // 逆序
    print(il);
}

// map & set
void test_12()
{
    // 统计一行字符并且忽略空格和特殊字符
    set<char> excldue{' ', '_', '-', '+', '=', '<', '>', '!', '@', '#', '$', '%', '^', '*', '(', ')'};
    map<char, int> counter;
    string s;

    cout << "Please input a line: " << endl;
    std::getline(cin, s);
    for (const auto &c : s)
    {
        if (excldue.find(c) == excldue.end()) // not excldue
        {
            ++counter[c];
        }
    }
    for (const auto &p : counter)
    {
        cout << p.first << ": " << p.second << endl;
    }
}

#endif

// vector of string
void test_13()
{
    vector<string> list = {"Hello", "World", "!", "!", "This is vector of string."};
    for (auto cc = list.begin(); cc != list.end(); ++cc)
    {
        cout << *cc << endl;
    }

    string tofind = "!";
    if (std::find(list.begin(), list.end(), tofind) != list.end())
    {
        cout << tofind << " found" << endl;
    }
    else
    {
        cout << tofind << " not found" << endl;
    }

    tofind = "!!";
    if (std::find(list.begin(), list.end(), tofind) != list.end())
    {
        cout << tofind << " found" << endl;
    }
    else
    {
        cout << tofind << " not found" << endl;
    }

    tofind = "!";
    cout << tofind << " appears " << std::count(list.begin(), list.end(), tofind) << " times." << endl;
    tofind = "!!";
    cout << tofind << " appears " << std::count(list.begin(), list.end(), tofind) << " times." << endl;
}

// std heap
void test_14()
{
    vector<int> v = {1, 3, 5, 7, 6, 4, 2, 0};
    cout << "initial vector     : ";
    print(v);

    std::make_heap(v.begin(), v.end());
    cout << "initial max heap   : ";
    print(v);

    std::pop_heap(v.begin(), v.end());
    v.pop_back();
    cout << "max heap after pop : ";
    print(v);

    v.push_back(99);
    std::push_heap(v.begin(), v.end());
    cout << "max heap after push: ";
    print(v);

    std::sort_heap(v.begin(), v.end()); // 堆排序 不同于快速排序
    cout << "final heap sorted  : ";
    print(v);

    std::sort(v.begin(), v.end()); // 采用了 introsort （内省排序，快排和堆排序的结合）和插入排序结合的方式来实现高效排序
    cout << "final std sorted   : ";
    print(v);
}

// std::next_permutation
void test_15()
{
    const int len = 3;

    vector<int> vi;
    for (int i = 0; i < len; ++i)
    {
        vi.push_back(i + 1);
    }

    std::sort(vi.begin(), vi.end());

    cout << "The " << len << "! possible permutations with " << len << " elements:\n";
    do
    {
        print(vi);
    } while (std::next_permutation(vi.begin(), vi.end()));

    cout << "After std::next_permutation: ";
    print(vi);
}

// std::minmax_element
void test_16()
{
    vector<int> vi = {3, 7, 2, 9, 5, 8, 6};

    auto result = std::minmax_element(vi.begin(), vi.end());

    print(vi);
    cout << "min is " << *result.first;
    cout << ", at position " << (result.first - vi.begin()) << '\n';
    cout << "max is " << *result.second;
    cout << ", at position " << (result.second - vi.begin()) << '\n';
}

int main()
{
    // test_1(); // 顺序容器的基本操作
    // test_2(); // vector的增长
    // test_3(); // string探析
    // test_4(); // 适配器
    // test_5(); // 泛型只读算法
    // test_6(); // 泛型写入算法
    // test_7(); // 泛型排序算法
    // test_8(); // 定制操作
    // test_9(); // lambda
    // test_10(); // 算法命名规范
    // test_11(); // list特有的
    // test_12(); // map（关联数组）
    // test_13(); // vector of string
    // test_14(); // std heap
    // test_15(); // std::next_permutation
    // test_16(); // std::minmax_element

    return 0;
}
