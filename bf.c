/************************************************************
 * File Name: bf.c
 * Author: Chobits
 * Date: 2021.04.25
 * Description: Brainfuck interpreter implementation in C
 ***********************************************************/

#include <stdio.h>

#define TAPE_SIZE 1024

void bf(FILE *fp);

int main(int argc, char const *argv[])
{
    if (argc != 2)
    {
        fprintf(stderr, "Error: parameter number mismatch.\n");
        fprintf(stderr, "Usage:\n");
        fprintf(stderr, "bf <src_file> # Interpret the brainfuck source code.\n");
        return 1;
    }

    FILE *fp;
    fopen_s(&fp, argv[1], "r");
    if (fp == NULL)
    {
        fprintf(stderr, "Error: failed to open file \"%s\".\n", argv[1]);
        return 2;
    }

    bf(fp);

    fclose(fp);

    return 0;
}

void bf(FILE *fp)
{
    int bracket_cnt;           // count brackets
    int command;               // current command character
    int data[TAPE_SIZE] = {0}; // memory data
    int *data_ptr;             // memory data pointer

    // Move data_ptr to middle of the data tape
    data_ptr = &data[TAPE_SIZE / 2];

    int c;
    while ((command = getc(fp)) != EOF)
    {
        switch (command)
        {
            /* Move data pointer to next address */
            case '>':
                ++data_ptr;
                break;

            /* Move data pointer to previous address */
            case '<':
                --data_ptr;
                break;

            /* Increase value at current data cell by one */
            case '+':
                ++*data_ptr;
                break;

            /* Decrease value at current data cell by one */
            case '-':
                --*data_ptr;
                break;

            /* Output character at current data cell */
            case '.':
                putc(*data_ptr, stdout);
                break;

            /* Accept one character from user and advance to next one */
            case ',':
                *data_ptr = getc(stdin);
                break;

            /* When the value at current data cell is 0,
            advance to next matching ] */
            case '[':
                if (!*data_ptr)
                {
                    for (bracket_cnt = 1; bracket_cnt; fseek(fp, 1, SEEK_CUR))
                    {
                        c = getc(fp);
                        fseek(fp, -1, SEEK_CUR);
                        if (c == '[')
                        {
                            bracket_cnt++;
                        }
                        else if (c == ']')
                        {
                            bracket_cnt--;
                        }
                    }
                }
                break;

            /* Moves the command pointer back to matching
            opening [ if the value of current data cell is not 0 */
            case ']':
                if (*data_ptr)
                {
                    // Move command pointer just before ]
                    fseek(fp, -2, SEEK_CUR);
                    for (bracket_cnt = 1; bracket_cnt; fseek(fp, -1, SEEK_CUR))
                    {
                        c = getc(fp);
                        fseek(fp, -1, SEEK_CUR);
                        if (c == ']')
                        {
                            bracket_cnt++;
                        }
                        else if (c == '[')
                        {
                            bracket_cnt--;
                        }
                    }
                    // Advance pointer after loop to match with opening [
                    fseek(fp, 1, SEEK_CUR);
                }
                break;

            /* Single-line comment */
            case '#':
                while ((c = getc(fp)) != '\n' && c != EOF)
                {
                }
                break;

            /* Ignore other characters */
            default:
                break;
        }
    }
}
