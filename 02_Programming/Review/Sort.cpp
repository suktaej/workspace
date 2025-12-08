#include <iostream>
#include <vector>
#include <limits>
#include <thread>
#include <functional>
#include <iterator>
#include <algorithm>

namespace Sort
{
    void SelectionSort(std::vector<int>& arr);
    void InsertionSort(std::vector<int>& arr);
    void InsertionWithFor(std::vector<int>& arr);
    void BubbleSort(std::vector<int>& arr);
    void BubbleWithWhile(std::vector<int>& arr);

    void QuickSort(std::vector<int>& arr);
    void QuickRecursion(std::vector<int>::iterator begin,std::vector<int>::iterator end);
    std::vector<int>::iterator Partition(std::vector<int>::iterator begin,std::vector<int>::iterator end);

    void MergeSort(std::vector<int>& arr);
    void Divide(std::vector<int>::iterator begin, std::vector<int>::iterator end);
    void Merge(std::vector<int>::iterator begin, std::vector<int>::iterator mid, std::vector<int>::iterator end);
};

class QuickSort
{
private:
    std::vector<int> arr;

public:
    QuickSort() {}
    QuickSort(const std::vector<int> &vec)
        : arr(vec) {}

public:
    void SetVector(const std::vector<int> &vec)
    {
        arr = vec;
    }

    void Sort()
    {
        Recursive(0,arr.size()-1);
    }

    void Recursive(int low, int high)
    {
        if(low < high)
        {
            int pivot = PartitionHoare(low, high);
            Recursive(low, pivot);
            Recursive(pivot+1,high);
        }
    }

    int PartitionLomuto(int low, int high)
    {
        int pivot = arr[high];
        int lowIdx = low - 1;

        for (int i = low; i < high; ++i)
        {
            if (arr[i] < pivot)
            {
                ++lowIdx;
                std::swap(arr[i], arr[lowIdx]);
            }
        }

        std::swap(arr[lowIdx + 1], arr[high]);

        return lowIdx + 1;
    }

    int PartitionHoare(int low, int high)
    {
        int pivot = arr[low];
        int lowIdx = low -1;
        int highIdx  = high + 1;

        while(true)
        {
            do
                ++lowIdx;
            while (arr[lowIdx] < pivot);

            do
                --highIdx;
            while (arr[highIdx] > pivot);

            if (lowIdx >= highIdx)
                return highIdx;

            std::swap(arr[lowIdx], arr[highIdx]);
        }
    }

    void Print()
    {
        for (const auto &it : arr)
            std::cout << it << " ";
    }
};

class MergeSort
{
private:
    std::vector<int> arr;
    std::vector<int> temp;

public:
    MergeSort() {}
    MergeSort(const std::vector<int> &vec)
        : arr(vec) {}

public:
    void SetVector(const std::vector<int> &vec)
    {
        arr = vec;
    }

    void Sort()
    {
        if (!arr.empty())
        {
            temp.resize(arr.size());
            Divide(0, arr.size() - 1);
        }
    }

    void Divide(int left, int right)
    {
        if (left < right)
        {
            int mid = left + (right - left) / 2;
            Divide(left, mid);
            Divide(mid + 1, right);
            Merge(left, mid, right);
        }
    }

    void Merge(int left, int mid, int right)
    {
        int lSize = mid - left + 1;
        int rSize = right - mid;    // right - (mid + 1) + 1

        std::vector<int> lVec(lSize);
        std::vector<int> rVec(rSize);

        for (int i = 0; i < lSize; ++i)
            lVec[i] = arr[left + i];
        for (int i = 0; i < rSize; ++i)
            rVec[i] = arr[mid + 1 + i];

        int lIdx = 0;
        int rIdx = 0;
        int iter = left;

        while (lIdx < lSize && rIdx < rSize)
        {
            if (lVec[lIdx] <= rVec[rIdx])
                arr[iter++] = lVec[lIdx++];
            else
                arr[iter++] = rVec[rIdx++];
        }

        while (lIdx < lSize)
            arr[iter++] = lVec[lIdx++];
        while (rIdx < rSize)
            arr[iter++] = rVec[rIdx++];
    }
    
