#include <iostream>
#include <vector>
#include <limits>

class Sort
{
public:
    void Selection(std::vector<int>& arr);
    void Insertion(std::vector<int>& arr);
    void Bubble(std::vector<int>& arr);
    void Quick(std::vector<int>& arr);
    void Merge(std::vector<int>& arr);
};

inline void Sort::Selection(std::vector<int>& arr)
{
    int count = arr.size();

    for (int i = 0; i < count; ++i)
    {
        int smallest = i;

        for (int j = i + 1; j < count; ++j)
            if (arr[smallest] > arr[j])
                smallest = j;

        std::swap(arr[i], arr[smallest]);
    }

    for (const auto &it : arr)
        std::cout << it << " ";
}

inline void Insertion(std::vector<int> &arr)
{
    int count = arr.size();

    for(int i =0; i<count;++i)
    {

        for(int j = i+1;j<count;++j)
        {
        }
    }
}

inline void Bubble(std::vector<int>& arr)
{
    int count = arr.size();

    for (int i = 0; i < count - 1; ++i)
    {
        for (int j = 0; j < count - i - 1; ++j)
        {
            if (arr[j] > arr[j + 1])
                std::swap(arr[j], arr[j + 1]);
        }
    }
}

int main()
{
    std::vector<int> inp = {10, 30, 40, 20, 50};
    Sort s;
    // s.Selection(inp);
    s.Bubble(inp);

    return 0;
}