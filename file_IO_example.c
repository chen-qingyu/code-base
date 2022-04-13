#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct person
{
    char name[10];
    int age;
    float weight;
};

void file_write(void);
void file_read(void);
void file_print(void);
void file_scan(void);

int main()
{
    // file_write();
    // file_read();
    // file_print();
    // file_scan();

    return 0;
}

void file_write(void)
{
    FILE *fd;

    // Open a new file for writing only
    fd = fopen("sampleFile.dat", "w");
    if (!fd)
    {
        printf("ERROR: Could not open file\n");
        exit(1);
    }

    // Write out a float
    float data = 1078.24;
    fwrite(&data, sizeof(float), 1, fd);

    // Write out a string of 30 chars
    char sentence[30] = "This is a sentence.";
    fwrite(sentence, sizeof(char), 30, fd);

    // Write out a whole array of ints
    int intArray[5] = {12, 34, 56, 78, 90};
    fwrite(intArray, sizeof(intArray), 1, fd);

    // Write out first three elements of the array
    fwrite(intArray, sizeof(int), 3, fd);

    // Write out an array of structs
    struct person friends[4] = {{"Bobby", 19, 143.57}, {"Jenny", 20, 110.32}, {"Fredy", 82, 178.29}, {"Marie", 67, 121.32}};
    fwrite(friends, sizeof(friends), 1, fd);

    // Write out a single friend, Bob
    fwrite(friends, sizeof(struct person), 1, fd);

    // All done ... close the file
    fclose(fd);
}

void file_read(void)
{
    FILE *fd;

    // Open the file for reading only
    fd = fopen("sampleFile.dat", "r");
    if (!fd)
    {
        printf("ERROR: Could not open file\n");
        exit(1);
    }

    // Read in a float
    float data;
    fread(&data, sizeof(float), 1, fd);
    printf("Here is the float: %f\n", data);

    // Read in a string of 30 chars
    char sentence[30];
    fread(sentence, sizeof(char), 30, fd);
    printf("Here is the sentence: \"%s\"\n", sentence);

    // Read in a whole array of ints
    int intArray[5];
    fread(intArray, sizeof(intArray), 1, fd);
    printf("\nHere is the array: { ");
    for (int i = 0; i < 5; i++)
    {
        printf("%d ", intArray[i]);
    }
    printf("}\n");

    // Read in first three elements of the array
    fread(intArray, sizeof(int), 3, fd);
    printf("\nHere are the first three elements of the array: { ");
    for (int i = 0; i < 3; i++)
    {
        printf("%d ", intArray[i]);
    }
    printf("}\n");

    // Read in an array of structs
    struct person friends[4];
    fread(friends, sizeof(friends), 1, fd);
    printf("\nHere are the friends:\n");
    for (int i = 0; i < 4; i++)
    {
        printf("  Name: %s,  Age: %d,  Weight: %f\n", friends[i].name, friends[i].age, friends[i].weight);
    }

    // Read in a single friend
    struct person friend;
    fread(&friend, sizeof(struct person), 1, fd);
    printf("\nHere is the first friend:\n");
    printf("  Name: %s,  Age: %d,  Weight: %f\n", friend.name, friend.age, friend.weight);
    printf("\n");

    fclose(fd); // All done ... close the file
}

void file_print(void)
{
    FILE *fd;

    // Open the file for writing only
    fd = fopen("sampleFile.txt", "w");
    if (!fd)
    {
        printf("ERROR: Could not open file\n");
        exit(1);
    }

    // Write out a float
    float data = 1078.24;
    fprintf(fd, "%f\n", data);

    // Write out a string of 30 chars
    char sentence[30] = "This is a sentence.";
    fprintf(fd, "%-30s\n", sentence);

    // Write out a whole array of ints
    int intArray[5] = {12, 34, 56, 78, 90};
    for (int i = 0; i < 5; i++)
    {
        fprintf(fd, "%d ", intArray[i]);
    }
    fprintf(fd, "\n");

    // Write out first three elements of the array
    for (int i = 0; i < 3; i++)
    {
        fprintf(fd, "%d ", intArray[i]);
    }
    fprintf(fd, "\n");

    // Write out an array of structs
    struct person friends[4] = {{"Bobby", 19, 143.57}, {"Jenny", 20, 110.32}, {"Fredy", 82, 178.29}, {"Marie", 67, 121.32}};
    for (int i = 0; i < 4; i++)
    {
        fprintf(fd, "%s %d %f\n", friends[i].name, friends[i].age, friends[i].weight);
    }

    // Write out a single friend
    fprintf(fd, "%s %d %f\n", friends[0].name, friends[0].age, friends[0].weight);

    // All done ... close the file
    fclose(fd);
}

void file_scan(void)
{
    FILE *fd;

    // Open the file for reading only
    fd = fopen("sampleFile.txt", "r");
    if (!fd)
    {
        printf("ERROR: Could not open file\n");
        exit(1);
    }

    // Read in a float
    float data;
    fscanf(fd, "%f\n", &data);
    printf("Here is the float: %f\n", data);

    // Read in a string of 30 chars
    char sentence[30];
    fscanf(fd, "%30c\n", sentence);
    printf("Here is the sentence: \"%s\"\n", sentence);

    // Read in a whole array of ints
    int intArray[5];
    printf("\nHere is the array: { ");
    for (int i = 0; i < 5; i++)
    {
        fscanf(fd, "%d", &intArray[i]);
        printf("%d ", intArray[i]);
    }
    printf(" }\n");
    fscanf(fd, "\n");

    // Read in first three elements of the array
    printf("\nHere are the first three elements of the array: { ");
    for (int i = 0; i < 3; i++)
    {
        fscanf(fd, "%d", &intArray[i]);
        printf("%d ", intArray[i]);
    }
    printf(" }\n");
    fscanf(fd, "\n");

    // Read in an array of structs
    struct person friends[4];
    printf("\nHere are the friends:\n");
    for (int i = 0; i < 4; i++)
    {
        fscanf(fd, "%s %d %f\n", friends[i].name, &friends[i].age, &friends[i].weight);
        printf("  Name: %s,  Age: %d,  Weight: %f\n", friends[i].name, friends[i].age, friends[i].weight);
    }

    // Read in a single friend
    struct person friend;
    fscanf(fd, "%s %d %f\n", friend.name, &friend.age, &friend.weight);
    printf("\nHere is the first friend:\n");
    printf("  Name: %s,  Age: %d,  Weight: %f\n", friend.name, friend.age, friend.weight);
    printf("\n");

    // All done ... close the file
    fclose(fd);
}