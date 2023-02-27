#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void file_write(void);
void file_read(void);
void file_print(void);
void file_scan(void);

int main()
{
    file_write();
    file_read();
    file_print();
    file_scan();

    printf("OK\n");

    return 0;
}

struct person
{
    char name[10];
    int age;
};

#define SENTENCE_LEN 30
#define INT_ARRAY_LEN 5
#define FRIEND_ARRAY_LEN 5

struct data_set
{
    float number;
    char sentence[SENTENCE_LEN];
    int integers[INT_ARRAY_LEN];
    struct person friends[FRIEND_ARRAY_LEN];
};

struct data_set out_data = {
    233.333333,
    "This is a sentence.",
    {12, 34, 56, 78, 90},
    {
        {"Alice", 18},
        {"Sakura", 19},
        {"Homura", 20},
        {"Mei", 17},
        {"Yuzu", 18},
    },
};

void file_write(void)
{
    // Open file for writing only
    FILE* fd = fopen("file_io.dat", "w");
    if (fd == NULL)
    {
        printf("ERROR: Could not open file\n");
        exit(EXIT_FAILURE);
    }

    // Write out a float
    fwrite(&out_data.number, sizeof(float), 1, fd);

    // Write out a string
    fwrite(out_data.sentence, sizeof(char), SENTENCE_LEN, fd);

    // Write out an array of integers
    fwrite(out_data.integers, sizeof(int), INT_ARRAY_LEN, fd);

    // Write out an array of structs
    fwrite(out_data.friends, sizeof(struct person), FRIEND_ARRAY_LEN, fd);

    // All done ... close the file
    fclose(fd);
}

void file_read(void)
{
    printf("file_read():\n");

    // Open file for reading only
    FILE* fd = fopen("file_io.dat", "r");
    if (fd == NULL)
    {
        printf("ERROR: Could not open file\n");
        exit(EXIT_FAILURE);
    }

    // Prepare the space
    struct data_set in_data;

    // Read in a float
    fread(&in_data.number, sizeof(float), 1, fd);
    printf("Here is the float: %f\n", in_data.number);

    // Read in a string
    fread(in_data.sentence, sizeof(char), SENTENCE_LEN, fd);
    printf("Here is the sentence: \"%s\"\n", in_data.sentence);

    // Read in an array of integers
    fread(in_data.integers, sizeof(int), INT_ARRAY_LEN, fd);
    printf("Here is the array: { ");
    for (int i = 0; i < INT_ARRAY_LEN; i++)
    {
        printf("%d ", in_data.integers[i]);
    }
    printf("}\n");

    // Read in an array of structs
    fread(in_data.friends, sizeof(struct person), FRIEND_ARRAY_LEN, fd);
    printf("Here are the friends:\n");
    for (int i = 0; i < FRIEND_ARRAY_LEN; i++)
    {
        printf("- name: %s, age: %d\n", in_data.friends[i].name, in_data.friends[i].age);
    }

    // All done ... close the file
    fclose(fd);
}

void file_print(void)
{
    // Open file for writing only
    FILE* fd = fopen("file_io.txt", "w");
    if (fd == NULL)
    {
        printf("ERROR: Could not open file\n");
        exit(EXIT_FAILURE);
    }

    // Write out a float
    fprintf(fd, "%f\n", out_data.number);

    // Write out a string
    fprintf(fd, "%-30s\n", out_data.sentence);

    // Write out an array of integers
    for (int i = 0; i < INT_ARRAY_LEN; i++)
    {
        fprintf(fd, "%d ", out_data.integers[i]);
    }
    fprintf(fd, "\n");

    // Write out an array of structs
    for (int i = 0; i < FRIEND_ARRAY_LEN; i++)
    {
        fprintf(fd, "%s %d\n", out_data.friends[i].name, out_data.friends[i].age);
    }

    // All done ... close the file
    fclose(fd);
}

void file_scan(void)
{
    printf("file_scan():\n");

    // Open file for reading only
    FILE* fd = fopen("file_io.txt", "r");
    if (fd == NULL)
    {
        printf("ERROR: Could not open file\n");
        exit(EXIT_FAILURE);
    }

    // Prepare the space
    struct data_set in_data;

    // Read in a float
    fscanf(fd, "%f\n", &in_data.number);
    printf("Here is the float: %f\n", in_data.number);

    // Read in a string
    fscanf(fd, "%30c\n", in_data.sentence);
    printf("Here is the sentence: \"%s\"\n", in_data.sentence);

    // Read in an array of integers
    printf("Here is the array: { ");
    for (int i = 0; i < INT_ARRAY_LEN; i++)
    {
        fscanf(fd, "%d ", &in_data.integers[i]);
        printf("%d ", in_data.integers[i]);
    }
    fscanf(fd, "\n");
    printf("}\n");

    // Read in an array of structs
    printf("Here are the friends:\n");
    for (int i = 0; i < FRIEND_ARRAY_LEN; i++)
    {
        fscanf(fd, "%s %d\n", in_data.friends[i].name, &in_data.friends[i].age);
        printf("- name: %s, age: %d\n", in_data.friends[i].name, in_data.friends[i].age);
    }

    // All done ... close the file
    fclose(fd);
}
