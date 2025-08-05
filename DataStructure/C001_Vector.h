#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <stdio.h>
#include <stdlib.h>

typedef struct 
{
    int* data;      // 입력될 데이터
    int size;       // 현재 저장된 원소의 개수
    int capacity;   // 할당된 메모리 공간의 총 크기

} DynamicArray;

void InitArray(DynamicArray* arr,int cap);
void FreeArray(DynamicArray* arr);
void push_back(DynamicArray* arr,int value);
void pop_back(DynamicArray* arr);
void arr_insert(DynamicArray* arr, int idx, int value);
//void arr_emplace(DynamicArray* arr, int idx, int value);
void arr_erase(DynamicArray* arr, int idx);
void arr_remove(DynamicArray* arr, int value);

void arr_clear(DynamicArray* arr);
void arr_swap(DynamicArray* arr,DynamicArray* swapArr);
int* arr_begin(DynamicArray* arr);
int* arr_end(DynamicArray* arr);
int* arr_rbegin(DynamicArray* arr);
int* arr_rend(DynamicArray* arr);
int* arr_at(DynamicArray* arr,int idx);
int* arr_front(DynamicArray* arr);
int* arr_back(DynamicArray* arr);
int get_size(DynamicArray* arr);
int get_capacity(DynamicArray* arr);
void Resizing(DynamicArray *arr);
void PrintArray(DynamicArray *arr);

#endif //DYNAMIC_ARRAY_H