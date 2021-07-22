#include <stdio.h>

void printArray(void *arr, int eleSize, int len, void (*myPrint)(const void *))
{
    char *p = arr;
    for (int i = 0; i < len; i++)
    {
        char *eleAddr = p + eleSize * i;
        myPrint(eleAddr);
    }
}

void myPrintInt(const void *data)
{
    const int *p = data;
    printf("Int: %d\n", *p);
}

void myPrintDouble(const void *data)
{
    const double *p = data;
    printf("Double: %.2lf\n", *p);
}

struct Person
{
    char name[64];
    int age;
};

void myPrintPerson(const void *data)
{
    const struct Person *p = data;
    printf("Name: %s\tAge: %d\n", p->name, p->age);
}

int main(void)
{
    int arrInt[] = {1, 2, 3, 4, 5};
    double arrDouble[] = {1.1, 1.2, 1.3};

    struct Person arrPerson[] = {
        {"Alice", 18},
        {"Sakura", 19},
        {"Homura", 20},
    };

    printArray(arrInt, sizeof(int), sizeof(arrInt) / sizeof(int), myPrintInt);
    printArray(arrDouble, sizeof(double), sizeof(arrDouble) / sizeof(double), myPrintDouble);
    printArray(arrPerson, sizeof(struct Person), sizeof(arrPerson) / sizeof(struct Person), myPrintPerson);
    return 0;
}
