#include <iostream>
#include <algorithm>
#include <string>
#include <vector>

int main()
{
    std::ios::sync_with_stdio(false);
    std::cin.tie(nullptr);

    std::string str[2];
    std::cin>>str[0]>>str[1];

    int n = str[0].length();
    int m = str[1].length();
    std::vector<std::vector<int>> lcs(n + 1, std::vector<int>(m + 1, 0));

    for(int i=1;i<=n;++i)
    {
        for(int j=1;j<=m;++j)
        {
            if(str[0][i-1] == str[1][j-1])
                lcs[i][j] = lcs[i - 1][j - 1] + 1;
            else
            {
                // Longest Common Sequence
                // lcs[i][j] = 0;
                // Longest Common Subsequence
                lcs[i][j] = std::max(lcs[i-1][j],lcs[i][j-1]);
            }
        }
    }

    std::cout<<lcs[n][m];

    return 0;
}