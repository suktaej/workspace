#include <iostream>
#include <string>

std::string str = "aabbaa";

bool strCheck()
{
    int size = str.size();
    int mid = size / 2;

    for(int i=0;i<mid;++i)
    {
        if(str[i]!=str[size-i])
            return false;
    }

    return true;
}

int revInt(int inp)
{
    int res = 0;
    while (inp > 0)
    {
        res = res * 10 + (inp % 10);
        inp /= 10;
    }

    return res;
}

bool solve()
{
    int orth = 123454321;
    int rev = revInt(orth);
    
    if(0 == (orth-rev))
        return true;
    else
        return false;
}

int main()
{

    solve();
    return 0;
}