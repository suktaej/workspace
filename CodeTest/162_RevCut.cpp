#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <sstream>

int testCase = 0;

void parsing(std::vector<int>& vec)
{
    std::string str;
    std::cin>>str;

    int num = 0;
    bool minus = false;

    for(char c : str)
    {
        if(c == '-')
            minus = true;
        else if (c >= '0' && c <= '9')
            num = num * 10 + (c - '0');
        else
        {
            if(num!=0)
            {
                if(minus)
                    num*=-1;

                vec.push_back(num);
                num = 0;
                minus = false;
            }
        }
    }

    if (num != 0)
        vec.push_back(num);
}

void parsingUsingStream(std::vector<int>& vec)
{
    std::string s;
    std::cin >> s;

    for (char &c : s)
    {
        if (c == '[' || c == ']' || c == ',')
            c = ' ';
    }

    std::istringstream iss(s);
    int x;
    
    while (iss >> x)
        vec.push_back(x);
}

void reverse(std::vector<int>& vec)
{
    int swapCount = vec.size() / 2;
    int lastIdx = vec.size() + 1;

    for(int i=0;i<swapCount;++i)
        std::swap(vec[i],vec[lastIdx-i]);
}

void solve()
{
    std::string order;
    int cnt = 0;
    std::vector<int> vec;
    
    std::cin>>order;
    std::cin>>cnt;
    vec.reserve(cnt);
    parsing(vec);

    if (order.empty())
    {
        std::cout << "error\n";
        return;
    }

    for(char c : order)
    {

        if(c=='R')
            std::reverse(vec.begin(),vec.end());
        else if(c=='D')
        {
            if (vec.empty())
            {
                std::cout << "error\n";
                return;
            }

            vec.erase(vec.begin(),vec.begin()+1);
        }
    }

    int size = vec.size();

    std::cout<<'[';
    for(int i=0;i<size;++i)
    {
        std::cout<<vec[i];

        if (i != size - 1)
            std::cout<<',';
    }
    std::cout<<']'<<'\n';
}

int main()
{
    std::cin>>testCase;
    for(int i=0;i<testCase;++i)
        solve();

    return 0;
}