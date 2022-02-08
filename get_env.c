#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    printf("PATH : %s\n", getenv("PATH"));
    printf("HOME : %s\n", getenv("HOME"));
    printf("ROOT : %s\n", getenv("ROOT"));
    printf("JAVA_HOME : %s\n", getenv("JAVA_HOME"));
    printf("QUERY_STRING: %s\n", getenv("QUERY_STRING"));

    return (0);
}
