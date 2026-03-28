#include <string>
#include <sstream>
#include <vector>

std::string PolynomialPartition(std::string polynomial) {

    std::istringstream iss(polynomial);
    std::string token;

    int coefficient = 0;
    int term = 0;

    while(iss>>token)
    {
        if("+" == token)
            continue;
        else if('x' == token.back())
        {
            std::string digits;

            for(char c : token)
            {
                if(std::isdigit(c))
                    digits.push_back(c);
                else
                    break;
            }
            
            if(!digits.empty())
                coefficient += std::stoi(digits);
            else
                ++coefficient;
        }
        else
            term += std::stoi(token);
    }

    std::ostringstream oss;

    if (coefficient != 0)
    {
        if (coefficient == 1)
            oss << "x";
        else
            oss << coefficient << "x";
    }

    if (coefficient != 0 && term != 0)
        oss << " + ";

    if (term != 0)
        oss << term;

    if (coefficient == 0 && term == 0)
        return "0";

    return oss.str();
}

std::string Optimize(std::string polynomial) {

    std::istringstream iss(polynomial);
    std::string token;

    int coefficient = 0;
    int term = 0;

    while(iss>>token)
    {
        if ("+" == token)
            continue;

        if ('x' == token.back())
        {
            if (1 == token.size())
                ++coefficient;
            else
                coefficient += std::stoi(token.substr(0,token.size()-1));
        }
        else
            term += std::stoi(token);
    }

    std::string answer = "";
    
    if (coefficient != 0)
    {
        if (coefficient == 1)
            answer += "x";
        else
            answer += std::to_string(coefficient) + "x";
    }

    if (coefficient != 0 && term != 0)
        answer.append(" + ");

    if (term != 0)
        answer.append(std::to_string(term));

    if (coefficient == 0 && term == 0)
        return "0";

    return answer;
}

int main()
{
    std::string str = "3x + 7 + x";
    PolynomialPartition(str);
    return 0;
}