#include <string>
#include <vector>
#include <algorithm> // fill

int solution(std::vector<std::string> spell, std::vector<std::string> dic) {


    for(const auto& word : dic)
    {
        std::vector<int> flag(spell.size(), 0);
        
        for(const char& c : word)
        {
            for(int i = 0; i < spell.size(); ++i)
            {
                if(c == spell[i][0])
                    ++flag[i];
            }
        }

        bool correct = true;

        for(auto it : flag)
        {
            if (it != 1)
            {
                correct = false;
                /*
                // flag를 for문 내부에 선언하여 불필요
                // 1. loop
                // for(auto& jt : flag)
                //     jt = 0;

                // 2. assign
                flag.assign(spell.size(),0);

                // 3. fill
                std::fill(flag.begin(),flag.end(),0);
                */
                break;
            }
        }

        if(correct)
            return 1;
    }

    return 2;
}

int Optimize(const std::vector<std::string>& spell, const std::vector<std::string>& dic)
{
    for (const auto& word : dic)
    {
        if (word.size() != spell.size()) 
            continue;

        bool ok = true;

        for (auto& s : spell)
        {
            if (word.find(s) == std::string::npos)
            {
                ok = false;
                break;
            }
        }

        if (ok) return 1;
    }

    return 2;
}

int main()
{
    std::vector<std::string> spell = {"z", "d", "x"};
    std::vector<std::string> dic = {"def", "dww", "dzx", "loveaw"};

    solution(spell,dic);
    return 0;
}