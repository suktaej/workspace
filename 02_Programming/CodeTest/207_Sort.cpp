#include <iostream>
#include <algorithm>
#include <vector>

class Node
{
private:
    int val;
    Node *next;

public:
    Node(int x, Node *next) : val(x), next(next) {}

public:
    void setNext(Node *node) { next = node; }
    Node *getNext() { return next; }
    int getValue() { return val; }
    void setValue(int i) { val = i; }

    Node *insertionSort(Node *head) {}
};

class List
{
private:
    Node *head;
    Node *tail;
    int size;

public:
    List() : head(nullptr), tail(nullptr), size(0) {}
    List(const List &other) = delete;
    List &operator=(const List &other) = delete;

    ~List()
    {
        Node *curr = head;

        while (nullptr != curr)
        {
            Node *next = curr->getNext();
            delete (curr);
            curr = next;
        }
    }

public:

    void insertionSort()
    {
        if(head== nullptr || head->getNext() == nullptr)
            return;

        Node* sortedHead = nullptr;
        Node* cur = head;

        while(cur!=nullptr)
        {
            Node* next = cur->getNext();

            if (sortedHead == nullptr ||
                sortedHead->getValue() >= cur->getValue())
                sortedHead = cur;
            else
            {
                Node* temp = sortedHead;
                while (temp->getNext() != nullptr &&
                       temp->getNext()->getValue() < cur->getValue())
                       temp = temp->getNext();

                cur->setNext(temp->getNext());
                temp->setNext(cur);
            }

            cur = next;
        }

        head = sortedHead;
        Node* lastNode = head;
        while (nullptr != lastNode &&
               nullptr != lastNode->getNext())
               lastNode = lastNode->getNext();

        tail = lastNode;
    }

    void push_back(int i)
    {
        Node *newNode = new Node(i, nullptr);

        if (head == nullptr)
            tail = head = newNode;
        else
        {
            tail->setNext(newNode);
            tail = newNode;
        }

        ++size;
    }

    void push_front(int i)
    {
        Node *newNode = new Node(i, nullptr);

        if (head == nullptr)
            tail = head = newNode;
        else
        {
            newNode->setNext(head);
            head = newNode;
        }

        ++size;
    }

    void pop_back()
    {
        if (head == nullptr)
            return;

        if (head == tail)
        {
            head->setNext(nullptr);
            delete tail;
            tail = head = nullptr;
        }
        else
        {
            Node *cur = head;
            while (cur->getNext() != tail)
                cur = cur->getNext();

            delete tail;
            cur->setNext(nullptr);
            tail = cur;
        }

        --size;
    }
    void pop_front()
    {
        if (head == nullptr)
            return;

        if (head == tail)
        {
            head->setNext(nullptr);
            delete tail;
            tail = head = nullptr;
        }
        else
        {
            Node *temp = head->getNext();
            delete head;
            head = temp;
        }

        --size;
    }

    Node *find(int i)
    {
        Node *cur = head;
        while (cur != nullptr)
        {
            if (i == cur->getValue())
                return cur;

            cur = cur->getNext();
        }

        return nullptr;
    }

    void insert_after(Node *pre, int i)
    {
        if (nullptr == head || nullptr == pre)
            return;

        Node *newNode = new Node(i, pre->getNext());
        pre->setNext(newNode);

        if (pre == tail)
            tail = newNode;

        ++size;
    }

    void remove_after(Node *pre)
    {
        if (nullptr == head || nullptr == pre || nullptr == pre->getNext())
            return;

        Node *temp = pre->getNext();
        pre->setNext(temp->getNext());

        if (temp == tail)
            tail = pre;

        delete temp;

        --size;
    }

    void reverse()
    {
        if (nullptr == head || head == tail)
            return;

        Node *prev = nullptr;
        Node *next = nullptr;
        Node *cur = head;
        Node *lastNode = head;

        while (cur != nullptr)
        {
            next = cur->getNext();
            cur->setNext(prev);

            prev = cur;
            cur = next;
        }

        head = prev;
        tail = lastNode;
    }
};

constexpr int n = 9;
int arr[n] = {10, 7, 42, 9, 20, 8, 34, 6, 5};

void selectionSort()
{
    for (int i = 0; i < n; ++i)
    {
        int temp = i;
        for (int j = i + 1; j < n; ++j)
            if (arr[temp] > arr[j])
                temp = j;

        std::swap(arr[i], arr[temp]);
    }
}

