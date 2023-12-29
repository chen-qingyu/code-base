#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "my_tools.h"

#define MONSTER_NUMBER 5

void init();
void show();
void update_with_input();
void update_without_input();

int height, width;
int man_x, man_y;
int monster_x[MONSTER_NUMBER], monster_y[MONSTER_NUMBER];
clock_t start, end;

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
    width = 40;
    height = 20;
    man_x = width / 2;
    man_y = height / 2;
    for (int i = 0; i < MONSTER_NUMBER; ++i)
    {
        monster_x[i] = rand() % width;
        monster_y[i] = rand() % height;
    }
    hide_cursor();
    for (int i = 0; i <= height; ++i)
    {
        for (int j = 0; j <= width; ++j)
        {
            putchar((i == height) || (j == width) ? '+' : ' ');
        }
        printf("\n");
    }
    printf("Move: W S A D; Try to hold on for 20 seconds.\n");
    start = clock();
}

void show()
{
    move_cursor(0, 0);
    for (int i = 0; i < height; ++i)
    {
        for (int j = 0; j < width; ++j)
        {
            if ((i == man_y) && (j == man_x))
            {
                printf("*");
            }
            else if ((i == monster_y[0]) && (j == monster_x[0]))
            {
                printf("!");
            }
            else if ((i == monster_y[1]) && (j == monster_x[1]))
            {
                printf("!");
            }
            else if ((i == monster_y[2]) && (j == monster_x[2]))
            {
                printf("!");
            }
            else if ((i == monster_y[3]) && (j == monster_x[3]))
            {
                printf("!");
            }
            else if ((i == monster_y[4]) && (j == monster_x[4]))
            {
                printf("!");
            }
            else
            {
                printf(" ");
            }
        }
        printf("\n");
    }
    end = clock();
    printf("\n\nTime: %.2lf s\n", (double)(end - start) / CLOCKS_PER_SEC);
}

void update_with_input()
{
    char input;

    if (kbhit())
    {
        input = getch();

        if (man_y != 0 && (input == 'w' || input == 'W'))
        {
            man_y--;
        }
        if (man_y != height - 1 && (input == 's' || input == 'S'))
        {
            man_y++;
        }
        if (man_x != 0 && (input == 'a' || input == 'A'))
        {
            man_x--;
        }
        if (man_x != width - 1 && (input == 'd' || input == 'D'))
        {
            man_x++;
        }
    }
}

void update_without_input()
{
    for (int i = 0; i < MONSTER_NUMBER; ++i)
    {
        if ((man_x == monster_x[i]) && (man_y == monster_y[i]))
        {
            if ((double)(end - start) / CLOCKS_PER_SEC > 20)
            {
                printf("\nYou're tooooooooo agile!\n");
            }
            else
            {
                printf("\n>_<\npress ENTER to exit...");
            }
            getchar();
            exit(EXIT_SUCCESS);
        }
    }

    static int speed = 0;
    if (speed < 20 - (end - start) / CLOCKS_PER_SEC)
    {
        speed++;
    }
    if (speed >= 20 - (end - start) / CLOCKS_PER_SEC)
    {
        for (int i = 0; i < MONSTER_NUMBER; ++i)
        {
            if (monster_x[i] < man_x)
            {
                monster_x[i]++;
            }
            if (monster_x[i] > man_x)
            {
                monster_x[i]--;
            }
            if (monster_y[i] < man_y)
            {
                monster_y[i]++;
            }
            if (monster_y[i] > man_y)
            {
                monster_y[i]--;
            }
        }
        speed = 0;
    }
}
