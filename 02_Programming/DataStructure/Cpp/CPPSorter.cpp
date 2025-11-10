#include "CPPSorter.h"

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

void Sorter::QuickSort(int low, int high)
{
    if (low < high)
    {
        int pivot = Partition(low, high);
        QuickSort(low, pivot -1);   // left sorting
        QuickSort(pivot + 1, high);  // right sorting
    }
}

int Sorter::Partition(int low, int high)
{
    int pivot = vec[high];  // 마지막 원소를 pivot
    int lowIdx = low - 1;       // 작은 원소의 idx(최종 pivot index)

    for (int j = low; j < high; ++j)
    {
        if (vec[j] < pivot)
        {
            ++lowIdx;
            std::swap(vec[j], vec[lowIdx]);
        }
    }
    std::swap(vec[lowIdx+1], vec[high]);
    
    return lowIdx + 1;
}

void Sorter::MergeSort(int left, int right)
{
    if (left < right)
    {
        int mid = left + (right - left) / 2;
        MergeSort(left, mid);
        MergeSort(mid + 1, right);
        Merge(left, mid, right);
    }
}

void Sorter::Merge(int left, int mid, int right)
{
    int leftSize = mid - left + 1;
    int rightSize = right - mid;

    std::vector<int> leftVec(leftSize), rightVec(rightSize);

    // 배열 복사
    for (int i =0;i<leftSize;++i)
        leftVec[i] = vec[left+i];

    for (int i =0;i<rightSize;++i)
        rightVec[i] = vec[mid + 1 + i];

    // 병합 인덱스
    int rightSearch = 0;
    int leftSearch = 0;
    int vecIndex = left;

    // 비교 후 병합
    while (leftSearch < leftSize && rightSearch < rightSize)
    {
        if (leftVec[leftSearch] <= rightVec[rightSearch])
            vec[vecIndex++] = leftVec[leftSearch++];
        else
            vec[vecIndex++] = rightVec[rightSearch++];
    }

    // 하나의 배열이 empty일 경우 나머지를 삽입
    while (leftSearch < leftSize)
        vec[vecIndex++] = leftVec[leftSearch++];

    while (rightSearch < rightSize)
        vec[vecIndex++] = rightVec[rightSearch++];
}