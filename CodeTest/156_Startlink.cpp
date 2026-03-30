#include <iostream>
#include <vector>
#include <algorithm>

std::vector<std::vector<int>> group;
std::vector<bool> team;

int n;
int memberCnt;
int res = 1e9;

void minDiff()
{
    std::vector<int> teamA;
    std::vector<int> teamB;
    int scoreA = 0;
    int scoreB = 0;

    for(int i=0;i<n;++i)
    {
        if(team[i])
            teamA.push_back(i);
        else
            teamB.push_back(i);
    }

    for(int i = 0;i<memberCnt;++i)
    {
        for(int j=0;j<memberCnt;++j)
        {
            scoreA += group[teamA[i]][teamA[j]];
            scoreB += group[teamB[i]][teamB[j]];
        }
    }

    res = std::min(std::abs(scoreA-scoreB),res);
}

void combine(int val, int cnt)
{
    if(res == 0)
        return;

    if (cnt == memberCnt)
    {
        minDiff();
        return;
    }

    for (int i = val; i < n; ++i)
    {
        team[i] = true;
        combine(i + 1, cnt + 1);
        team[i] = false;
    }
}

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::cin>>n;
    group.assign(n,std::vector<int>(n));

    memberCnt = n/2;
    team.assign(memberCnt,false);

    for(int i=0;i<n;++i)
        for(int j=0;j<n;++j)
            std::cin>>group[i][j];

    team[0] = true;
    combine(1,1);
    std::cout<<res;

    return 0;
}
