#include <iostream>

class Sorter
{
    public:
        // default Constructor
        Sorter() = default;
        Sorter(int _cnt) : cnt(_cnt)
        {
            arr = new int[cnt];
        };
        // Copy
        Sorter(const Sorter &rhs) : cnt(rhs.cnt)
        {
            arr = new int[cnt]{};
            std::copy(rhs.arr, rhs.arr + cnt, arr);
        };

        Sorter &operator=(const Sorter &rhs)
        {
            if (this != &rhs)
            {
                delete[] arr;
                cnt = rhs.cnt;
                arr = new int[cnt];
                std::copy(rhs.arr, rhs.arr + cnt, arr);
            }
            return *this;
        }
        // Move
        Sorter(Sorter &&rhs) noexcept
        {
            cnt = rhs.cnt;
            arr = rhs.arr;
            rhs.cnt = 0;
            rhs.arr = nullptr;
        };

        Sorter &operator=(Sorter &&rhs) noexcept
        {
            if (this != &rhs)
            {
                delete[] arr;
                cnt = rhs.cnt;
                arr = rhs.arr;
                rhs.cnt = 0;
                rhs.arr = nullptr;
            }
            return *this;
        }
        // Destructor
        ~Sorter()
        {
            delete[] arr;
        };

    public:
        int cnt = 0;
        int *arr = nullptr;
};
