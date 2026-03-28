#include <iostream>
#include <vector>

int n;
int nums[11] = { 0, };
int op[4] = { 0, };
int minRes = 1e9;
int maxRes = -1e9;

void input()
{
    std::ios::sync_with_stdio(false);  
    std::cin.tie(NULL);

    std::cin>>n;
    for(int i=0;i<n;++i)
        std::cin>>nums[i];
    for(int i=0;i<4;++i)
        std::cin>>op[i];
}

void dfs(int idx, int accVal)
{
    if(idx == n)
    {
        if(accVal < minRes)
            minRes = accVal; 
        if(accVal > maxRes)
            maxRes = accVal; 

        return;
    }

    for (int i = 0; i < 4; ++i)
    {
        if (op[i] > 0)
        {
            --op[i];
            
            switch (i)
            {
            case 0:
                dfs(idx + 1, accVal + nums[idx]); break;
            case 1:
                dfs(idx + 1, accVal - nums[idx]); break;
            case 2:
                dfs(idx + 1, accVal * nums[idx]); break;
            case 3:
                dfs(idx + 1, accVal / nums[idx]); break;
            }

            ++op[i];
        }
    }
}

int main()
{
    input();
    dfs(1, nums[0]);
    std::cout<<maxRes<<'\n'<<minRes;

    return 0;
}