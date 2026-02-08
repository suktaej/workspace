#include <iostream>
#include <vector>
#include <algorithm>

struct FTime
{
    int start;
    int end;

    bool operator<(const FTime& other)  const
    {
        if(end!=other.end)
            return end < other.end;

        return start < other.start;
    }
    
    bool operator>(const FTime& other)  const
    {
        if(end!=other.end)
            return end > other.end;
        
        return start > other.start;
    }
};

int n;
std::vector<FTime> t;

void structType()
{
    std::cin>>n;

    t.reserve(n);
    int s, e;

    for(int i=0;i<n;++i)
    {
        std::cin>>s>>e;
        t.push_back({s,e});
    }
    
    std::sort(t.begin(),t.end());
    
    int cnt = 0;
    int cur = 0;

    for(const FTime& meet : t)
    {
        if(meet.start >= cur)
        {
            cur = meet.end;
            ++cnt;
        }
    }

    std::cout<<cnt;
}

std::vector<std::pair<int,int>> pt;

void pairType()
{
    std::cin>>n;

    pt.reserve(n);
    int s, e;

    for(int i=0;i<n;++i)
    {
        std::cin>>s>>e;
        pt.push_back({e,s});
    }
    
    std::sort(pt.begin(),pt.end());
    
    int cnt = 0;
    int cur = 0;

    for(const auto& meet : pt)
    {
        if(meet.second >= cur)
        {
            cur = meet.first;
            ++cnt;
        }
    }
    std::cout<<cnt;
}

int main()
{
    pairType();

    return 0;
}