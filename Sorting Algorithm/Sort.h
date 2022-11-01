#ifndef SORT_H
#define SORT_H

#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define SIZE 100          // Maximum number of elements
#define Sedgewick_SIZE 10 // For shellSort()
#define CUTOFF 50         // For quickSort()
#define MAX_DIGIT 5       // For radixSort()
#define RADIX 10          // For radixSort()

typedef int item_t;

void bubbleSort(item_t arr[], int n);
void insertionSort(item_t arr[], int n);
void shellSort(item_t arr[], int n);
void selectionSort(item_t arr[], int n);
void heapSort(item_t arr[], int n);
void mergeSort(item_t arr[], int n);
void quickSort(item_t arr[], int n);
void radixSort(item_t arr[], int n);

#endif
