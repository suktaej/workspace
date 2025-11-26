#include <vector>
#include <limits>
#include <algorithm>
#include <map>
#include <iostream>

using namespace std;

// 3중첩 무시
int OverlapLine(vector<vector<int>> lines);
int OverlapLine2(vector<vector<int>> lines);
// 3중첩 적용
int LineSwap(vector<vector<int>> lines);
int LineSwap2(vector<vector<int>> lines);
int MapCount(vector<vector<int>> lines);

int main(int argc, char* argv[])
{
    vector<vector<int>> lines, lines2;
    
    lines = {{0, 2}, {-3, -1}, {-2, 1}};
    lines2 = {{0, 5}, {3, 9}, {1, 10}};

    LineSwap(lines2);
    return 0;
}

int OverlapLine(vector<vector<int>> lines)
{
    int answer = 0;

    for (auto line = lines.begin(); line != lines.end() - 1; ++line)
    {
        for (auto compareLine = line + 1; compareLine != lines.end(); ++compareLine)
        {
            int overlapStart = 0;
            int overlapEnd = 0;

            if ((*line)[0] <= (*compareLine)[0]) // line의 start가 같거나 앞일 경우
            {
                overlapStart = (*compareLine)[0];

                if ((*line)[1] <= (*compareLine)[1]) // 1. compareline의 end가 같거나 뒤일 경우
                    overlapEnd = (*line)[1];
                    //answer += (*compareLine)[0] - (*line)[1];
                else // 2. compareline이 line 내부일 경우
                    overlapEnd = (*compareLine)[1];
                //answer += (*compareLine)[0] - (*compareLine)[1];        
            }
            else // line의 start가 뒤일 경우
            {
                overlapStart = (*line)[0];

                if ((*line)[0] < (*compareLine)[1]) // 3. compareline의 end가 같거나 클 경우
                    overlapEnd = (*compareLine)[1];
                    //answer += (*line)[0] - (*compareLine)[1];
                else // 4. overlap되지 않음
                    overlapEnd = (*line)[0];
            }

            if (overlapEnd > overlapStart)
                answer += overlapEnd - overlapStart;
        }
    }

    return answer;
}

int OverlapLine2(vector<vector<int>> lines)
{
    int answer = 0;

    for (auto line = lines.begin(); line != lines.end() - 1; ++line)
    {
        for (auto compareLine = line + 1; compareLine != lines.end(); ++compareLine)
        {
            int overlapStart = max((*line)[0], (*compareLine)[0]);
            int overlapEnd = min((*line)[1], (*compareLine)[1]);

            if (overlapEnd > overlapStart)
                answer += overlapEnd - overlapStart;
        }
    }

    return answer;
}

int LineSwap(vector<vector<int>> lines)
{
    int answer = 0;
    
    int overlapStart = std::numeric_limits<int>::max();
    int overlapEnd = std::numeric_limits<int>::min();

    for (auto line : lines)
    {
        overlapStart = min(overlapStart, line[0]);
        overlapEnd = max(overlapEnd, line[1]);
    }
    
    for (int i = overlapStart; i <= overlapEnd; ++i)
    {
        int overlapCount = 0;
        
        for (const auto& line : lines)
        {
            const int& lineStart = line[0];
            const int& lineEnd = line[1];
            
            if (lineStart <= i && lineEnd > i)
                ++overlapCount;
        }
        
        if (overlapCount >= 2)
            ++answer;
    }
    
    return answer;
}

int LineSwap2(vector<vector<int>> lines) 
{
    // 이벤트 구조: {좌표, +1/-1} → +1: 선분 시작, -1: 선분 끝
    vector<pair<int,int>> events;

    for (auto &line : lines) 
    {
        events.push_back({line[0], +1}); // 시작점
        events.push_back({line[1], -1}); // 끝점
    }

    // 좌표 기준 정렬
    sort(events.begin(), events.end());

    int answer = 0;
    int count = 0;        // 현재 겹치는 선분 수
    int prev = 0;         // 이전 좌표

    for (auto &[x, type] : events) 
    {
        if (count >= 2) 
        {
            // 이전 좌표 ~ 현재 좌표까지 2개 이상 겹친 구간 길이 누적
            answer += x - prev;
        }
        
        count += type;    // 시작이면 +1, 끝이면 -1
        prev = x;         // 현재 좌표를 이전 좌표로 갱신
    }

    return answer;
}

int MapCount(vector<vector<int>> lines) 
{
    int answer = 0;
    map<int, int> sectionCnt;

    for(auto i : lines)
        for(int j = i[0] + 1; j <= i[1]; j++)
            sectionCnt[j]++;
        
    for(auto i : sectionCnt)
        if (i.second >= 2) answer++;

    return answer;
}