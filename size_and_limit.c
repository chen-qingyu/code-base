#include <float.h>
#include <limits.h>
#include <stdio.h>

int main(void)
{
    printf("1 byte = %d bits on this system.\n\n", CHAR_BIT);

    printf("The size of type char        is %u bytes\n", sizeof(char));
    printf("The size of type short       is %u bytes\n", sizeof(short));
    printf("The size of type int         is %u bytes\n", sizeof(int));
    printf("The size of type float       is %u bytes\n", sizeof(float));
    printf("The size of type double      is %u bytes\n", sizeof(double));
    printf("The size of type long        is %u bytes\n", sizeof(long));
    printf("The size of type long long   is %u bytes\n", sizeof(long long));
    printf("The size of type long double is %u bytes\n\n", sizeof(long double));

    printf("Max char       = %20d.\tMin char            = %20d.\n", CHAR_MAX, CHAR_MIN);
    printf("Max int        = %20d.\tMin int             = %20d.\n", INT_MAX, INT_MIN);
    printf("Max long long  = %20lld.\tMin long long       = %20lld.\n", LLONG_MAX, LLONG_MIN);
    printf("Max float      = %20e.\tPositive min float  = %20e.\n", FLT_MAX, FLT_MIN);
    printf("Max double     = %20e.\tPositive min double = %20e.\n", DBL_MAX, DBL_MIN);
    printf("Float digit    = %20d.\tFloat epsilon       = %20e.\n", FLT_DIG, FLT_EPSILON);
    printf("Double digit   = %20d.\tDouble epsilon      = %20e.\n", DBL_DIG, DBL_EPSILON);

    return 0;
}
