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
    int temp;

    srand(time(NULL));

    printf("Input Random Number:");
    scanf("%d", cnt);

    if (*cnt <= 0)
        *cnt = 1;

    *arr = (int*)malloc(*cnt * sizeof(int));
    
    for (int i = 0; i < *cnt; ++i)
    {
        temp = (rand() % MAX_SIZE);
        *((*arr) + i) = temp;

        for (int j = 0; j < i; ++j)
        {
            if (*((*arr) + j) == temp)
            {
                --i;
                printf("%d is duplicate\n",temp);
                break;
            }
        }
        printf("%d\n", *((*arr) + i));
    }
}