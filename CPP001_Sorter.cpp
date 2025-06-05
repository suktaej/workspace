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

  // 기존 메모리 해제
  delete[] arr;
  // 포인터 초기화
  arr = nullptr;

  try {
    // 메모리 할당 시도
    arr = new int[cnt];
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

  for (int i = 0; i < cnt; ++i)
    arr[i] = pool[i];

  PrintArray();
}

void Sorter::PrintArray() {
  for (int i = 0; i < cnt; ++i)
    std::cout << *(arr + i) << " ";

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
  std::cin>>inp;

  if(inp >= 0 && inp < static_cast<int>(ESortType::End))
    tp = static_cast<ESortType>(inp);
  else
   tp = ESortType::Selection;

  switch (tp) {
  case ESortType::Selection:
    SelectionSort();
    break;
  case ESortType::Insertion:
    break;
  case ESortType::Bubble:
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

void Sorter::SelectionSort() 
{
    for(int i =0; i<cnt-1;++i)
    {
        int minIdx = i;
        for(int j = i+1;j<cnt;++j)
        {
            if(arr[j] < arr[minIdx])
              minIdx = j;
        }

        if(minIdx!=i)
        std::swap(arr[i],arr[minIdx]);
    }
}