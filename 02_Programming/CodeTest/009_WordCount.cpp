#include <iostream>
#include <vector>

int WordCount(std::vector<std::string> babbling);

int main()
{
    std::vector<std::string> babyWord, babyWord2;
    babyWord = {"aya", "yee", "u", "maa", "wyeoo"};
    babyWord2 = {"ayaye", "uuuma", "ye", "yemawoo", "ayaa"};
    WordCount(babyWord2);

    return 0;
}

int WordCount(std::vector<std::string> babbling)
{
    int totalCount = 0;
    std::vector<std::string> babyWord = {"aya", "ye", "woo", "ma"};

    for (std::string source : babbling)
    {
        for (std::string target : babyWord)
        {
            size_t pos = source.find(target);
    
            if (pos!= std::string::npos)
                source.replace(pos, target.length(), " ");
        }
    
        bool bSpeak = true;
        
        for (char c : source)
        {
            if (c != ' ')
            {
                bSpeak = false;
                break;
            }
        }
        
        if (bSpeak)
           ++totalCount; 
    }

    return totalCount;
}
