#include <iostream>
#include <vector>

// avgCount : 내부 학생의 수
// avg : 학생배열 포인터
// return : 가장 적게 움직일 수 있는 턴 수
// 1번에 1칸만 이동
int minMoves(int avgCount, int* avg)
{
    int LMove = 0;
    int RMove = 0;
    int zeroCount = 0;

    for(int i= avgCount -1; i>=0; --i)
    {
        if(avg[i] == 0)
            ++zeroCount;
        else
            RMove += zeroCount;
    }

    zeroCount = 0;
    for(int i=0;i<avgCount;++i)
    {
        if(avg[i] ==0)
            ++zeroCount;
        else
            LMove += zeroCount;
    }
    /*
    int* arr = (int*)malloc(avgCount*sizeof(int));
    int lArr = 0;
    int rArr = 0;

    memcpy(arr,avg,avgCount*sizeof(int));

    for(int i=0;i<avgCount-1;++i)
        for(int j=0;j<avgCount-1-i;++j)
            if(arr[j] == 1 && arr[j+1] == 0)
            {
                ++rArr;
                std::swap(arr[j],arr[j+1]);
            }
    */

    return (LMove < RMove) ? LMove : RMove;
}

int main()
{
    int arr[] = {1,0,1,0,1,1,1,1};
    int size = sizeof(arr)/sizeof(int);
    minMoves(size,arr);
    return 0;
}