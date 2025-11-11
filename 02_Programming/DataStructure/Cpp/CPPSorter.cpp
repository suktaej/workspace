#include "CPPSorter.h"
#include <algorithm>
#include <vector>
#include <queue>
#include <thread>

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
  const char *SortTypeNames[] = {"Selection", "Insertion", "Bubble", "Quick",
                                 "Merge", "Heap", "Counting", "Radix", "Shell"};

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
    QuickSort(0,cnt-1);
    break;
  case ESortType::Merge:
    MergeSort(0, cnt-1);
    break;
  case ESortType::Heap:
    HeapSort();
    break;
  case ESortType::Counting:
    break;
  case ESortType::Radix:
    RadixSort();
    break;
  case ESortType::Shell:
    ShellSort2();
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

void Sorter::ShellSort()
{
    int size = vec.size();
  
    // gap크기 설정
    for(int gap = size/2; gap > 0; gap /= 2)
    {
        for(int i = gap; i<size; ++i)
        {
            int temp = vec[i];
            int j = i;

            while(j >= gap && vec[j-gap] > temp)
            {
                vec[j] = vec[j-gap];
                j -= gap;
            }
            vec[j] = temp;
        }
    }
}

void Sorter::ShellSort2()
{
    int count = vec.size();
    int interval = count / 2;

    while (interval >= 1)
    {
        for (int i = 0; i < interval; ++i)
            ShellInsertionSort(i, count - 1, interval);
        
        interval = interval / 2;
    }
}

void Sorter::ShellInsertionSort(int start, int end, int interval)
{
    int currentheapSize = 0;
    int compareIdx = 0;

    for (int i = start + interval; i <= end; i = i + interval)
    {
        currentheapSize = vec[i];
        compareIdx = i - interval;

        while (compareIdx >= start && currentheapSize < vec[compareIdx])
        {
            vec[compareIdx + interval] = vec[compareIdx];
            compareIdx -= interval;
        }

        vec[compareIdx + interval] = currentheapSize;
    }
}

void Sorter::HeapSort()
{
    int size = vec.size();

    // 전체 배열을 힙으로 변환
    for (int i = size / 2 - 1; i >= 0; --i)
        Heapify(size, i);

    // 루트(최대값)를 끝으로 이동
    // heap size 줄이기
    for (int i = size - 1; i > 0; --i)
    {
        std::swap(vec[0], vec[i]);
        Heapify(i, 0);  // 남은 구간만 힙 재정렬
    }
}

void Sorter::Heapify(int heapSize, int rootIndex)
{
    int largest = rootIndex;
    int left = 2 * rootIndex + 1;
    int right = 2 * rootIndex + 2;

    // 왼쪽 자식이 더 크면 largest 갱신
    if (left < heapSize && vec[left] > vec[largest])
        largest = left;

    // 오른쪽 자식이 더 크면 largest 갱신
    if (right < heapSize && vec[right] > vec[largest])
        largest = right;
      
    // 루트가 가장 크지 않다면 swap 후 recursive
    if (largest != rootIndex)
    {
        std::swap(vec[rootIndex], vec[largest]);
        Heapify(heapSize, largest);
    }
}

void Sorter::RadixSort()
{
    // 자릿수를 기준별 정렬
    int maxValue = 0;

    for(const auto& it : vec)
        if(maxValue < it)
            maxValue = it;

    // 자릿수만큼 반복
    for(int exp = 1; maxValue / exp > 0 ; exp *= 10)
    {
        // 0-9 까지의 buckets
        std::vector<std::queue<int>> buckets(10);

        // 현재 자릿수를 기준 분류
        for(const int& num : vec)
        {
            int digit = (num/exp) % 10;
            buckets[digit].push(num);
        }

        // bucket에서 꺼내 배열에 갱신
        int idx = 0;
        for(int i = 0; i < 10; ++i)
        {
            while(false != buckets[i].empty())
            {
                vec[idx++] = buckets[i].front();
                buckets[i].pop();
            }
        }
    }
}

