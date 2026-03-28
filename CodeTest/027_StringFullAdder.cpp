#include <string>
#include <vector>
#include <algorithm>

std::string BitCalc(std::string bin1, std::string bin2) {

    std::string answer = "";
    bool c = false;

    while(!bin1.empty() || !bin2.empty() || c)
    {
        bool a = false;
        bool b = false;
        
        if(!bin1.empty())
        {
            a = ('1' == bin1.back());
            bin1.pop_back();
        }

        if(!bin2.empty())
        {
            b = ('1' == bin2.back());
            bin2.pop_back();
        }
        
        bool s = a ^ b ^ c;
        answer.push_back(s ? '1' : '0');

        c = (a & b) | (c & (a ^ b));
    }

    std::reverse(answer.begin(),answer.end());

    return answer;
}

std::string IntCalc(std::string bin1, std::string bin2) {

    std::string ans;
    ans.reserve(std::max(bin1.size(), bin2.size()) + 1); // 미리 공간 확보
    
    int i = bin1.size() - 1;
    int j = bin2.size() - 1;
    int carry = 0;

    while (i >= 0 || j >= 0 || carry) 
    {
        int sum = carry;
        
        if (i >= 0) 
            sum += bin1[i--] - '0';
        if (j >= 0) 
            sum += bin2[j--] - '0';

        ans.push_back((sum % 2) + '0');
        carry = sum / 2;
    }

    std::reverse(ans.begin(), ans.end());
    return ans;
}