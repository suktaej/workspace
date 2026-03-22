#include <iostream>
#include <algorithm>
#include <vector>

class ListNode
{
private:
    int val;
    ListNode* nextNode;

public:
    ListNode(int x, ListNode* next) : val(x), nextNode(next){}

public:
    ListNode* insertionSort(ListNode* head)
    {

    }
};

constexpr int n = 9;
int arr[n] = {1, 7, 4, 9, 2, 8, 3, 6, 5};

void selectionSort()
{
    for (int i = 0; i < n; ++i)
    {
        int temp = i;
        for (int j = i + 1; j < n; ++j)
        {
            if (arr[temp] > arr[j])
                temp = j;
        }
        if(temp!=i)
            std::swap(arr[temp],arr[i]);
    }
}

void insertionSort()
{
    for (int i = 1; i < n; ++i)
    {
        int key = arr[i];
        int j = i-1;

        while (j >= 0)
        {
            if(arr[j] < key)
                break;

            arr[j+1] = arr[j];
            --j;
        }

        arr[j+1] = key;
    }
}



int main()
{
    for (int i = 0; i < n; ++i)
        std::cout<<arr[i]<<' ';

    insertionSort();
    std::cout<<std::endl;
    
    for (int i = 0; i < n; ++i)
        std::cout<<arr[i]<<' ';

    return 0;
}