void insertionSort()
{
    for (int i = 1; i < n; ++i)
    {
        int key = arr[i];
        int j = i - 1;

        while (j >= 0)
        {
            if (arr[j] < key)
                break;

            arr[j + 1] = arr[j];
            --j;
        }

        arr[j + 1] = key;
    }
}

void bubbleSort()
{
    for (int i = 0; i < n - 1; ++i)
        for (int j = 0; j < (n - 1 - i); ++j)
            if (arr[j] > arr[j + 1])
                std::swap(arr[j + 1], arr[j]);
}

void merge(int left, int mid, int right)
{
    int leftSize = mid - left;
    int rightSize = right - mid;

    std::vector<int> leftVector(leftSize);
    for (int i = 0; i < leftSize; ++i)
        leftVector[i] = arr[i + left];

    std::vector<int> rightVector(rightSize);
    for (int i = 0; i < rightSize; ++i)
        rightVector[i] = arr[i + mid];

    int leftIndex = 0;
    int rightIndex = 0;
    int idx = left;

    while (leftIndex < leftSize && rightIndex < rightSize)
    {
        if (leftVector[leftIndex] <= rightVector[rightIndex])
            arr[idx++] = leftVector[leftIndex++];
        else
            arr[idx++] = rightVector[rightIndex++];
    }

    while (leftIndex < leftSize)
        arr[idx++] = leftVector[leftIndex++];

    while (rightIndex < rightSize)
        arr[idx++] = rightVector[rightIndex++];
}

void mergeSort(int left, int right)
{
    if(right - left > 1)
    {
        int mid = left + (right - left) / 2;
        mergeSort(left, mid);
        mergeSort(mid,right);
        merge(left,mid,right);
    }
}

int hoare(int low, int high)
{
    int pivot = arr[low];
    int li = low - 1;
    int hi = high + 1;

    while(true)
    {
        do ++li;
        while (arr[li] < pivot);

        do --hi;
        while(arr[hi] > pivot);
    
        if(li >= hi)
            return hi;

        std::swap(arr[li], arr[hi]);
    }
}

int lomuto(int low, int high)
{
    int mid = low + (high - low) / 2;
    std::swap(arr[mid], arr[high]);
    
    int pivot = arr[high];
    int idx = low;

    for (int i = low; i < high; ++i)
    {
        if(arr[i] < pivot)
        {
            std::swap(arr[i],arr[idx]);
            ++idx;
        }
    }

    std::swap(arr[idx],arr[high]);

    return idx;
}

void hoareQuickSort(int low, int high)
{
    if (low < high)
    {
        int pivot = lomuto(low, high);
        hoareQuickSort(low, pivot);
        hoareQuickSort(pivot+1, high);
    }
}

void lomutoQuickSort(int low, int high)
{
    if (low < high)
    {
        int pivot = lomuto(low, high);
        lomutoQuickSort(low, pivot -1);
        lomutoQuickSort(pivot+1, high);
    }
}

void heapify(int arrSize, int rootIdx)
{
    int largeIdx = rootIdx;
    int left = 2 * rootIdx + 1;
    int right = 2 * rootIdx + 2;

    if(left < arrSize && arr[largeIdx] < arr[left])
        largeIdx = left;

    if(right < arrSize && arr[largeIdx] < arr[right])
        largeIdx = right;

    if(largeIdx!=rootIdx)
    {
        std::swap(arr[largeIdx],arr[rootIdx]);
        heapify(arrSize,largeIdx);
    }
}

void heapSort()
{
    int size = sizeof(arr)/sizeof(int);
    int bnd = size / 2 - 1;

    for (int i = bnd; i >= 0; --i)
        heapify(size, i);

    for (int i = size - 1; i > 0; --i)
    {
        std::swap(arr[0],arr[i]);
        heapify(i,0);
    }
}

int main()
{
    int inArr[n] = {10, 7, 42, 9, 20, 8, 34, 6, 5};

    for (int i = 0; i < n; ++i)
        std::cout << arr[i] << ' ';

    int arrSize = sizeof(arr)/sizeof(int);
    // insertionSort();
    // selectionSort();
    // bubbleSort();
    // mergeSort(0,sizeof(arr)/sizeof(arr[0]));
    // lomutoQuickSort(0,sizeof(arr)/sizeof(int)-1);
    // hoareQuickSort(0,sizeof(arr)/sizeof(int)-1);
    heapSort();

    std::cout << std::endl;

    for (int i = 0; i < n; ++i)
        std::cout << arr[i] << ' ';

    return 0;
}