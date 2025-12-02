#include <iostream>
#include <vector>
#include <string>
#include <array>
#include <string_view>
#include <unordered_map>

std::vector<int> solution(std::vector<std::string> keyinput, std::vector<int> board) {

    std::vector<int> answer(2,0);

    for(const std::string& dir : keyinput)
    {
        if(dir=="left")
        {
            if(answer[0]-1 < -1*board[0]/2)
                continue;

            answer[0] -= 1;
        }
        else if(dir=="right")
        {
            if(answer[0]+1 > board[0]/2)
                continue;

            answer[0] += 1;
        }
        else if(dir=="up")
        {
            if(answer[1]+1 > board[1]/2)
                continue;

            answer[1] += 1;
        }
        else if(dir=="down")
        {
            if(answer[1]-1 < -1*board[1]/2)
                continue;

            answer[1] -= 1;
        }
    }
    return answer;
}

void UsingArray(std::vector<std::string> keyinput, std::vector<int> board)
{
    enum class DIR
    {
        LEFT,
        RIGHT,
        UP,
        DOWN,
        COUNT
    };

    // std::array 초기화 시 중괄호 2개 사용
    constexpr std::array<std::pair<std::string_view, DIR>, 4> table = {{
        {"left", DIR::LEFT},
        {"right", DIR::RIGHT},
        {"up", DIR::UP},
        {"down", DIR::DOWN}}};

    for(const auto& dir: keyinput)
    {
        // std::find_if(start,end,lambda)
        // container 순회탐색
        // 조건이 true라면 iterator를 반환, false일 경우 다음 요소로 이동
        auto it = std::find_if(table.begin(), table.end(),
                               [&](auto &p)
                               {
                                   return p.first == s;
                               });

        if (it != table.end())
            DIR d = it->second;
    }
}


void UsingUnorderedMap(std::vector<std::string> keyinput, std::vector<int> board)
{
    enum class DIR
    {
        LEFT,
        RIGHT,
        UP,
        DOWN,
        COUNT
    };

    static const std::unordered_map<std::string_view, DIR> table = {
    {"left", DIR::LEFT},
    {"right", DIR::RIGHT},
    {"up", DIR::UP},
    {"down", DIR::DOWN}};

    DIR arrow;

    for(const auto& dir : keyinput)
    {
        auto it = table.find(dir);

        if (it != table.end())
            arrow = it->second;
    }
}