    void MergeUsingTemp(int left, int mid, int right)
    {
        for(int i = left; i<= right ;++i)
            temp[i] = arr[i];

        int lIdx = left;
        int rIdx = mid + 1;
        int iter = left;

        while(lIdx <= mid && rIdx <= right)
        {
            if(temp[lIdx] <= temp[rIdx])
                arr[iter++] = temp[lIdx++];
                else
                arr[iter++] = temp[rIdx++];
        }

        while(lIdx <= mid)
            arr[iter++] = temp[lIdx++];
    }

    void Print()
    {
        for (const auto &it : arr)
            std::cout << it << " ";
    }
};

void Sort::SelectionSort(std::vector<int>& arr)
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

void Sort::InsertionSort(std::vector<int> &arr)
{
    int count = arr.size();

    for (int i = 1; i < count; ++i)
    {
        int key = arr[i];
        int j = i - 1;
        
        while (j >= 0 && arr[j] > key)
        {
            arr[j+1] = arr[j];
            --j;
        }

        arr[j+1] = key;
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

void Sort::BubbleSort(std::vector<int>& arr)
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

void Sort::QuickSort(std::vector<int>& arr)
{
    if (!arr.empty())
        QuickRecursion(arr.begin(),arr.end());
}

void QuickRecursion(std::vector<int>::iterator begin, std::vector<int>::iterator end)
{
    std::ptrdiff_t size = std::distance(begin,end);

    if(size < 2)
        return;

    std::vector<int>::iterator pivot = Partition(begin,end);
    QuickRecursion(begin,pivot);
    QuickRecursion(std::next(pivot),end);
}

std::vector<int>::iterator Partition(std::vector<int>::iterator begin, std::vector<int>::iterator end)
{
    int pivot = *begin;
    std::vector<int>::iterator store = std::next(begin);

    for (std::vector<int>::iterator it = std::next(begin); it != end; ++it)
    {
        if(*it < pivot)
        {
            std::iter_swap(it,store);
            ++store;
        }
    }

    std::vector<int>::iterator pivotPos = std::prev(store);
    std::iter_swap(begin,pivotPos);

    return pivotPos;
}

void Sort::MergeSort(std::vector<int> &arr)
{
    if(!arr.empty())
        Divide(arr.begin(),arr.end());
}

void Sort::Divide(std::vector<int>::iterator begin, std::vector<int>::iterator end)
{
    std::ptrdiff_t size = std::distance(begin,end);

    if(size < 2)
        return;

    std::vector<int>::iterator mid = begin + size / 2;
    Divide(begin, mid);
    Divide(mid, end);
    Merge(begin, mid, end);
}

void Sort::Merge(std::vector<int>::iterator begin, std::vector<int>::iterator mid, std::vector<int>::iterator end)
{
    std::vector<int> temp;
    temp.reserve(std::distance(begin,end));

    std::vector<int>::iterator lIdx = begin;
    std::vector<int>::iterator rIdx = mid;

    while (lIdx != mid && rIdx != end)
    {
        if(*lIdx <= *rIdx)
        {
            temp.push_back(*lIdx);
            ++lIdx;
        }
        else
        {
            temp.push_back(*rIdx);
            ++rIdx;
        }
    }

    temp.insert(temp.end(),lIdx,mid);
    temp.insert(temp.end(),rIdx,end);
    // std::copy(lIdx,mid,std::back_inserter(temp));
    // std::copy(rIdx,end,std::back_inserter(temp));
    std::copy(temp.begin(), temp.end(), begin);
}

int main()
{
    std::vector<int> inp = {10, 30, 25, 60, 40, 20, 50};
    // Sort::SelectionSort(inp);
    // Sort::BubbleSort(inp);
    // Sort::BubbleWithWhile(inp);
    // Sort::InsertionSort(inp);
    // Sort::QuickSort(inp);
    Sort::MergeSort(inp);
    
    for (const auto &it : inp)
        std::cout << it << " ";

    // QuickSort q(inp);
    // q.Sort();
    // q.Print();

    // MergeSort m(inp);
    // m.Sort();
    // m.Print();

    return 0;
}