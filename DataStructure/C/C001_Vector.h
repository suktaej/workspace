#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct
{
    int* data;      // 입력될 데이터
    int size;       // 현재 저장된 원소의 개수
    int capacity;   // 할당된 메모리 공간의 총 크기

} DynamicArray;

void InitArray(DynamicArray* arr, int cap);
void FreeArray(DynamicArray* arr);
void Resizing(DynamicArray* arr);
void PrintArray(DynamicArray* arr);

void push_back(DynamicArray* arr, int value);
void pop_back(DynamicArray* arr);
void arr_insert(DynamicArray* arr, int idx, int value);
//void arr_emplace(DynamicArray* arr, int idx, int value);

void arr_erase(DynamicArray* arr, int idx);
void arr_remove(DynamicArray* arr, int value);
void arr_clear(DynamicArray* arr);

int* arr_begin(DynamicArray* arr); // 주소 반환
int* arr_end(DynamicArray* arr);

int arr_front(DynamicArray* arr);  // 값 반환
int arr_back(DynamicArray* arr);
int arr_at(DynamicArray* arr, int idx);

int arr_find(DynamicArray* arr, int value);   // 값의 인덱스 반환, 없으면 -1
bool arr_contains(DynamicArray* arr, int value); // 존재 여부 확인

//int* arr_rbegin(DynamicArray* arr);
//int* arr_rend(DynamicArray* arr);


#endif //DYNAMIC_ARRAY_H