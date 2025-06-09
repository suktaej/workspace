#include <array>
#include <cstdlib>
#include <random>
#include <algorithm>
#include <iostream>
#include <vector>

static constexpr int MAX_SIZE = 100;

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

public:
  void InputRand();
  void Selector();
  void PrintArray();
  void Shuffle();

  void SelectionSort();
  void InsertionSort();
};
