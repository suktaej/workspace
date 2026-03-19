#include <iostream>
#include <queue>

int moveCount = 0;
std::queue<std::pair<int,int>> q;

void moveDisk(int cnt, int src, int temp, int dest)
{
    if(cnt == 0)
        return;

    moveDisk(cnt - 1, src, dest, temp);
    ++moveCount;
    q.push({src, dest});
    moveDisk(cnt - 1, temp, src, dest);
}

void solve()
{
    int n;
    std::cin>>n;
  
    moveDisk(n,1,2,3);
   
    std::cout<<moveCount<<'\n';

    while(!q.empty())
    {
        auto [a, b] = q.front();
        std::cout<<a<<' '<<b<<'\n';
        q.pop();
    }
}


int main()
{
    solve();
    return 0;
}