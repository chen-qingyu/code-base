#include <conio.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "my_tools.h"

#define HEIGHT 20
#define WIDTH 50

#define UP 1
#define DOWN 2
#define LEFT 3
#define RIGHT 4

void init();
void show();
void update_with_input();
void update_without_input();

int canvas[HEIGHT][WIDTH] = {0}; // -2: food, -1: wall, 0: space, 1: head, >1: body
int direction;
int food_x, food_y;
int score;

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
        canvas[i][0] = -1;
        canvas[i][WIDTH - 1] = -1;
    }
    for (int i = 0; i < WIDTH; ++i)
    {
        canvas[0][i] = -1;
        canvas[HEIGHT - 1][i] = -1;
    }
    score = 0;
    direction = RIGHT;
    canvas[HEIGHT / 2][WIDTH / 2] = 1;
    for (int i = 1; i < 4; ++i)
    {
        canvas[HEIGHT / 2][WIDTH / 2 - i] = i + 1;
    }
    food_y = rand() % (HEIGHT - 2) + 1;
    food_x = rand() % (WIDTH - 2) + 1;
    canvas[food_y][food_x] = -2;
    hide_cursor();
}

void show()
{
    move_cursor(0, 0);
    for (int i = 0; i < HEIGHT; ++i)
    {
        for (int j = 0; j < WIDTH; ++j)
        {
            if (canvas[i][j] == 0)
            {
                printf(" ");
            }
            else if (canvas[i][j] == -1)
            {
                printf("+");
            }
            else if (canvas[i][j] == 1)
            {
                printf("@");
            }
            else if (canvas[i][j] > 1)
            {
                printf("*");
            }
            else if (canvas[i][j] == -2)
            {
                printf("$");
            }
        }
        printf("\n");
    }
    printf("Move: W S A D\n");
    printf("Score: %d\n", score);
    Sleep(500 / (score + 1));
}

void update_with_input()
{
    char input;

    if (kbhit())
    {
        input = getch();
        if (direction != DOWN && (input == 'w' || input == 'W'))
        {
            direction = UP;
        }
        else if (direction != UP && (input == 's' || input == 'S'))
        {
            direction = DOWN;
        }
        else if (direction != RIGHT && (input == 'a' || input == 'A'))
        {
            direction = LEFT;
        }
        else if (direction != LEFT && (input == 'd' || input == 'D'))
        {
            direction = RIGHT;
        }
    }
}

void update_without_input()
{
    int max = 0;
    int old_tail_i, old_tail_j, old_head_i, old_head_j, new_head_i, new_head_j;
    for (int i = 0; i < HEIGHT; ++i)
    {
        for (int j = 0; j < WIDTH; ++j)
        {
            if (canvas[i][j] > 0)
            {
                canvas[i][j]++;
                if (max < canvas[i][j])
                {
                    max = canvas[i][j];
                    old_tail_i = i;
                    old_tail_j = j;
                }
                if (canvas[i][j] == 2)
                {
                    old_head_i = i;
                    old_head_j = j;
                }
            }
        }
    }
    if (direction == UP)
    {
        new_head_i = old_head_i - 1;
        new_head_j = old_head_j;
    }
    else if (direction == DOWN)
    {
        new_head_i = old_head_i + 1;
        new_head_j = old_head_j;
    }
    else if (direction == LEFT)
    {
        new_head_i = old_head_i;
        new_head_j = old_head_j - 1;
    }
    else if (direction == RIGHT)
    {
        new_head_i = old_head_i;
        new_head_j = old_head_j + 1;
    }

    if (canvas[new_head_i][new_head_j] == -2)
    {
        canvas[food_y][food_x] = 0;
        food_y = rand() % (HEIGHT - 2) + 1;
        food_x = rand() % (WIDTH - 2) + 1;
        while (canvas[food_y][food_x] > 0)
        {
            food_y = rand() % (HEIGHT - 2) + 1;
            food_x = rand() % (WIDTH - 2) + 1;
        }
        canvas[food_y][food_x] = -2;
        score++;
    }
    else
    {
        canvas[old_tail_i][old_tail_j] = 0;
    }

    if (canvas[new_head_i][new_head_j] > 0 || canvas[new_head_i][new_head_j] == -1)
    {
        printf(">_<\npress ENTER to exit...");
        getchar();
        exit(EXIT_SUCCESS);
    }
    else
    {
        canvas[new_head_i][new_head_j] = 1;
    }
}
