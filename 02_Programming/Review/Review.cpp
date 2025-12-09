#include <iostream>
#include <vector>
#include <algorithm>

using intIter = std::vector<int>::iterator;

namespace Sort
{
    void InsertionSort(std::vector<int>& vec);
    void BubbleSort(std::vector<int>& vec);
    void SelectionSort(std::vector<int>& vec);

    void QuickSort(intIter low,intIter high);
    intIter Partition(intIter low, intIter high);
}

class QuickSort
{
private:
    std::vector<int> vec;

public:
    QuickSort() {}
    QuickSort(std::vector<int> inp)
        : vec(inp) {}

public:
    void Sort()
    {
        if(!vec.empty())
            LomutoRecursion(0, vec.size()-1);
        
        for(const int& val : vec)
            std::cout<<val<<" ";
    }

private:
    void HoareRecursion(int low, int high)
    {
        if(low < high)
        {
            int pivot = HoarePartition(low, high);
            HoareRecursion(low, pivot);
            HoareRecursion(pivot + 1, high);
        }
    }
    
    void LomutoRecursion(int low, int high)
    {
        if(low < high)
        {
            int pivot = LomutoPartition(low, high);
            LomutoRecursion(low, pivot - 1);
            LomutoRecursion(pivot + 1, high);
        }
    }

    int LomutoPartition(int low, int high)
    {
        int pivot = vec[high];
        int iterIdx = low - 1;

        for (int i = low; i < high; ++i)
        {
            if (vec[i] < pivot)
            {
                ++iterIdx;
                std::swap(vec[i],vec[iterIdx]);
            }
        }

        ++iterIdx;
        std::swap(vec[iterIdx], vec[high]);

        return iterIdx;
    }
    
    int HoarePartition(int low, int high)
    {
        int pivot = vec[low];
        int lIdx = low - 1;
        int hIdx = high + 1;

        while(true)
        {
            do
                ++lIdx;
            while (vec[lIdx] < pivot);

            do
                --hIdx;
            while (vec[hIdx] > pivot);

            if (lIdx >= hIdx)
                return hIdx;

            std::swap(vec[lIdx], vec[hIdx]);
        }
    }
};

class MergeSort
{
private:
    std::vector<int> vec;
    std::vector<int> temp;

public:
    MergeSort(){}
    MergeSort(std::vector<int> inp)
    : vec(inp){}

public:
    void Sort()
    {
        temp.resize(vec.size());
        if (!vec.empty())
            Recursion(0, vec.size() - 1);

        for (const int &val : vec)
            std::cout << val << " ";
    }

private:
    void Recursion(int left, int right)
    {
        if(left < right)
        {
            int mid = left + (right - left) / 2;
            Recursion(left, mid);
            Recursion(mid + 1, right);
            MergeUsingTemp(left, mid, right);
        }
    }

    void Merge(int left, int mid, int right)
    {
        int lSize = mid - left + 1;
        int rSize = right - mid;
        std::vector<int> lVec(lSize);
        std::vector<int> rVec(rSize);

        for (int i = 0; i < lSize; ++i)
            lVec[i] = vec[left + i];
        for (int i = 0; i < rSize; ++i)
            rVec[i] = vec[mid + 1 + i];

        int lIdx = 0;
        int rIdx = 0;
        int iter = left;

        while(lIdx < lSize && rIdx < rSize)
        {
            if(lVec[lIdx] <= rVec[rIdx])
                vec[iter++] = lVec[lIdx++];
            else
                vec[iter++] = rVec[rIdx++];
        }

        while(lIdx < lSize)
            vec[iter++] = lVec[lIdx++];
        while(rIdx < rSize)
            vec[iter++] = rVec[rIdx++];
    }

    void MergeUsingTemp(int left, int mid, int right)
    {
        for(int i = left; i<= right; ++i)
            temp[i] = vec[i];

        int lIdx = left;
        int rIdx = mid + 1;
        int iter = left;

        while(lIdx <= mid && rIdx <= right)
        {
            if(temp[lIdx] <= temp[rIdx])
                vec[iter++] = temp[lIdx++];
            else
                vec[iter++] = temp[rIdx++];
        }

        while(lIdx <= mid)
            vec[iter++] = temp[lIdx++];
    }
};