void Sorter::RadixSortForNegative()
{
    if (vec.empty()) return;

    std::vector<int> negatives;
    std::vector<int> positives;

    // 음수,양수 분리
    for (int num : vec)
    {
        if (num < 0) 
            negatives.push_back(-num); // 부호 반전
        else 
            positives.push_back(num);
    }

    // 정렬
    //RadixSort(negatives);
    //RadixSort(positives);

    // 음수 부호 복원 후 반전
    for(auto& it : negatives)
        it *= -1;
    
    std::reverse(negatives.begin(), negatives.end());

    // 병합
    vec.clear();
    vec.insert(vec.end(), negatives.begin(), negatives.end());
    vec.insert(vec.end(), positives.begin(), positives.end());
}

void Sorter::CountingSort()
{
    if (vec.empty()) return;

    int minVal = *std::min_element(vec.begin(), vec.end());
    int maxVal = *std::max_element(vec.begin(), vec.end());
    int range = maxVal - minVal + 1;

    std::vector<int> count(range, 0);
    std::vector<int> output(vec.size(), 0);

    // 등장 횟수 세기
    for (int num : vec)
        count[num - minVal]++;

    // 누적합 만들기
    for (int i = 1; i < range; ++i)
        count[i] += count[i - 1];

    // 역순으로 원소 배치
    for (int i = vec.size() - 1; i >= 0; --i)
    {
        output[count[vec[i] - minVal] - 1] = vec[i];
        count[vec[i] - minVal]--;
    }

    // 결과를 복사
    vec = std::move(output);
}

void Sorter::BucketSort()
{
    if (vec.empty()) 
        return;

    int minVal = *std::min_element(vec.begin(), vec.end());
    int maxVal = *std::max_element(vec.begin(), vec.end());

    // heuristic, 성능 최적화를 위한 시간복잡도 근사값 
    int bucketCount = std::max(1, (int)std::sqrt(vec.size()));
    double range = (double)(maxVal - minVal + 1) / bucketCount;

    std::vector<std::vector<int>> buckets(bucketCount);

    // bucket 분배
    for (int num : vec)
    {
        int idx = (int)((num - minVal) / range);

        if (idx >= bucketCount) // overflow 방지
            idx = bucketCount - 1;

        buckets[idx].push_back(num);
    }

    vec.clear();

    for (auto& bucket : buckets)
    {
        std::sort(bucket.begin(), bucket.end()); // bucket 내부정렬
        vec.insert(vec.end(), bucket.begin(), bucket.end()); // 병합
    }
}

void Sorter::BucketSortForFloat()
{
    if (vec.empty())
        return;

    int bucketCount = std::max(1, (int)std::sqrt(vec.size()));
    std::vector<std::vector<double>> buckets(bucketCount);

    // 실수 데이터를 [0, 1)로 정규화되어 있다고 가정
    // (그 외의 경우엔 min, max를 구해 normalize 필요)
    double minVal = *std::min_element(vec.begin(), vec.end());
    double maxVal = *std::max_element(vec.begin(), vec.end());
    double range = maxVal - minVal;

    if (range == 0.0)
        return;

    // 값 → 버킷 분배
    for (double num : vec)
    {
        int idx = static_cast<int>(((num - minVal) / range) * bucketCount);
        if (idx >= bucketCount)
            idx = bucketCount - 1;

        buckets[idx].push_back(num);
    }

    // 버킷 내부 정렬 후 병합
    vec.clear();

    for (auto& bucket : buckets)
    {
        std::sort(bucket.begin(), bucket.end());
        vec.insert(vec.end(), bucket.begin(), bucket.end());
    }
}

void Sorter::TimSort()
{
    static constexpr int RUN = 32;
    int arrSize = vec.size();

    // 작은 구간(RUN) 단위로 insertion Sort
    for(int i = 0; i< arrSize; i+= RUN)
    {
        int right = std::min(i+RUN-1, arrSize-1);
        //InsertionSort(i, right);
    }

    // 정렬된 run들을 병함
    for (int size = RUN; size < arrSize; size *= 2) 
    {
        for (int left = 0; left < arrSize; left += 2 * size) 
        {
            int mid = std::min(left + size - 1, arrSize - 1);
            int right = std::min(left + 2 * size - 1, arrSize - 1);

            if (mid < right)
                Merge(left, mid, right);
        }
    }
}

