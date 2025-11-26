#include <vector>
#include <string>
#include <sstream>

bool Calc(std::vector<std::string>& formula)
{
}

std::vector<std::string> solution(std::vector<std::string> quiz) {

    std::vector<std::string> answer;

    for(const auto &formula : quiz)
    {
        std::istringstream iss(formula);

        int a, b, c;
        char op, eq;
        bool correct;

        iss >> a >> op >> b >> eq >> c;

        switch (op)
        {
        case '+': correct = ( a + b == c ); break;
        case '-': correct = ( a - b == c ); break;
        case '*': correct = ( a * b == c ); break;
        case '/': correct = ( a / b == c ); break;
        }
        
        answer.push_back(correct ? "O" : "X");
    }

    return answer;
}
