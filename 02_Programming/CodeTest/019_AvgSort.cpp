#include <string>
#include <vector>
#include <algorithm>

std::vector<int> solution(std::vector<std::vector<int>> score) 
{
    std::vector<float> avg; 

    for(auto &p : score)
        avg.push_back((p[0] + p[1]) / 2.f);
    
    std::vector<std::pair<float, int>> sorter;
    
    for(int i = 0; i<avg.size();++i)
        sorter.push_back({avg[i],i});    // 값, 주소
    
    // sort(sorter.begin(),sorter.end(),
    //      [](const std::pair<float,int>& a, const std::pair<float,int>& b)
    //      {
    //         return a.first > b.first;
    //      });
    sort(sorter.begin(),sorter.end(),std::greater<>());
    
    std::vector<int> answer(avg.size());
    
    for(int i=0;i<sorter.size();++i)
    {
        if(i>0 && sorter[i].first == sorter[i-1].first)
            answer[sorter[i].second] = answer[sorter[i-1].second];
        else
            answer[sorter[i].second] = i+1;
    }

    return answer;
}