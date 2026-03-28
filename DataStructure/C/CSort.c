#include "CSort.h"

int swap_count = 0;

int main(void)
{
    srand(time(NULL));

    int* arr = NULL;
    int cnt = 0;

    InputRand(&cnt, &arr);
    Selector(&cnt, arr);

    free(arr);

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

    PrintArray(cnt, arr);
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
        int minIdx = i;                     //최소값 index 지정
        for (int j = i + 1;j < *cnt;++j)
        {
            if(*(arr+j) < *(arr+minIdx))    //탐색 중 지정한 최소값보다 작은 값을 발견 시
            minIdx = j;                     //재지정
        }

        if(minIdx!=i)                       //최종 최소값이 기존과 다르다면
          Swap(arr + i, arr + minIdx);  //기존 최소값의 자리와 새 최소값의 자리를 교체
    }
}

void InsertionSort(const int* const cnt, int *const arr)
{
    for(int i=1;i<*cnt;++i) // 정렬되지 않은 부분의 첫 번째 요소부터 시작
                            // i=0은 정렬부로 간주
    {
        int key = *(arr+i);     // 삽입 요소
        int j = i;        // 정렬부의 마지막 요소부터 역순탐색

        while(j>=0 && *(arr+j-1) > key)    //뒤로 미루기 위한 반복문
        {
            *(arr+j) = *(arr+j-1);    // 한 칸 뒤로 이동
            --j;          // 다음요소 확인
        }
        *(arr+j) = key;         // 정렬 된 위치에 키값 삽입
    }
}

void BubbleSort(const int* const cnt, int *const arr)
{
    for(int i=0;i<*cnt-1;++i)
    {
        bool swapFlag = false;

        for(int j=0;j<*cnt-1-i;++j) //마지막 숫자는 정렬 된 상태
                                    //i가 증가할 때 마다 뒤쪽 정렬을 제거(-i)
        {
            if(*(arr+j) > *(arr+j+1))
            {
                Swap(arr+j, arr+j+1);
                swapFlag = true;
            }
        }
        if(!swapFlag)   //Swap이 발생하지 않았다면 정렬이 완료된 상태
           break;
    }
}