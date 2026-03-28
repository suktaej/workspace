#include <iostream>
#include <sstream>
#include <string>
#include <vector>

void input()
{
    int temp = 0;
    std::vector<int> operend;
    std::string inp;
    std::istringstream iss;

    std::cin>>inp;
    iss.str(inp);

    while(iss>>temp)
        operend.push_back(temp);
}

void solve()
{
    int temp = 0;
    int res = 0;
    int size;
    bool sign = true;
    std::string inp;

    std::cin>>inp;
    size = inp.size();
    
    for(int i =0;i<=size;++i)
    {
        if (i == size || inp[i] == '+' || inp[i] == '-')
        {
            if(sign)
                res += temp;
            else
                res -= temp;

            temp = 0;

            if(inp[i] == '-')
                sign = false;
        }
        else
            temp = temp * 10 + (inp[i] - '0');
    }

    std::cout<<res;
}

int main()
{
    solve();
    return 0;
}