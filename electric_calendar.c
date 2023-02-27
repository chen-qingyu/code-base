#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SUNDAY 0

const int base_year = 1589;
const int base_year_jan_1 = SUNDAY;
const int max_year = 2999;

static inline void print_header(const int year, const int month)
{
    switch (month)
    {
        case 1:
            printf("====January %d====\n", year);
            break;
        case 2:
            printf("====February %d===\n", year);
            break;
        case 3:
            printf("====March %d======\n", year);
            break;
        case 4:
            printf("====April %d======\n", year);
            break;
        case 5:
            printf("====May %d========\n", year);
            break;
        case 6:
            printf("====June %d=======\n", year);
            break;
        case 7:
            printf("====July %d=======\n", year);
            break;
        case 8:
            printf("====August %d=====\n", year);
            break;
        case 9:
            printf("====September %d==\n", year);
            break;
        case 10:
            printf("====October %d====\n", year);
            break;
        case 11:
            printf("====November %d===\n", year);
            break;
        case 12:
            printf("====December %d===\n", year);
            break;
        default:
            break;
    }
    printf("Su Mo Tu We Th Fr Sa\n");
}

static inline bool is_leap_year(int year)
{
    return year % 400 == 0 || (year % 100 != 0 && year % 4 == 0);
}

static inline bool is_valid_date(int year, int month, int day)
{
    bool is_valid_year = (year >= base_year && year <= max_year);
    bool is_valid_month = (month >= 1 && month <= 12);
    bool is_valid_day = false;

    if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
    {
        is_valid_day = (day >= 1 && day <= 31);
    }
    else if (month == 4 || month == 6 || month == 9 || month == 11)
    {
        is_valid_day = (day >= 1 && day <= 30);
    }
    else // month == 2
    {
        is_valid_day = is_leap_year(year) ? (day >= 1 && day <= 29) : (day >= 1 && day <= 28);
    }

    return is_valid_year && is_valid_month && is_valid_day;
}

static inline int day_of_week(int year, int month, int day)
{
    int dow = base_year_jan_1 - 1;

    for (int y = base_year; y < year; y++)
    {
        for (int m = 1; m <= 12; m++)
        {
            for (int d = 1; d <= 31; d++)
            {
                if (is_valid_date(y, m, d))
                {
                    dow++;
                }
            }
        }
    }

    for (int m = 1; m < month; m++)
    {
        for (int d = 1; d <= 31; d++)
        {
            if (is_valid_date(year, m, d))
            {
                dow++;
            }
        }
    }

    for (int d = 1; d <= day; d++)
    {
        if (is_valid_date(year, month, d))
        {
            dow++;
        }
    }

    return dow % 7;
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

    int dow = day_of_week(year, month, 1);
    for (int i = 0; i < dow; i++)
    {
        printf("   ");
    }

    for (int i = 1; i <= days; i++)
    {
        if ((i + dow) % 7 == 0 || i == days)
        {
            printf("%02d\n", i);
        }
        else
        {
            printf("%02d ", i);
        }
    }
}

int main(void)
{
    printf("Welcome to the electronic calendar program!\n");
    printf("Designed by C\n");
    printf(" - N: Show calendar for next month.\n");
    printf(" - P: Show calendar for previous month.\n");
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
    }

    return 0;
}
