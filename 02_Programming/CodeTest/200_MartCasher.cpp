#include <iostream>
#include <vector>
#include <cmath>

int main()
{
    int l1, l2, p1, p2;
    std::cin>>l1>>l2>>p1>>p2;

    std::vector<std::vector<double>> dp(l1 + 1, std::vector<double>(l2 + 1, 0.));

    // 정규분포
    double q1 = 1./p1;
    double q2 = 1./p2;

    // 사건 발생 시 둘 중 한 명이 끝날 확률 = 1 - (둘 다 끝나지 않을 확률)
    // 아무것도 일어나지 않은 경우를 제외하기 위함

    // 가위바위보에서 각각의 확률은 1/3이지만 승리할 확률은 1/2
    // 이는 비기는 경우를 제외하였기 때문
    // 1 - drawPercent = 1 - 1/3 = 2/3
    // 이기는 확률 : (1/3)/(2/3) = 1/2
    double eventProb = 1. - (1. - q1) * (1. - q2);

    double prob1 = (q1 * (1. - q2)) / eventProb;    // 1 번만 끝날 확률
    double prob2 = (q2 * (1. - q1)) / eventProb;    // 2 번만 끝날 확률
    double probA = (q1 * q2) / eventProb;           // 둘 다 끝날 확률

    for (int i = 0; i <= l1; ++i)
        dp[i][0] = 0;

    for (int i = 1; i <= l2; ++i)
        dp[0][i] = 1;

    for(int i = 1; i<= l1 ; ++i)
        for(int j = 1; j<= l2; ++j)
            dp[i][j] = (prob1 * dp[i-1][j]) + (prob2 * dp[i][j-1]) + (probA * dp[i-1][j-1]);

    std::cout<<dp[l1][l2];

    return 0;
}