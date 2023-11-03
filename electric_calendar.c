#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static inline void print_header(const int year, const int month)
{
    static const char* headers[] = {
        "====January %d====\n",
        "====February %d===\n",
        "====March %d======\n",
        "====April %d======\n",
        "====May %d========\n",
        "====June %d=======\n",
        "====July %d=======\n",
        "====August %d=====\n",
        "====September %d==\n",
        "====October %d====\n",
        "====November %d===\n",
        "====December %d===\n",
    };
    printf(headers[month - 1], year);
    printf("Su Mo Tu We Th Fr Sa\n");
}

static inline bool is_leap_year(int year)
{
    return year % 400 == 0 || (year % 100 != 0 && year % 4 == 0);
}

static inline int day_of_week(int year, int month, int day)
{
    // Tomohiko Sakamoto's Algorithm
    year -= month < 3;
    return (year + year / 4 - year / 100 + year / 400 + "-bed=pen+mad."[month] + day) % 7;
}

static inline void print_calendar(int year, int month)
{
    print_header(year, month);

    int days;
    if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
    {
        days = 31;
    }
    else if (month == 4 || month == 6 || month == 9 || month == 11)
    {
        days = 30;
    }
    else // month == 2
    {
        days = is_leap_year(year) ? 29 : 28;
    }

    int dow = day_of_week(year, month, 1); // Sunday is 0
    for (int i = 0; i < dow; i++)
    {
        printf("   ");
    }

    for (int i = 1; i <= days; i++)
    {
        printf("%02d%c", i, (i + dow) % 7 == 0 || i == days ? '\n' : ' ');
    }
}

int main(void)
{
    printf("Welcome to the electronic calendar program!\n");
    printf("Designed by C\n");
    printf(" - N: Show calendar for next month.\n");
    printf(" - P: Show calendar for previous month.\n");
    printf(" - C: Show calendar for current month.\n");
    printf(" - Q: Quit.\n");
    printf("\n");

    time_t now = time(NULL);
    struct tm* tm = localtime(&now);

    int show_year = tm->tm_year + 1900;
    int show_month = tm->tm_mon + 1;

    while (true)
    {
        now = time(NULL);
        tm = localtime(&now);

        int year = tm->tm_year + 1900;
        int month = tm->tm_mon + 1;
        int day = tm->tm_mday;
        int hour = tm->tm_hour;
        int minute = tm->tm_min;
        int second = tm->tm_sec;

        print_calendar(show_year, show_month);
        printf("\n");
        printf("Now: %d.%02d.%02d %02d:%02d:%02d\n", year, month, day, hour, minute, second);

        char choice = '\0';
        scanf("%c", &choice);
        fflush(stdin);

        if (choice == 'Q' || choice == 'q')
        {
            printf("Bye.\n");
            break;
        }
        else if (choice == 'N' || choice == 'n')
        {
            show_month++;
            if (show_month > 12)
            {
                show_year++;
                show_month -= 12;
            }
        }
        else if (choice == 'P' || choice == 'p')
        {
            show_month--;
            if (show_month < 1)
            {
                show_year--;
                show_month += 12;
            }
        }
        else if (choice == 'C' || choice == 'c')
        {
            show_year = year;
            show_month = month;
        }
    }

    return 0;
}
