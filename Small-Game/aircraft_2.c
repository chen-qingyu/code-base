#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "my_tools.h"

#define HEIGHT 20
#define WIDTH 50
#define TARGET 5

void init();
void show();
void update_with_input();
void update_without_input();

int canvas[HEIGHT][WIDTH] = {0}; // 0:space; 1:plane; 2:bullet; 3:target;
int plane_x, plane_y;
int target_x[TARGET], target_y[TARGET];
int score;
int weapon;

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
    plane_x = WIDTH / 2;
    plane_y = HEIGHT / 2;
    canvas[plane_y][plane_x] = 1;
    for (int i = 0; i < TARGET; ++i)
    {
        target_x[i] = rand() % WIDTH;
        target_y[i] = 0;
        canvas[target_y[i]][target_x[i]] = 3;
    }
    score = 0;
    weapon = 0;
    hide_cursor();
    for (int i = 0; i <= HEIGHT; ++i)
    {
        for (int j = 0; j <= WIDTH; ++j)
        {
            putchar((i == HEIGHT) || (j == WIDTH) ? '+' : ' ');
        }
        printf("\n");
    }
    printf("Move: W S A D; Fire: SPACE\n");
}

void show()
{
    move_cursor(0, 0);
    for (int i = 0; i < HEIGHT; ++i)
    {
        for (int j = 0; j < WIDTH; ++j)
        {
            if (canvas[i][j] == 1)
            {
                printf("*");
            }
            else if (canvas[i][j] == 2)
            {
                printf("|");
            }
            else if (canvas[i][j] == 3)
            {
                printf("@");
            }
            else
            {
                printf(" ");
            }
        }
        printf("\n");
    }
    printf("\n\nScore: %d ", score);
}

void update_with_input()
{
    char input;

    if (kbhit())
    {
        input = getch();

        if (plane_y != 0 && (input == 'w' || input == 'W'))
        {
            canvas[plane_y][plane_x] = 0;
            plane_y--;
            canvas[plane_y][plane_x] = 1;
        }
        if (plane_y != HEIGHT - 1 && (input == 's' || input == 'S'))
        {
            canvas[plane_y][plane_x] = 0;
            plane_y++;
            canvas[plane_y][plane_x] = 1;
        }
        if (plane_x != 0 && (input == 'a' || input == 'A'))
        {
            canvas[plane_y][plane_x] = 0;
            plane_x--;
            canvas[plane_y][plane_x] = 1;
        }
        if (plane_x != WIDTH - 1 && (input == 'd' || input == 'D'))
        {
            canvas[plane_y][plane_x] = 0;
            plane_x++;
            canvas[plane_y][plane_x] = 1;
        }
        if (input == ' ')
        {
            int left = plane_x - weapon, right = plane_x + weapon;
            if (left < 0)
            {
                left = 0;
            }
            if (right > WIDTH - 1)
            {
                right = WIDTH - 1;
            }
            for (int i = left; i <= right; ++i)
            {
                canvas[plane_y - 1][i] = 2;
            }
        }
    }
}

void update_without_input()
{
    for (int i = 0; i < HEIGHT; ++i)
    {
        for (int j = 0; j < WIDTH; ++j)
        {
            if (canvas[i][j] == 2)
            {
                for (int k = 0; k < TARGET; ++k)
                {
                    if (i == target_y[k] && j == target_x[k])
                    {
                        canvas[target_y[k]][target_x[k]] = 0;
                        target_y[k] = 0;
                        target_x[k] = rand() % WIDTH;
                        canvas[target_y[k]][target_x[k]] = 3;
                        score++;
                        if (score % 3 == 0)
                        {
                            weapon++;
                        }
                    }
                }
                canvas[i][j] = 0;
                if (i > 0)
                {
                    canvas[i - 1][j] = 2;
                }
            }
        }
    }

    for (int k = 0; k < TARGET; ++k)
    {
        if (target_y[k] > HEIGHT)
        {
            canvas[target_y[k]][target_x[k]] = 0;
            target_y[k] = 0;
            target_x[k] = rand() % WIDTH;
            canvas[target_y[k]][target_x[k]] = 3;
            score--;
        }
    }

    static int speed = 0;
    if (speed < 20 - score / 2)
    {
        speed++;
    }
    if (speed >= 20 - score / 2)
    {
        for (int k = 0; k < TARGET; ++k)
        {
            canvas[target_y[k]][target_x[k]] = 0;
            target_y[k]++;
            canvas[target_y[k]][target_x[k]] = 3;
            speed = 0;
        }
    }

    for (int i = 0; i < TARGET; ++i)
    {
        if ((plane_x == target_x[i]) && (plane_y == target_y[i]))
        {
            printf("\n>_<\npress ENTER to exit...");
            getchar();
            exit(EXIT_SUCCESS);
        }
    }
}
