#include <iostream>
#include <vector>

void CheckProgression(std::vector<int> vec)
{
    int a = vec[0];
    int b = vec[1];

    int ratio = b - a;

    if(b+ratio==vec[2])
    {
        vec.back() + ratio;
    }
    else
    {
        ratio = b / a;
        vec.back() * ratio;
    }
}

int main(void)
{
    return 0;
}
