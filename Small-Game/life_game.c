#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "my_tools.h"

#define HEIGHT 50
#define WIDTH 100

void init();
void show();
void update_with_input();
void update_without_input();

int cells[HEIGHT][WIDTH];

int main(void)
{
    init();
    while (1)
    {
        show();
        update_with_input();
        update_without_input();
    }
    return 0;
}

void init()
{
    srand(time(NULL));
    for (int i = 0; i < HEIGHT; ++i)
    {
        for (int j = 0; j < WIDTH; ++j)
        {
            cells[i][j] = rand() % 2;
        }
        printf("\n");
    }
    printf("Just look.\n");
    printf("Press Q to quit.\n");
    hide_cursor();
}

void show()
{
    move_cursor(0, 0);
    for (int i = 0; i < HEIGHT; ++i)
    {
        for (int j = 0; j < WIDTH; ++j)
        {
            putchar(cells[i][j] == 1 ? '*' : ' ');
        }
        printf("\n");
    }
}

void update_with_input()
{
    if (kbhit())
    {
        char c = getch();
        if (c == 'Q' || c == 'q')
        {
            exit(EXIT_SUCCESS);
        }
    }
}

void update_without_input()
{
    int tmp[HEIGHT][WIDTH];
    for (int i = 0; i < HEIGHT; ++i)
    {
        for (int j = 0; j < WIDTH; ++j)
        {
            tmp[i][j] = cells[i][j];
        }
    }

    for (int i = 1; i < HEIGHT - 1; ++i)
    {
        for (int j = 1; j < WIDTH - 1; ++j)
        {
            int adjacent = cells[i - 1][j - 1] + cells[i - 1][j] + cells[i - 1][j + 1] + cells[i][j - 1] + cells[i][j + 1] + cells[i + 1][j - 1] + cells[i + 1][j] + cells[i + 1][j + 1];
            if (adjacent == 3)
            {
                tmp[i][j] = 1;
            }
            else if (adjacent == 2)
            {
                tmp[i][j] = cells[i][j];
            }
            else
            {
                tmp[i][j] = 0;
            }
        }
    }

    for (int i = 0; i < HEIGHT; ++i)
    {
        for (int j = 0; j < WIDTH; ++j)
        {
            cells[i][j] = tmp[i][j];
        }
    }

    Sleep(100);
}