class NumberOfCase
{
private:
    std::vector<int> vec;
    std::vector<int> bundle;
    std::vector<bool> dup;
    std::vector<std::vector<int>> res;
    int n;
    int p;

public:
    NumberOfCase(std::vector<int> inp, int count)
        : vec(inp), n(inp.size()), p(count) 
        {
            dup.resize(n,false);
        }

public:
    void Per()
    {
        res.clear();
        bundle.clear();
        std::fill(dup.begin(),dup.end(),false);

        Permutation(p,bundle,dup);
        Print();
    }

    void Com()
    {
        res.clear();

        Combination(0,p,bundle);
        Print();
    }
    
private:
    void Permutation(int toPick, std::vector<int>& picked, std::vector<bool>& used)
    {
        // Base Case
        if(0==toPick)
        {
            res.push_back(picked);
            return;
        }

        for (int i = 0; i < n; ++i)
        {
            if(used[i])
                continue;
            
            picked.push_back(vec[i]);
            used[i] = true;
            Permutation(toPick-1,picked,used);
            picked.pop_back();
            used[i] = false;
        }
    }

    void Combination(int start, int toPick, std::vector<int>& picked)
    {
        // Base Case
        if (0 == toPick)
        {
            res.push_back(picked);
            return;
        }

        for (int i = start; i < n; ++i)
        {
            picked.push_back(vec[i]);
            Combination(i + 1, toPick - 1, picked);
            picked.pop_back();
        }
    }

    void Print() const
    {
        for (const auto &vecItem : res)
        {
            std::cout << "(";
            for (size_t i = 0; i < vecItem.size(); ++i)
            {
                std::cout << vecItem[i];
                if (i + 1 < vecItem.size())
                    std::cout << ",";
            }
            std::cout << ") ";
        }
    }
};

void Sort::InsertionSort(std::vector<int>& vec)
{
    int size = vec.size();

    for (int i = 0; i < size; ++i)
    {
        int minIdx = i;

        for (int j = i + 1; j < size; ++j)
            if (vec[minIdx] > vec[j])
                minIdx = j;
        
        std::swap(vec[i],vec[minIdx]);
    }
}

void Sort::BubbleSort(std::vector<int>& vec)
{
    int size = vec.size();

    for (int i = 0; i < size - 1; ++i)
        for (int j = 0; j < size - i - 1; ++j)
            if(vec[j] > vec[j+1])
                std::swap(vec[j], vec[j + 1]);
}

void Sort::SelectionSort(std::vector<int> &vec)
{
    int size = vec.size();

    for (int i = 1; i < size; ++i)
    {
        int key = vec[i];
        int j = i - 1;

        while (j >= 0 && vec[j] > key)
        {
            vec[j+1] = vec[j];
            --j;
        }

        vec[j + 1] = key;
    }
}

void Sort::QuickSort(intIter low, intIter high)
{
    std::ptrdiff_t dist = std::distance(low,high);

    if(dist < 2)
        return;

    intIter pivot = Partition(low,high);
    QuickSort(low,pivot);
    QuickSort(std::next(pivot),high);
}

intIter Sort::Partition(intIter low, intIter high)
{
    int pivot = *low;
    intIter store = std::next(low);

    for (intIter it = std::next(low); it != high; ++it)
    {
        if(*it < pivot)
        {
            std::iter_swap(it,store);
            ++store;
        }
    }

    intIter pivotPos = std::prev(store);
    std::iter_swap(low,pivotPos);

    return pivotPos;
}

int main()
{
    std::vector<int> inp = {10, 30, 25, 60, 40, 20, 50};
    // Sort::SelectionSort(inp);
    // Sort::BubbleSort(inp);
    // Sort::InsertionSort(inp);
    // Sort::QuickSort(inp.begin(), inp.end());
    
    // for (const auto &it : inp) std::cout << it << " ";

    // QuickSort q(inp); q.Sort();
    // MergeSort m(inp); m.Sort();

    // NumberOfCase n(inp,3);
    // n.Per();
    // n.Com();

    return 0;
}