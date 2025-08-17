#include "C001_Vector.h"

void InitArray(DynamicArray* arr, int cap)
{
    arr->data = (int*)malloc(sizeof(int) * cap);
    arr->size = 0;
    arr->capacity = cap;
}

void FreeArray(DynamicArray* arr)
{
    free(arr->data);
    arr->data = NULL;

    arr->size = 0;
    arr->capacity = 0;
}

void push_back(DynamicArray* arr, int value)
{
    if (arr->capacity == arr->size)
        Resizing(arr);

    //arr->data[arr->size++] = value;
    *(arr->data + arr->size) = value;
    ++arr->size;
}

void pop_back(DynamicArray* arr)
{
    if (0 == arr->size)
        return;

    --arr->size;
}

void arr_insert(DynamicArray* arr, int idx, int value)
{
    if (idx < 0 || idx > arr->size)
        return;

    if (arr->size == arr->capacity)
        Resizing(arr);

    for (int i = arr->size; i > idx; --i)
        *(arr->data + i) = *(arr->data + (i - 1));

    *(arr->data + idx) = value;
    ++arr->size;
}

void arr_erase(DynamicArray* arr, int idx)
{
    if (idx < 0 || idx >= arr->size)
        return;

    for (int i = idx; i < arr->size -1; ++i)
        *(arr->data + i) = *(arr->data + (i + 1));

    --arr->size;
}

void arr_remove(DynamicArray* arr, int value)
{
    if (arr == NULL || arr->size == 0)
        return;

    for (int i = 0; i < arr->size; ++i)
    {
        if (*(arr->data + i) == value)
        {
            for (int j = i; j < arr->size; ++j)
                *(arr->data + j) = *(arr->data + (j + 1));

            --arr->size;
            break;
        }
    }
}

void arr_clear(DynamicArray* arr)
{
    arr->size = 0;
}

int arr_at(DynamicArray* arr, int idx)
{
    if (idx < 0 || idx >= arr->size)
        return -1;

    return *(arr->data + idx);
}

int arr_front(DynamicArray* arr)
{
    return *(arr->data);
}

int arr_back(DynamicArray* arr)
{
    if (arr->size == 0)
        return -1;

    return *(arr->data+arr->size-1);
}

int arr_find(DynamicArray* arr, int value)
{
    for (int i = 0; i < arr->size; ++i)
    {
        if (*(arr->data + i) == value)
            return i;
    }
    return -1;
}

bool arr_contains(DynamicArray* arr, int value)
{
    for (int i = 0; i < arr->size; ++i)
    {
        if (*(arr->data + i) == value)
            return true;
    }
    return false;
}

int* arr_begin(DynamicArray* arr)
{
    return arr->data;
}

int* arr_end(DynamicArray* arr)
{
    return arr->data + arr->size;
}

void Resizing(DynamicArray* arr)
{
    // 저장 가능한 용량(capacity)을 2배로 증가
    // 새로운 데이터 공간을 생성
    int newCap = arr->capacity * 2;
    int* newData = (int*)malloc(sizeof(int) * newCap);

    // 새 데이터에 기존 데이터를 복사
    // 복사하는 크기는 size
    for (int i = 0; i < arr->size; ++i)
        //newData[i] = arr->data[i];
        *(newData + i) = *(arr->data + i);

    // 기존 동적할당 된 data메모리 해제
    free(arr->data);
    // 새로 할당한 메모리로 data 포인터를 교체
    arr->data = newData;
    // 최대 용량 갱신
    arr->capacity = newCap;
}

void PrintArray(DynamicArray* arr)
{
    for (int i = 0; i < arr->size; ++i)
        printf("%d\t", *(arr->data + i));

    printf("\n");
}