#include "C001_Vector.h"

int main(void)
{
    DynamicArray arr;
    InitArray(&arr, 4);

    push_back(&arr, 10);
    push_back(&arr, 20);
    push_back(&arr, 30);
    pop_back(&arr);
    push_back(&arr, 40);
    arr_insert(&arr, 0, 5);
    arr_erase(&arr, 1);

    PrintArray(&arr);
    FreeArray(&arr);

    return 0;
}