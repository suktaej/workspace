#ifndef SORT_ALGORITHMS_H
#define SORT_ALGORITHMS_H

#include <stdio.h> 
#include <stdlib.h> 
#include <stdbool.h>
#include <time.h>   

#define MAX_SIZE 100

enum ESortType
{
    Selection,
    Insertion,
    Bubble,
    Quick,
    Merge,
    Heap,
    Counting,
    Radix,
    End
};

extern int swap_count; 

void InputRand(int* cnt, int** arr);
void Selector(const int* const cnt, int *const arr);
void Swap(int *a, int *b);
void PrintArray(const int *const cnt, const int *const arr);

void SelectionSort(const int* const cnt, int *const arr);
void InsertionSort(const int* const cnt, int *const arr); 
void BubbleSort(const int* const cnt, int *const arr);

#endif // SORT_ALGORITHMS_H