void Sorter::BitonicSort(bool ascending)
{
    BitonicRecursive(0,vec.size(),ascending);
}

void Sorter::BitonicRecursive(int low, int cnt, bool ascending)
{
    if (cnt <= 1)
        return;

    int k = cnt / 2;

    // 반은 오름차순, 반은 내림차순으로 정렬
    BitonicRecursive(low, k, true);
    BitonicRecursive(low + k, k, false);

    // 병합
    BitonicMerge(low, cnt, ascending);
}

void Sorter::BitonicMerge(int low, int cnt, bool ascending)
{
    if (cnt <= 1)
            return;

    int k = cnt / 2;

    for (int i = low; i < low + k; ++i)
    {
        if ((vec[i] > vec[i + k]) == ascending)
            std::swap(vec[i], vec[i + k]);
    }

    BitonicMerge(low, k, ascending);
    BitonicMerge(low + k, k, ascending);
}

void Sorter::ParallelBitonicRecursive(int low, int cnt, bool ascending)
{
    if (cnt <= 1)
            return;

        int k = cnt / 2;

        if (cnt > PARALLEL_THRESHOLD)
        {
            std::thread t1(&Sorter::ParallelBitonicRecursive, this, low, k, true);
            std::thread t2(&Sorter::ParallelBitonicRecursive, this, low + k, k, false);
            t1.join();
            t2.join();
        }
        else
        {
            ParallelBitonicRecursive(low, k, true);
            ParallelBitonicRecursive(low + k, k, false);
        }

        ParallelBitonicMerge(low, cnt, ascending);
}

void Sorter::ParallelBitonicMerge(int low, int cnt, bool ascending)
{
    if (cnt <= 1)
        return;

    int k = cnt / 2;

    // 병합 비교 (pairwise swap)
    for (int i = low; i < low + k; ++i)
    {
        if ((vec[i] > vec[i + k]) == ascending)
            std::swap(vec[i], vec[i + k]);
    }

    // 재귀 병합 (필요하다면 병렬화 가능)
    if (cnt > PARALLEL_THRESHOLD)
    {
        std::thread t1(&Sorter::ParallelBitonicMerge, this, low, k, ascending);
        std::thread t2(&Sorter::ParallelBitonicMerge, this, low + k, k, ascending);
        t1.join();
        t2.join();
    }
    else
    {
        ParallelBitonicMerge(low, k, ascending);
        ParallelBitonicMerge(low + k, k, ascending);
    }
}

void Sorter::ParallelMergeSort(std::vector<int>& arr, int left, int right)
{
    if (left >= right) 
        return;

    int mid = (left + right) / 2;

    std::thread t1([&](){ ParallelMergeSort(arr, left, mid); });
    std::thread t2([&](){ ParallelMergeSort(arr, mid + 1, right); });

    t1.join();
    t2.join();

    std::inplace_merge(arr.begin() + left, arr.begin() + mid + 1, arr.begin() + right + 1); 
}

void Sorter::parallelQuickSort(std::vector<int>& arr, int left, int right, int depth)
{
    if (left >= right) 
        return;

    int pivot = arr[(left + right) / 2];
    int i = left;
    int j = right;

    while (i <= j) 
    {
        while (arr[i] < pivot) 
            i++;
        while (arr[j] > pivot) 
            j--;

        if (i <= j) 
            std::swap(arr[i++], arr[j--]);
    }

    // 너무 깊어지면 스레드 폭발 방지
    if (depth < 3) 
    {   // depth 제한 (보통 log2(thread count))
        std::thread t1([&]() { parallelQuickSort(arr, left, j, depth + 1); });
        std::thread t2([&]() { parallelQuickSort(arr, i, right, depth + 1); });
        t1.join();
        t2.join();
    }
    else 
    {
        parallelQuickSort(arr, left, j, depth + 1);
        parallelQuickSort(arr, i, right, depth + 1);
    }
}