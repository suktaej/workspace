#include <algorithm>
#include <array>
#include <cstdlib>
#include <iostream>
#include <random>
#include <vector>

static constexpr int MAX_SIZE = 100;
//constexpr의 경우 static으로 지정하더라도 cpp에서 정의할 필요 없음

using vec_it = std::vector<int>::iterator;

enum class ESortType {
  Selection,
  Insertion,
  Bubble,
  Quick,
  Merge,
  Heap,
  Counting,
  Radix,
  Shell,
  End
};

class Sorter {
public:
  // default Constructor
  Sorter() = default;
  Sorter(int _cnt) : cnt(_cnt) { arr = new int[cnt]; };
  // Copy
  Sorter(const Sorter &rhs) : cnt(rhs.cnt) {
    arr = new int[cnt]{};
    std::copy(rhs.arr, rhs.arr + cnt, arr);
  };

  Sorter &operator=(const Sorter &rhs) {
    if (this != &rhs) {
      delete[] arr;
      cnt = rhs.cnt;
      arr = new int[cnt];
      std::copy(rhs.arr, rhs.arr + cnt, arr);
    }
    return *this;
  }
  // Move
  Sorter(Sorter &&rhs) noexcept {
    cnt = rhs.cnt;
    arr = rhs.arr;
    rhs.cnt = 0;
    rhs.arr = nullptr;
  };

  Sorter &operator=(Sorter &&rhs) noexcept {
    if (this != &rhs) {
      delete[] arr;
      cnt = rhs.cnt;
      arr = rhs.arr;
      rhs.cnt = 0;
      rhs.arr = nullptr;
    }
    return *this;
  }
  // Destructor
  ~Sorter() { delete[] arr; };

private:
  int cnt = 0;
  int *arr = nullptr;
  std::vector<int> vec;
  static constexpr int PARALLEL_THRESHOLD = 1 << 12;

public:
  void InputRand();
  void Selector();
  void PrintArray();
  void Shuffle();

  void SelectionSort();
  void InsertionSort();

  void ShellSort();
  void ShellSort2();
  void ShellInsertionSort(int start, int end, int interval);

  void BubbleSort();

  void QuickSort(int low, int high);
  int Partition(int low, int high);

  void MergeSort(int left, int right);
  void Merge(int left, int mid, int right);

  void HeapSort();
  void Heapify(int value, int root);

  void RadixSort();
  void RadixSortForNegative();

  void CountingSort();

  void BucketSort();
  void BucketSortForFloat();

  void TimSort();

  void BitonicSort(bool ascending = true);
  void BitonicRecursive(int low, int cnt, bool ascending);
  void BitonicMerge(int low, int cnt, bool ascending);
  /*
  void OddEvenSort();
  void StoogeSort();
  void CocktailSort();
  void CombSort();
  */
  void ParallelBitonicRecursive(int low, int cnt, bool ascending);
  void ParallelBitonicMerge(int low, int cnt, bool ascending);

  void ParallelMergeSort(std::vector<int>& arr, int left, int right);
  void parallelQuickSort(std::vector<int>& arr, int left, int right, int depth = 0);
};
