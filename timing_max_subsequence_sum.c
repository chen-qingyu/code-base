/*
比较不同的计算最大子列和的算法的时间复杂度
*/

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX(A, B, C) ((A) > (B) ? (A) > (C) ? (A) : (C) : (B) > (C) ? (B) : (C))

typedef int (*pfun_t)(int n, int a[]);

int method_1(int n, int a[]);
int method_2(int n, int a[]);
int method_3(int n, int a[]);
int method_4(int n, int a[]);
void time_test(pfun_t method);

int main(void)
{
    time_test(method_1); // 暴力循环法 O(N^3)
    time_test(method_2); // 改进的暴力循环法 O(N^2)
    time_test(method_3); // 分治法 O(NlogN)
    time_test(method_4); // 在线处理算法 O(N)
    getchar();
    return 0;
}

int method_1(int n, int a[])
{
    int thisSum, maxSum = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = i; j < n; j++)
        {
            thisSum = 0;
            for (int k = i; k <= j; k++)
            {
                thisSum += a[k];
            }
            if (thisSum > maxSum)
            {
                maxSum = thisSum;
            }
        }
    }
    return maxSum;
}

int method_2(int n, int a[])
{
    int thisSum, maxSum = 0;
    for (int i = 0; i < n; i++)
    {
        thisSum = 0;
        for (int j = i; j < n; j++)
        {
            thisSum += a[j];
            if (thisSum > maxSum)
            {
                maxSum = thisSum;
            }
        }
    }
    return maxSum;
}

int divideAndConquer(int a[], int left, int right)
{
    int maxLeftSum, maxRightSum;
    int maxLeftBorderSum, maxRightBorderSum;
    int leftBorderSum, rightBorderSum;
    int center, i;

    if (left == right)
    {
        if (a[left] > 0)
        {
            return a[left];
        }
        else
        {
            return 0;
        }
    }

    center = (left + right) / 2;

    maxLeftSum = divideAndConquer(a, left, center);
    maxRightSum = divideAndConquer(a, center + 1, right);

    maxLeftBorderSum = 0;
    leftBorderSum = 0;
    for (i = center; i >= left; i--)
    {
        leftBorderSum += a[i];
        if (leftBorderSum > maxLeftBorderSum)
        {
            maxLeftBorderSum = leftBorderSum;
        }
    }

    maxRightBorderSum = 0;
    rightBorderSum = 0;
    for (i = center + 1; i <= right; i++)
    {
        rightBorderSum += a[i];
        if (rightBorderSum > maxRightBorderSum)
        {
            maxRightBorderSum = rightBorderSum;
        }
    }

    return MAX(maxLeftSum, maxRightSum, maxLeftBorderSum + maxRightBorderSum);
}

int method_3(int n, int a[])
{
    return divideAndConquer(a, 0, n - 1);
}

int method_4(int n, int a[])
{
    int thisSum = 0, maxSum = 0;
    for (int i = 0; i < n; i++)
    {
        thisSum += a[i];
        if (thisSum > maxSum)
        {
            maxSum = thisSum;
        }
        else if (thisSum < 0)
        {
            thisSum = 0;
        }
    }
    return maxSum;
}

void time_test(pfun_t method)
{
    clock_t start, end;
    static int i = 0;
    i++;

    int loop = 1e5; // 多次运行取平均值
    int size = 100;
    int a[size];
    srand(0);
    for (int i = 0; i < size; i++)
    {
        a[i] = rand(); // 给定的整数序列
    }
    int result; // 计算结果

    start = clock();
    for (int i = 0; i < loop; i++)
    {
        result = method(size, a); // 计算最大子列和
    }
    end = clock();

    printf("method %d result: %d\n", i, result);
    printf("method %d duration: %.2e s\n\n", i, (double)(end - start) / CLOCKS_PER_SEC / loop);
}
