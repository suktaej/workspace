#include "CPP001_Sorter.h"

int main(void) {

  Sorter mySorter;

  mySorter.InputRand();
  mySorter.Selector();

  return 0;
}

void Sorter::InputRand() {
  std::cout << "Input Random Number:";
  std::cin >> cnt;

  if (cnt <= 0)
    cnt = 1;
  else if (cnt > MAX_SIZE)
    cnt = MAX_SIZE;

  // pointer arr
  // 기존 메모리 해제
  delete[] arr;
  // 포인터 초기화
  arr = nullptr;

  try {
    // 메모리 할당 시도
    arr = new int[cnt];
    // vector 초기화
    vec.clear();
    // 선행적 메모리 초기화
    vec.resize(cnt);
  } catch (const std::bad_alloc &e) {
    std::cerr << "Memory alloc failed" << e.what() << std::endl;
    exit(1);
  }

  Shuffle();
}

void Sorter::Shuffle() {

  std::array<int, MAX_SIZE> pool;

  for (int i = 0; i < MAX_SIZE; ++i)
    pool[i] = i;

  // 난수 생성
  std::random_device rd;
  std::mt19937 g(rd());

  std::shuffle(pool.begin(), pool.end(), g);

  for (int i = 0; i < cnt; ++i) {
    arr[i] = pool[i];
    // push_back은 현재 끝에 새로운 요소를 추가
    // 이 경우 용량을 확인하고 부족할 경우 새 메모리 블록을 재할당
    // 이후 복사, 이동, 해제를 진행
    // 위에서 크기를 확정했으므로(resize) 대입이 메모리 절감
    // vec.push_back(pool[i]);
    vec[i] = pool[i];
  }
}

void Sorter::PrintArray() {
  for (int i = 0; i < cnt; ++i)
    std::cout << *(arr + i) << " ";
  std::cout << std::endl;

  for (const int &val : vec)
    std::cout << val << " ";
  std::cout << std::endl;
}

void Sorter::Selector() {
  const char *SortTypeNames[] = {"Selection", "Insertion", "Bubble",   "Quick",
                                 "Merge",     "Heap",      "Counting", "Radix"};

  ESortType tp;
  std::cout << "Select Sort Alg" << std::endl;

  for (int i = 0; i < static_cast<int>(ESortType::End); ++i)
    std::cout << i << ". " << SortTypeNames[i] << "\n";
  std::cout << "> ";

  int inp;
  std::cin >> inp;

  if (inp >= 0 && inp < static_cast<int>(ESortType::End))
    tp = static_cast<ESortType>(inp);
  else
    tp = ESortType::Selection;

  PrintArray();
  switch (tp) {
  case ESortType::Selection:
    SelectionSort();
    break;
  case ESortType::Insertion:
    InsertionSort();
    break;
  case ESortType::Bubble:
    BubbleSort();
    break;
  case ESortType::Quick:
    break;
  case ESortType::Merge:
    break;
  case ESortType::Heap:
    break;
  case ESortType::Counting:
    break;
  case ESortType::Radix:
    break;
  default:
    break;
  }

  PrintArray();
}

void Sorter::SelectionSort() {
  /*
  // pointer array
  for (int i = 0; i < cnt - 1; ++i) {
    int minIdx = i;
    for (int j = i + 1; j < cnt; ++j) {
      if (arr[j] < arr[minIdx])
        minIdx = j;
    }

    if (minIdx != i)
      std::swap(arr[i], arr[minIdx]);
  }
  */

  // vector
  if (vec.empty() || vec.size() < 2)
    return;

  for (vec_it it_i = vec.begin(); it_i != vec.end() - 1; ++it_i) {
    vec_it minIt = it_i;
    for (vec_it it_j = it_i + 1; it_j != vec.end(); ++it_j) {
      if (*it_j < *minIt)
        minIt = it_j;
    }

    if (minIt != it_i)
      std::swap(*it_i, *minIt);
  }
}

void Sorter::InsertionSort() {
  if (vec.empty() || vec.size() < 2)
    return;

  for (vec_it it_i = vec.begin() + 1; it_i != vec.end(); ++it_i) {
    int key = *it_i;
    vec_it it_j = it_i;

    while (it_j != vec.begin() && *(it_j - 1) > key) {
      *it_j = *(it_j - 1);
      --it_j;
    }
    *it_j = key;
  }
}

void Sorter::BubbleSort() {
  if (vec.empty() || vec.size() < 2)
    return;

  for (vec_it it_i = vec.begin(); it_i != vec.end() - 1; ++it_i) {
    bool swapFlag = false;
    // it_i - vec.begin() : 두 개의 Iterator사이의 거리(정수값)
    for (vec_it it_j = vec.begin();
         it_j != vec.end() - 1 - (it_i - vec.begin()); ++it_j) {
      if (*it_j > *(it_j + 1)) {
        std::swap(*it_j, *(it_j + 1));
        swapFlag = true;
      }

      if (!swapFlag)
        break;
    }
  }
}
