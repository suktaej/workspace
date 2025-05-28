#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define MAX_SIZE 100

void InputRand(int*, int**);

int main(void)
{
    int* arr = NULL;
    int cnt = 0;

    InputRand(&cnt, &arr);
    
    for (int i = 0;i < cnt;++i)
    {
        if (i%5==0)
            printf("\n");
        printf("%d\t", *(arr + i));
    }

    free(arr);

    return 0;
}

void InputRand(int* cnt, int** arr)
{
    srand(time(NULL));

    printf("Input Random Number:");
    scanf("%d", cnt);

    if (*cnt <= 0)
        *cnt = 1;
    else if (*cnt > MAX_SIZE)
        *cnt = MAX_SIZE;

    *arr = (int*)malloc(*cnt * sizeof(int));
    
    if (*arr == NULL)
    {
        printf("Memory allocation failed.\n");
        exit(1);
    }

    int i = 0;
    while (i < *cnt)
    {
        int temp = rand() % MAX_SIZE;
        int isDuplicate = 0;

        for (int j = 0; j < i; ++j)
        {
            if (*(*arr+j) == temp)
            {
                isDuplicate = 1;
                break;
            }
        }

        if (!isDuplicate)
        {
            *(*arr+i) = temp;
            ++i;
        }
    }
}