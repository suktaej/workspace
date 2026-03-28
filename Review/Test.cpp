#include <iostream>
#include <algorithm>
#include <vector>

constexpr int n = 9;
int gArr[n] = {10, 7, 42, 9, 20, 8, 34, 6, 5};

void selectionSort(int* arr, int size)
{
    for(int i=0;i<size;++i)
    {
        int tmp = i;
        for(int j=i+1;j<size;++j)
        {
            if(arr[tmp] > arr[j])
                tmp = j;
        }
        std::swap(arr[tmp],arr[i]);
    }
}

void insertionSort(int* arr, int size)
{
    for(int i = 1;i<size;++i)
    {
        int key = arr[i];
        int j = i-1;
        
        while (j >= 0)
        {
            if (arr[j] < key)
                break;

            arr[j+1] = arr[j];
            --j;
        }
        arr[j+1] = key;
    }
}

void bubbleSort(int* arr, int size)
{
    for (int i = 0; i < size - 1; ++i)
        for (int j = 0; j < size - 1 - i; ++j)
            if (arr[j] > arr[j + 1])
                std::swap(arr[j], arr[j + 1]);
}

void merge(int left, int mid, int right)
{
    int ls = mid - left;
    int rs = right - mid;

    std::vector<int> lv(ls);
    std::vector<int> rv(rs);

    for (int i = 0; i < ls; ++i)
        lv[i] = gArr[i + left];

    for (int i = 0; i < rs; ++i)
        rv[i] = gArr[i + mid];

    int li = 0;
    int ri = 0;
    int idx = left;

    while (li < ls && ri < rs)
    {
        if (lv[li] <= rv[ri])
            gArr[idx++] = lv[li++];
        else
            gArr[idx++] = rv[ri++];
    }

    while (li < ls)
        gArr[idx++] = lv[li++];

    while (ri < rs)
        gArr[idx++] = rv[ri++];
}

void mergeSort(int left, int right)
{
    if (right - left > 1)
    {
        int mid = left + (right - left) / 2;
        mergeSort(left, mid);
        mergeSort(mid, right);
        merge(left, mid, right);
    }
}

int hoare(int low, int high)
{
    int pivot = gArr[low];
    int li = low - 1;
    int hi = high + 1;

    while(true)
    {
        do ++li; while (gArr[li] < pivot);
        do --hi; while (gArr[hi] > pivot);

        if(li >= hi)
            return hi;

        std::swap(gArr[li], gArr[hi]);
    }
}

int lomuto(int low, int high)
{
    int mid = low + (high - low) / 2;
    std::swap(gArr[mid],gArr[high]);

    int pivot = gArr[high];
    int idx = low;

    for (int i = low; i < high; ++i)
        if(gArr[i] < pivot)
        {
            std::swap(gArr[i],gArr[idx]);
            ++idx;
        }

    std::swap(gArr[idx],gArr[high]);

    return idx;
}

void hoareQuickSort(int low, int high)
{
    if( low < high)
    {
        int pivot = hoare(low, high);
        hoareQuickSort(low, pivot);
        hoareQuickSort(pivot+1,high);
    }
}

void lomutoQuickSort(int low, int high)
{
    if(low < high)
    {
        int pivot = lomuto(low, high);
        lomutoQuickSort(low, pivot-1);
        lomutoQuickSort(pivot+1, high);
    }
}


void heapify(int arrSize, int rootIdx)
{
    int large = rootIdx;
    int left = 2 * rootIdx + 1;
    int right = 2 * rootIdx + 2;

    if(left < arrSize && gArr[left] > gArr[large])
        large = left;
    
    if(right < arrSize && gArr[right] > gArr[large])
        large = right;

    if(large!=rootIdx)
    {
        std::swap(gArr[large],gArr[rootIdx]);
        heapify(arrSize,large);
    }
}

void heapSort(int size)
{
    int bnd = size / 2 - 1;
    for (int i = bnd; i >= 0; --i)
        heapify(size, i);

    for (int i = size - 1; i > 0; --i)
    {
        std::swap(gArr[i],gArr[0]);
        heapify(i,0);
    }
}

/*
void countingSort()
{
    int size = sizeof(arr)/sizeof(int);
    int minVal = *std::min_element(std::begin(arr),std::end(arr));
    int maxVal = *std::max_element(std::begin(arr),std::end(arr));
    int range = maxVal - minVal + 1;

    std::vector<int> cnt(range, 0);
    std::vector<int> output(size, 0);

    for(int n : arr)
        ++cnt[n - minVal];

    for (int i = 1; i < range; ++i)
        cnt[i] += cnt[i-1];

    for (int i = size - 1; i >= 0; --i)
    {
        int pos = arr[i] - minVal;
        output[cnt[pos]-1] = arr[i];
        --cnt[pos];
    }

    memcpy(arr,output.data(),output.size()*sizeof(int));
    // std::copy(output.begin(), output.end(), arr);
}
*/
int main()
{
    int iArr[n];
    memcpy(iArr,gArr,sizeof(gArr));

    for (int i = 0; i < n; ++i)
        std::cout << gArr[i] << ' ';

    int size = sizeof(iArr)/sizeof(int);
    // selectionSort(iArr,size);
    // insertionSort(iArr,size);
    // bubbleSort(iArr,size);
    // mergeSort(0,size);
    // lomutoQuickSort(0, size - 1);
    // hoareQuickSort(0, size - 1);
    heapSort(size);
    // countingSort();

    std::cout << std::endl;

    for (int i = 0; i < n; ++i)
        std::cout << gArr[i] << ' ';

    return 0;
}