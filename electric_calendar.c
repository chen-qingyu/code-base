#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SUNDAY 0

const int base_year = 1589;
const int base_year_jan_1 = SUNDAY;
const int max_year = 2999;

void print_header(const int year, const int month)
{
    if (month == 1)
    {
        printf("====January %d====\n", year);
    }
    else if (month == 2)
    {
        printf("===February %d====\n", year);
    }
    else if (month == 3)
    {
        printf("=====March %d=====\n", year);
    }
    else if (month == 4)
    {
        printf("=====April %d=====\n", year);
    }
    else if (month == 5)
    {
        printf("======May %d======\n", year);
    }
    else if (month == 6)
    {
        printf("=====June %d======\n", year);
    }
    else if (month == 7)
    {
        printf("=====July %d======\n", year);
    }
    else if (month == 8)
    {
        printf("====August %d=====\n", year);
    }
    else if (month == 9)
    {
        printf("===September %d===\n", year);
    }
    else if (month == 10)
    {
        printf("====October %d====\n", year);
    }
    else if (month == 11)
    {
        printf("===November %d====\n", year);
    }
    else if (month == 12)
    {
        printf("===December %d====\n", year);
    }
    printf("Su Mo Tu We Th Fr Sa\n");
}

bool valid_date(int year, int month, int day)
{
    bool is_leap = (year % 400 == 0 || (year % 100 != 0 && year % 4 == 0));

    bool is_valid_year = (year >= base_year && year <= max_year);
    bool is_valid_month = (month >= 1 && month <= 12);
    bool is_valid_day;

    if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
    {
        is_valid_day = (day >= 1 && day <= 31);
    }
    else if (month == 2)
    {
        if (is_leap)
        {
            is_valid_day = (day >= 1 && day <= 29);
        }
        else
        {
            is_valid_day = (day >= 1 && day <= 28);
        }
    }
    else if (month == 4 || month == 6 || month == 9 || month == 11)
    {
        is_valid_day = (day >= 1 && day <= 30);
    }
    else
    {
        is_valid_day = false;
    }

    return is_valid_year && is_valid_month && is_valid_day;
}

int day_of_the_week(int year, int month, int day)
{
    int tmp = base_year_jan_1 - 1;

    for (int y = base_year; y < year; y++)
    {
        for (int m = 1; m <= 12; m++)
        {
            for (int d = 1; d <= 31; d++)
            {
                if (valid_date(y, m, d))
                {
                    tmp++;
                }
            }
        }
    }

    for (int m = 1; m < month; m++)
    {
        for (int d = 1; d <= 31; d++)
        {
            if (valid_date(year, m, d))
            {
                tmp++;
            }
        }
    }

    for (int d = 1; d <= day; d++)
    {
        if (valid_date(year, month, d))
        {
            tmp++;
        }
    }

    return tmp % 7;
}

void print_calendar(int year, int month)
{
    print_header(year, month);

    int dow = day_of_the_week(year, month, 1);
    int days;
    if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
    {
        days = 31;
    }
    else if (month == 4 || month == 6 || month == 9 || month == 11)
    {
        days = 30;
    }
    else
    {
        if ((year % 400 == 0 || (year % 100 != 0 && year % 4 == 0)))
        {
            days = 29;
        }
        else
        {
            days = 28;
        }
    }

    for (int i = 0; i < dow; i++)
    {
        printf("   ");
    }

    for (int i = 1; i <= days; i++)
    {
        if ((i + dow) % 7 == 0)
        {
            printf("%02d\n", i);
        }
        else if (i == days)
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
    printf("\n");
    printf("Input Q to quit.\n");
    printf("Input N to show calendar for next month.\n");
    printf("Input P to show calendar for previous month.\n");
    printf("\n");

    time_t now;
    struct tm *ts;
    time(&now);
    ts = localtime(&now);

    int showYear = ts->tm_year + 1900;
    int showMonth = ts->tm_mon + 1;

    char choice = '\0';
    while (true)
    {
        time(&now);
        ts = localtime(&now);

        int year = ts->tm_year + 1900;
        int month = ts->tm_mon + 1;
        int day = ts->tm_mday;
        int hour = ts->tm_hour;
        int minute = ts->tm_min;
        int second = ts->tm_sec;

        print_calendar(showYear, showMonth);
        printf("\n");
        printf("Now: %d.%02d.%02d %02d:%02d:%02d\n", year, month, day, hour, minute, second);
        scanf("%c", &choice);
        fflush(stdin);

        if (choice == 'Q' || choice == 'q')
        {
            printf("Bye.\n");
            break;
        }
        else if (choice == 'N' || choice == 'n')
        {
            showMonth++;
            if (showMonth > 12)
            {
                showYear++;
                showMonth -= 12;
            }
        }
        else if (choice == 'P' || choice == 'p')
        {
            showMonth--;
            if (showMonth < 1)
            {
                showYear--;
                showMonth += 12;
            }
        }
    }

    return 0;
}
