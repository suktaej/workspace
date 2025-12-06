#include <iostream>
#include <vector>
#include <limits>

namespace Sort
{
    void Selection(std::vector<int>& arr);
    void Insertion(std::vector<int>& arr);
    void InsertionWithFor(std::vector<int>& arr);
    void Bubble(std::vector<int>& arr);
    void BubbleWithWhile(std::vector<int>& arr);

    void Quick(std::vector<int>& arr);
    void QuickRecursion(int low, int high,std::vector<int>& arr);
    int PartitionLomuto(int low, int high,std::vector<int>& arr);
    int PartitionHoare(int low, int high,std::vector<int>& arr);
    void Merge(std::vector<int>& arr);
};

void Sort::Selection(std::vector<int>& arr)
{
    int count = arr.size();

    for (int i = 0; i < count; ++i)
    {
        int smallest = i;

        for (int j = i + 1; j < count; ++j)
            if (arr[smallest] > arr[j])
                smallest = j;

        std::swap(arr[i], arr[smallest]);
    }
}

void Sort::Insertion(std::vector<int> &arr)
{
    int count = arr.size();

    for (int i = 1; i < count; ++i)
    {
        int key = arr[i];

        int j = i - 1;
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            --j;
        }
        arr[j + 1] = key;
    }
}

void Sort::InsertionWithFor(std::vector<int> &arr)
{
    int count = arr.size();

    for (int i = 1; i < count; ++i)
    {
        int key = arr[i];

        int j;
        for (j = i - 1; j >= 0 && arr[j] > key; --j)
            arr[j+1] = arr[j];
        
        arr[j+1] = key;
    }
}

void Sort::Bubble(std::vector<int>& arr)
{
    int count = arr.size();

    for (int i = 0; i < count - 1; ++i)
        for (int j = 0; j < count - i - 1; ++j)
            if (arr[j] > arr[j + 1])
                std::swap(arr[j], arr[j + 1]);
}

void Sort::BubbleWithWhile(std::vector<int> &arr)
{
    int count = arr.size();

    while(count > 0)
    {
        for(int j =0;j<count-1;++j)
            if(arr[j] > arr[j+1])
                std::swap(arr[j],arr[j+1]);
        
        --count;
    }
}

void Sort::Quick(std::vector<int>& arr)
{
    if (!arr.empty())
        QuickRecursion(0, arr.size() - 1, arr);
}

void Sort::QuickRecursion(int low, int high, std::vector<int> &arr)
{
    if (low < high)
    {
        int pivot = PartitionLomuto(low, high, arr);
        QuickRecursion(low, pivot - 1, arr);
        QuickRecursion(pivot + 1, high, arr);

        // int p = PartitionHoare(low, high, arr);
        // QuickRecursion(low, p, arr);
        // QuickRecursion(p + 1, high, arr);
    }
}

int Sort::PartitionLomuto(int low, int high,std::vector<int>& arr)
{
    int pivot = arr[high];
    int lowIdx = low - 1;

    for (int i = low; i < high; ++i)
    {
        if(arr[i] < pivot)
        {
            ++lowIdx;
            std::swap(arr[i], arr[lowIdx]);
        }
    }

    std::swap(arr[lowIdx + 1], arr[high]);

    return lowIdx + 1;
}

int Sort::PartitionHoare(int low, int high, std::vector<int>& arr)
{
    int pivot = arr[low];
    int lowIdx = low - 1;
    int highIdx = high + 1;

    while (true)
    {
        do 
        {
            lowIdx++;
        } while (arr[lowIdx] < pivot);

        do 
        {
            highIdx--;
        } while (arr[highIdx] > pivot);

        if (lowIdx >= highIdx)
            return highIdx;

        std::swap(arr[lowIdx], arr[highIdx]);
    }
}

int main()
{
    std::vector<int> inp = {10, 30, 25, 60, 40, 20, 50};
    // Sort::Selection(inp);
    // Sort::Bubble(inp);
    // Sort::BubbleWithWhile(inp);
    // Sort::Insertion(inp);
    Sort::Quick(inp);
    
    for (const auto &it : inp)
        std::cout << it << " ";

    return 0;
}