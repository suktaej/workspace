#include <string>
#include <vector>
#include <unordered_map>

long long VectorReplace(std::string numbers) {
    
    const std::vector<std::pair<std::string, std::string>> table = {
        {"zero", "0"}, {"one", "1"}, {"two", "2"}, {"three", "3"}, {"four", "4"},
        {"five", "5"}, {"six", "6"}, {"seven", "7"}, {"eight", "8"}, {"nine", "9"}
    };
    
    for(auto& [word,digit] : table)
    {
        size_t pos = 0;
        
        // string.find(탐색할문자열,탐색시작위치)
        while((pos = numbers.find(word, pos)) != std::string::npos)
        {
            // replace(치환시작위치,제거할용량,삽입할문자열)
            numbers.replace(pos,word.size(),digit);
            pos += 1;
        }
    }
    return std::stoi(numbers);
}

int MapReplace(const std::string& numbers) {
    std::unordered_map<std::string, int> dict = {
        {"zero", 0}, {"one", 1}, {"two", 2}, {"three", 3}, {"four", 4}, {"five", 5}, {"six", 6}, {"seven", 7}, {"eight", 8}, {"nine", 9}};

    // std::string result;
    int result = 0;
    std::string buffer;

    for (char c : numbers) 
    {
        // buffer로 복사
        buffer.push_back(c);

        // Map function
        // count(inp) : key를 탐색(bool 반환) - 존재여부만 확인
        // find(inp) : key를 탐색(iterator반환) - 존재하는 값을 사용
        if (dict.count(buffer)) 
        {
            // result.push_back(dict[buffer]);
            result = result * 10 + dict[buffer];
            buffer.clear();
        }
    }

    return result;
}
