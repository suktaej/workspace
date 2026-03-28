#include <iostream>
#include <limits>
#include <fstream>
#include <vector>
#include <algorithm>
#include <limits>
#include <string>
#include <queue>
#include <stack>

// using INT_MAX = std::numeric_limits<int>::max();
#include <climits>

#pragma region SORT
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

template <typename T>
class NumberOfCase
{
private:
    std::vector<T> vec;
    std::vector<int> bundle;
    std::vector<bool> dup;
    std::vector<std::vector<T>> res;
    int n;
    int p;

public:
    NumberOfCase(std::vector<int> inp, int count)
        : vec(inp), n(inp.size()), p(count) 
        {
            dup.resize(n,false);
        }

public:
    void Permutation()
    {
        res.clear();
        bundle.clear();
        std::fill(dup.begin(),dup.end(),false);

        Permute(p,bundle,dup);
        Print();
    }

    void Combination()
    {
        res.clear();

        Combine(0,p,bundle);
        Print();
    }
    
private:
    void Permute(int toPick, std::vector<T>& picked, std::vector<bool>& used)
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
            Permute(toPick-1,picked,used);
            picked.pop_back();
            used[i] = false;
        }
    }

    void Combine(int start, int toPick, std::vector<T>& picked)
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
            Combine(i + 1, toPick - 1, picked);
            picked.pop_back();
        }
    }

    void Print() const
    {
        std::cout<<"Result: ";

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

        std::cout<<std::endl;
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

#pragma endregion SORT

#pragma region Algor
int GCD(int largerVal, int modVal)
{
    return (modVal == 0) ? largerVal : GCD(modVal, largerVal % modVal);
}

int Prime(int n)
{
    int maxVal = std::sqrt(n);

    for(int i= 2;i <= maxVal; ++i)
    {
        if (n % i == 0)
            return false;
    }

    return true;
}

std::vector<int> Factors(int n)
{
    std::vector<int> res;
    int maxVal = std::sqrt(n);

    for(int i=1;i<=maxVal;++i)
    {
        if (n % i == 0)
        {
            res.push_back(i);
            if (i != n / i)
                res.push_back(n / i);
        }
    }

    return res;
}

struct FEdge
{
    int src;
    int dest;
    int weight;

    bool operator<(const FEdge &other) const
    {
        return weight < other.weight;
    }

    bool operator>(const FEdge &other) const
    {
        return weight > other.weight;
    }
};

std::vector<FEdge> gEdges;

struct FDisjointSet
{
    std::vector<int> parents;
    std::vector<int> rank;

    FDisjointSet(int nodes)
        : parents(nodes + 1), rank(nodes + 1, 0)
    {
        for (int i = 0; i <= nodes; ++i)
            parents[i] = i;
    }

    int find(int child)
    {
        if(parents[child] == child)
            return child;

        return parents[child] = find(parents[child]);
    }

    bool unite(int i, int j)
    {
        int rooti = find(i);
        int rootj = find(j);

        if(rooti == rootj)
            return false;

        if (rank[rooti] < rank[rootj])
            std::swap(rooti, rootj);

        parents[rootj] = rooti;

        if (rank[rooti] == rank[rootj])
            ++rank[rooti];

        return true;
    }
};

int gEdgeCount, gVertexCount;
std::vector<std::vector<std::pair<int,int>>> gAdj; // {weight, dest}

void GraphInput(bool dir = false)
{
    std::fstream in;

    in.open("input.txt");

    if(in.is_open())
    {
        int w,u,v;
        in >> gEdgeCount >> gVertexCount;

        for (int i = 0; i < gEdgeCount; ++i)
        {
            in >> u >> v >> w;

            gEdges.push_back({u,v,w});
            gAdj[u].push_back({w,v});
            
            if(!dir)
                gAdj[v].push_back({w, v});
        }
    }

    in.close();
}

void Prim(int start)
{
    std::priority_queue<std::pair<int,int>, std::vector<std::pair<int,int>>, std::greater<std::pair<int,int>>> que;
    std::vector<bool> visited(gVertexCount + 1, false);

    que.push({0,start});
    visited[start] = true;

    for(const auto& edge : gAdj[start])
        que.push(edge);   

    while(!que.empty())
    {
        const auto& [curWeight, curDest] = que.top();
        std::cout << curDest << " (weight: " << curWeight << ")\n";
        que.pop();

        if(visited[curDest])
            continue;

        for(const auto& next : gAdj[curDest])
        {
            const auto& [nextWeight, nextDest] = next;

            if(visited[nextDest])
                continue;
            
            que.push(next);
        }
    }
}

bool Dijkstra(int start, int goal)
{
    std::priority_queue<std::pair<int,int>, std::vector<std::pair<int,int>>, std::greater<std::pair<int,int>>> que;
    std::vector<int> accDist(gVertexCount + 1, INT_MAX);
    std::vector<int> parent(gVertexCount + 1, -1);

    que.push({0, start});
    accDist[start] = 0;

    while(!que.empty())
    {
        const auto [curWeight, curDest] = que.top();
        que.pop();

        if(curDest == goal)
            break;

        if(curWeight > accDist[curDest])
            continue;

        for(const auto& next : gAdj[curDest])
        {
            const auto& [nextWeight, nextDest] = next;

            if (accDist[curDest]!= INT_MAX &&
                accDist[curDest] + nextWeight < accDist[nextDest])
                {
                    accDist[nextDest] = accDist[curDest] + nextWeight;
                    parent[nextDest] = curDest;
                    que.push({accDist[nextDest],nextDest});
                }
        }
    }

    if (INT_MAX == accDist[goal])
        return false;

    std::stack<int> path;
    for(int trace = goal;trace != -1; trace = parent[trace])
        path.push(trace);

    while(!path.empty())
    {
        std::cout<<path.top()<<(path.size() > 1 ? "->" : "");
        path.pop();
    }

    return true;
}

void Kruskal()
{
    std::sort(gEdges.begin(), gEdges.end(), [](const FEdge &a, const FEdge &b)
              { return a.weight < b.weight; });

    FDisjointSet ds(gVertexCount);

    int edgeCount = 0;
    int totalWeight = 0;

    for(const FEdge& edge : gEdges)
    {
        if(ds.unite(edge.src, edge.dest))
        {
            std::cout<<edge.src<<"-"<<edge.dest<<"\n";
            
            totalWeight += edge.weight;
            ++edgeCount;

            if (edgeCount == gVertexCount - 1)
                break;
        }
    }
}

#pragma endregion Algor

#pragma region PROBLEM

constexpr int CLOCKS = 16;
constexpr int SWITCHES = 10;
constexpr int INF = std::numeric_limits<int>::max();

const std::vector<std::vector<int>> connectedClocks = {
    {0, 1, 2},              // Switch 0
    {3, 7, 9, 11},          // Switch 1
    {4, 10, 14, 15},        // Switch 2
    {0, 4, 5, 6, 7},        // Switch 3
    {6, 7, 8, 10, 12},      // Switch 4
    {0, 2, 14, 15},         // Switch 5
    {3, 14, 15},            // Switch 6
    {4, 5, 7, 14, 15},      // Switch 7
    {1, 2, 3, 4, 5},        // Switch 8
    {3, 4, 5, 9, 13}        // Switch 9
};

bool CheckClock(std::vector<int> clocks)
{
    for(const int& c : clocks)
        if(12 != c) 
            return false;

    return true;
}

void Push(std::vector<int>& clocks, int switcher)
{
    for(int clockIdx : connectedClocks[switcher])
    {
        clocks[clockIdx] += 3;

        if(clocks[clockIdx] == 15)
            clocks[clockIdx] = 3;
    }
}

int Solve(std::vector<int> clocks, int switcher)
{
    // Base case
    if(switcher == SWITCHES)
        return CheckClock(clocks) ? 0 : INF;
    
    // Accumulate
    int res = INF;

    for (int i = 0; i < 4; ++i)
    {
        int temp = Solve(clocks, switcher+1);

        if(temp != INF)
            res = std::min(res, i + temp);

        Push(clocks,switcher);
    }

    return res;
}

void ClockProblem()
{
    std::vector<int> clocks = {12, 12, 12, 3, 3, 3, 12, 12, 12, 3, 12, 12, 12, 3, 12, 12};
    std::cout << Solve(clocks, 0);
}

constexpr int BLOCKSIZE = 3;
constexpr int BLOCKSHAPE = 4;
const int coverType[BLOCKSHAPE][BLOCKSIZE][2] = {
    {{0, 0}, {1, 0}, {0, 1}},
    {{0, 0}, {0, 1}, {1, 1}},
    {{0, 0}, {1, 0}, {1, 1}},
    {{0, 0}, {1, 0}, {1, -1}}};

bool SetBlock(std::vector<std::vector<int>>& board, int y, int x, int shape, int delta)
{
    bool bPlaced = true;

    for (int i = 0; i < BLOCKSIZE; ++i)
    {
        const int ny = y + coverType[shape][i][0];
        const int nx = x + coverType[shape][i][1];

        if (ny < 0 || nx < 0 || ny >= board.size() || nx >= board[0].size())
            bPlaced = false;
        else if ((board[ny][nx] += delta) > 1)
            bPlaced = false;
    }

    return bPlaced;
}

int Cover(std::vector<std::vector<int>>& board)
{
    int x = -1;
    int y = -1;

    for (int i = 0; i < board.size(); ++i)
    {
        for (int j = 0; j < board[i].size(); ++j)
        {
            if (0 == board[i][j])
            {
                x = j;
                y = i;
                break;
            }
        }
        
        if (y != -1)
            break;
    }

    // Base case
    if (y == -1)
        return 1;
    
    // board에 block 삽입
    int res = 0;

    for (int i = 0; i < BLOCKSHAPE; ++i)
    {
        if(SetBlock(board,y,x,i,1))
            res += Cover(board);
        
        SetBlock(board,y,x,i,-1);
    }

    return res;
}

void BlockProblem()
{
    std::vector<std::vector<int>> board = {
        {0, 0, 0, 0},
        {0, 0, 0, 0},
        {0, 0, 0, 0}};
    
    std::cout<<Cover(board)<<std::endl;
}

constexpr int DISKCOUNT = 5;
int gMoveCount = 0;

void Hanoi(int disk, char from, char temp, char to)
{
    if(disk == 0)
        return;

    Hanoi(disk-1,from,to,temp);
    std::cout<<"Move disk "<<disk<<" from "<<from<<" to "<<to<<std::endl;
    ++gMoveCount;
    Hanoi(disk-1,temp,from,to);
}

void HanoiProblem()
{
    Hanoi(DISKCOUNT,'A','B','C');
    std::cout<<"Count: "<<gMoveCount<<std::endl;
}

int Fibonacci(int n, int a = 0, int b = 1)
{
    if(n == 0)
        return a;
    if(n == 1)
        return b;

    return Fibonacci(n - 1, b, a + b);
}

#pragma endregion PROBLEM

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

    // NumberOfCase<int> n(inp,3);
    // n.Permutation();
    // n.Combination();

    // HanoiProblem();

    // Fibonacci(4);

    return 0;
}