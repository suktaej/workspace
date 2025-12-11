#include <vector>

int ExpectedValue(int n, std::vector<int> Aprob, std::vector<int> Bprob)
{
    int Aexp = 0;
    int Bexp = 0;

    for (int i = 1; i <= n; ++i)
    {
        Bexp += Bprob[i] / n;
        Aexp += Aprob[i] / n;
    }

    return Bexp + Aexp;
}

int ExptectedQuiz(int quizCount, std::vector<int> choice, std::vector<int> point)
{
    int exp;
    for(int i=1;i<=quizCount;++i)
        exp += point[i] / choice[i];

    return exp;
}