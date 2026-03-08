#include <iostream>

// stack area size problem
void func()
{
    constexpr int cnt = 128;
    int slot[cnt][cnt] = { 0, };

    for (int i = 0; i < cnt; ++i)
    {
        for (int j = 0; j < cnt; ++j)
        {
            slot[i][j] = i * cnt + j;
            std::cout<<slot[i][j]<<' ';
        }
        std::cout<<'\n';
    }
}

int main()
{
    func();
    return 0;
}
