#include <stdio.h>
#include <string.h>
#define LEN 20

enum spectrum
{
    red,
    orange,
    yellow,
    green,
    cyan,
    blue,
    purple,
    black,
    white
} color;

const char *colors[] = {"red", "orange", "yellow", "green", "cyan",
                        "blue", "purple", "black", "white"};

int main(void)
{
    char input[LEN];
    int found = 0;
    puts("Please enter a color (enter q to quit):");
    while (scanf("%s", input) && input[0] != 'q')
    {
        for (int i = 0; i < sizeof(input); i++)
        {
            if (input[i] >= 'A' && input[i] <= 'Z')
            {
                input[i] += 32;
            }
        }
        for (color = red; color <= white; color++)
        {
            if (strcmp(input, colors[color]) == 0)
            {
                found = 1;
                break;
            }
        }
        if (found)
        {
            switch (color)
            {
                case red:
                    puts("Red like roses fills my dreams and brings me to the place you rest.");
                    break;
                case orange:
                    puts("Orange is warm, like summer citrus.");
                    break;
                case yellow:
                    puts("Yellow beauty burns gold.");
                    break;
                case green:
                    puts("Green is full of vitality, bringing spring.");
                    break;
                case cyan:
                    puts("Cyan is me.");
                    break;
                case blue:
                    puts("Blue is the sky, vast expanse.");
                    break;
                case purple:
                    puts("Purple is passionate and noble.");
                    break;
                case black:
                    puts("Black the beast descends from shadows.");
                    break;
                case white:
                    puts("White is cold and always yearning burdened by a royal test.");
                    break;
            }
        }
        else
        {
            printf("I don't know about the \"%s\"\n", input);
        }
        found = 0;
        puts("\nNext color, please (enter q to quit):");
    }
    puts("\nGoodbye~");

    return 0;
}
