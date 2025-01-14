#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::string;
using std::vector;

// Select the arrangement of m numbers from vector of T.
template <typename T>
vector<vector<T>> arrangement(const vector<T>& vt, int m)
{
    vector<vector<T>> ret;
    if ((int)vt.size() < m)
    {
        return ret;
    }

    // recursive exit
    if (1 == m)
    {
        for (const auto& item : vt)
        {
            vector<T> vtTemp;
            vtTemp.push_back(item);
            ret.push_back(vtTemp);
        }
        return ret;
    }

    // Take an element from the set, and then let the remaining elements take m-1 elements for full arrangement, recursively
    for (auto it = vt.begin(); it != vt.end(); it++)
    {
        vector<T> vtTemp;
        // gets the preceding part of the current element
        if (it != vt.begin())
        {
            vtTemp.insert(vtTemp.end(), vt.begin(), it);
        }
        // get the following part of the current element
        if (it + 1 != vt.end())
        {
            vtTemp.insert(vtTemp.end(), it + 1, vt.end());
        }
        vector<vector<T>> vtArrage = arrangement(vtTemp, m - 1); // recursion, decomposition problem
        // adds the current element to the collection and the collection to the result set
        for (const auto& vtSet : vtArrage)
        {
            auto itInsert = ret.insert(ret.end(), vtSet);
            itInsert->push_back(*it);
        }
    }

    return ret;
}

// Calculate x^n
int pow(int x, int n)
{
    int result = 1;
    while (n > 0)
    {
        result *= x;
        --n;
    }
    return result;
}

// Get the number of leaf node of a N-forked tree.
// layer 0 => 0, layer 1 => 1, layer 2 => n+1
int getNodeNum(int layer, int n)
{
    int number = 0;
    for (int i = 0; i < layer; ++i)
    {
        number += pow(n, i);
    }
    return number;
}

// Full arrangement with put back
// ({'+', '-', '*', '/'}, 2) =>
//   {{'+', '+'}, {'+', '-'}, {'+', '*'}, {'+', '/'},
//    {'-', '+'}, ..., {'-', '/'}, {'*', '+'}, ..., {'/', '/'}}
template <typename T>
vector<vector<T>> NForkedTree(vector<T> seq, int layer)
{
    // N-ForkedTree! Each branch node is a T!

    vector<vector<T>> ret;
    int n = seq.size(); // n-forked

    // for each leaf node, back up to root to get the combination of T on the path
    for (int node = getNodeNum(layer, n), i = 0, cnt = pow(n, layer); i < cnt; ++node, ++i)
    {
        vector<T> path;
        int current = node;
        while (current > 0)
        {
            path.push_back(seq[(current - 1) % n]);
            current = (current - 1) / n; // go back to the upper level
        }
        ret.push_back(path);
    }
    return ret;
}

string lineToString(const vector<string>& line)
{
    string str;
    for (const auto& i : line)
    {
        str += i;
        str += " ";
    }
    return str;
}

string lineToString(const vector<int>& line)
{
    string str;
    for (const auto& i : line)
    {
        str += std::to_string(i);
        str += " ";
    }
    return str;
}

int main()
{
    // example 1
    vector<string> opseq = {"+", "-", "*", "/"};
    auto ops = NForkedTree(opseq, 3);
    auto arrops = arrangement(opseq, 3);
    for (const auto& op : ops)
    {
        cout << lineToString(op) << endl;
    }
    cout << "count: " << ops.size() << endl;
    cout << "^ is put it back by NForkedTree(), v is not put it back by arrangement()" << endl;
    for (const auto& op : arrops)
    {
        cout << lineToString(op) << endl;
    }
    cout << "count: " << arrops.size() << endl;

    cout << "========" << endl;

    // example 2
    vector<int> intseq = {1, 2, 3, 4, 5};
    auto ints = NForkedTree(intseq, 2);
    auto arrints = arrangement(intseq, 2);
    for (const auto& i : ints)
    {
        cout << lineToString(i) << endl;
    }
    cout << "count: " << ints.size() << endl;
    cout << "^ is put it back by NForkedTree(), v is not put it back by arrangement()" << endl;
    for (const auto& i : arrints)
    {
        cout << lineToString(i) << endl;
    }
    cout << "count: " << arrints.size() << endl;

    return 0;
}
