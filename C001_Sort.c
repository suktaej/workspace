#include "C001_Sort.h"

int swap_count = 0;

int main(void)
{
    srand(time(NULL));

    int* arr = NULL;
    int cnt = 0;

    InputRand(&cnt, &arr);

    clock_t start = clock();
    Selector(&cnt, arr);
    clock_t end = clock();

    free(arr);

    double time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Execution time: %.6f seconds\n", time_spent);
    printf("Total swaps: %d\n", swap_count);

    return 0;
}

void InputRand(int* cnt, int** arr)
{
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
        bool bIsDuplicate = false;

        for (int j = 0; j < i; ++j)
        {
            if (*(*arr + j) == temp)
            {
                bIsDuplicate = true;
                break;
            }
        }

        if (!bIsDuplicate)
        {
            *(*arr + i) = temp;
            ++i;
        }
    }
    
    PrintArray(cnt, *arr);
}

void Selector(const int* const cnt, int *const arr)
{
    const char *SortTypeNames[] = {"Selection", "Insertion", "Bubble", "Quick", "Merge", "Heap", "Counting", "Radix"};
    int inp = 0;

    printf("Select Sort Alg\n");

    for (int i = 0; i < End; ++i)
        printf("%d. %s\n", i, SortTypeNames[i]);
    printf("> ");

    scanf("%d", &inp);

    switch (inp)
    {
    case Selection:
        SelectionSort(cnt, arr);
        break;
    case Insertion:
        InsertionSort(cnt, arr);
        break;
    case Bubble:
        BubbleSort(cnt ,arr);
        break;
    case Quick:
        break;
    case Merge:
        break;
    case Heap:
        break;
    case Counting:
        break;
    case Radix:
        break;
    default:
        break;
    }

    PrintArray(cnt, arr);
}

void Swap(int *a,int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
    swap_count++;
}

void PrintArray(const int *const cnt, const int *const arr)
{
    for (int i = 0;i < *cnt;++i)
        printf("%d ", *(arr + i));
    printf("\n");
}

void SelectionSort(const int* const cnt, int *const arr)
{
    for (int i = 0;i < *cnt - 1;++i)
    {
        int minIdx = i;
        for (int j = i + 1;j < *cnt;++j)
        {
            if(*(arr+j) < *(arr+minIdx))
            minIdx = j;
        }

        if(minIdx!=i)
          Swap(arr + i, arr + minIdx);
    }
}

void InsertionSort(const int* const cnt, int *const arr)
{
    for(int i=1;i<*cnt;++i) // 정렬되지 않은 부분의 첫 번째 요소부터 시작
                            // i=0은 정렬부로 간주
    {
        int key = *(arr+i);     // 삽입 요소
        int j = i-1;        // 정렬부의 마지막 요소부터 역순탐색

        while(j>=0 && *(arr+j) > key)
        {
            *(arr+j+1) = *(arr+j);    // 한 칸 뒤로 이동
            --j;          // 다음요소 확인
        }
        *(arr+j+1) = key;         // 정렬 된 위치에 키값 삽입
    }
}

void BubbleSort(const int* const cnt, int *const arr)
{

}