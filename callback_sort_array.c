#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void sortArray(void *arr, int eleSize, int len, int (*myCmp)(const void *, const void *))
{
    char *temp = malloc(eleSize);
    for (int i = 0; i < len - 1; i++)
    {
        int isSwapped = 0;
        for (int j = 0; j < len - i - 1; j++)
        {
            char *eleAddr = (char *)arr + eleSize * j;
            char *eleAddrPlus = (char *)arr + eleSize * (j + 1);
            if (myCmp(eleAddrPlus, eleAddr))
            {
                // 利用memcpy()交换元素
                memcpy(temp, eleAddrPlus, eleSize);
                memcpy(eleAddrPlus, eleAddr, eleSize);
                memcpy(eleAddr, temp, eleSize);
                isSwapped = 1;
            }
        }
        if (isSwapped == 0)
        {
            break;
        }
    }
    free(temp);
    temp = NULL;
}

// void sortArray(void *arr, int eleSize, int len, int (*myCmp)(const void *, const void *))
// {
//     if (len > 1)
//     {
//         char *temp = malloc(eleSize);
//         char *pivot = malloc(eleSize);
//         int low = 0, high = len - 2;
//         int left = 0, right = len - 1;
//         int center = (left + right) / 2;

//         char *eleAddrLeft = (char *)arr + eleSize * left;
//         char *eleAddrRright = (char *)arr + eleSize * right;
//         char *eleAddrCenter = (char *)arr + eleSize * center;
//         if (myCmp(eleAddrLeft, eleAddrCenter))
//         {
//             memcpy(temp, eleAddrLeft, eleSize);
//             memcpy(eleAddrLeft, eleAddrCenter, eleSize);
//             memcpy(eleAddrCenter, temp, eleSize);
//         }
//         if (myCmp(eleAddrLeft, eleAddrRright))
//         {
//             memcpy(temp, eleAddrLeft, eleSize);
//             memcpy(eleAddrLeft, eleAddrRright, eleSize);
//             memcpy(eleAddrRright, temp, eleSize);
//         }
//         if (myCmp(eleAddrCenter, eleAddrRright))
//         {
//             memcpy(temp, eleAddrCenter, eleSize);
//             memcpy(eleAddrCenter, eleAddrRright, eleSize);
//             memcpy(eleAddrRright, temp, eleSize);
//         }

//         memcpy(temp, eleAddrCenter, eleSize);
//         memcpy(eleAddrCenter, eleAddrRright - eleSize, eleSize);
//         memcpy(eleAddrRright - eleSize, temp, eleSize);

//         memcpy(pivot, eleAddrRright - eleSize, eleSize);

//         char *eleAddrLow = (char *)arr + eleSize * (low + 1);
//         char *eleAddrHigh = (char *)arr + eleSize * (high - 1);

//         while (1)
//         {
//             while (myCmp(pivot, eleAddrLow))
//             {
//                 low++;
//                 eleAddrLow += eleSize;
//             }

//             while (myCmp(eleAddrHigh, pivot))
//             {
//                 high--;
//                 eleAddrHigh -= eleSize;
//             }
//             if (low < high)
//             {
//                 memcpy(temp, eleAddrLow, eleSize);
//                 memcpy(eleAddrLow, eleAddrHigh, eleSize);
//                 memcpy(eleAddrHigh, temp, eleSize);
//             }
//             else
//             {
//                 break;
//             }

//             char *addrEdge = (char *)arr + eleSize * (len - 2);
//             memcpy(temp, eleAddrLow, eleSize);
//             memcpy(eleAddrLow, addrEdge, eleSize);
//             memcpy(addrEdge, temp, eleSize);

//             sortArray(arr, eleSize, low, myCmp);
//             sortArray((char *)arr + eleSize * (low + 1), eleSize, len - low - 1, myCmp);
//         }
//         free(temp);
//         temp = NULL;
//         free(pivot);
//         pivot = NULL;
//     }
// }

int myCmpInt(const void *a, const void *b)
{
    const int *p1 = a;
    const int *p2 = b;
    return *p1 > *p2; // ">" 降序排列
}

struct Person
{
    char name[64];
    int age;
};

int myCmpPersonAge(const void *a, const void *b)
{
    const struct Person *p1 = a;
    const struct Person *p2 = b;
    return p1->age < p2->age;
}

int myCmpPersonName(const void *a, const void *b)
{
    const struct Person *p1 = a;
    const struct Person *p2 = b;
    return strcmp(p1->name, p2->name) < 0;
}

int main(void)
{
    int arrInt[] = {2, 5, 7, 5, 4, 3, 8, 21, 9, 0, 99};
    struct Person arrPerson[] = {
        {"Alice", 18},
        {"Sakura", 19},
        {"Homura", 20},
        {"Mei", 17},
        {"Yuzu", 18},
    };

    /* 动态获取长度 */
    int lenArrInt = sizeof(arrInt) / sizeof(int);
    sortArray(arrInt, sizeof(int), lenArrInt, myCmpInt);
    for (int i = 0; i < lenArrInt; i++)
    {
        printf("%d ", arrInt[i]);
    }
    printf("\n");

    /* 动态获取长度 */
    int lenArrPerson = sizeof(arrPerson) / sizeof(struct Person);
    /* 根据结构体元素的年龄排序 */
    printf("Order by Age-----------\n");
    sortArray(arrPerson, sizeof(struct Person), lenArrPerson, myCmpPersonAge);
    for (int i = 0; i < lenArrPerson; i++)
    {
        printf("Name: %s\tAge: %d\n", arrPerson[i].name, arrPerson[i].age);
    }
    /* 根据结构体元素的姓名排序 */
    printf("Order by Name----------\n");
    sortArray(arrPerson, sizeof(struct Person), lenArrPerson, myCmpPersonName);
    for (int i = 0; i < lenArrPerson; i++)
    {
        printf("Name: %s\tAge: %d\n", arrPerson[i].name, arrPerson[i].age);
    }

    return 0;
}
