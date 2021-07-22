#include <stdio.h>
#include <string.h>
#define SIZE 100

int main(void)
{
    char a[SIZE];
    int digit, ch, blank, other;
    while (1)
    {
        digit = 0, ch = 0, blank = 0, other = 0;
        printf("Please enter a character string:\n");
        gets(a);
        for (int i = 0; i < strlen(a); i++)
        {
            if ((a[i] >= '0') && (a[i] <= '9'))
            {
                digit++;
            }
            else if ((a[i] >= 'a' && a[i] <= 'z') || (a[i] >= 'A' && a[i] <= 'Z'))
            {
                ch++;
            }
            else if (a[i] == ' ')
            {
                blank++;
            }
            else
            {
                other++;
            }
        }
        printf("char=%d, space=%d, digit=%d, other=%d\n\n", ch, blank, digit, other);
    }

    return 0;
}
