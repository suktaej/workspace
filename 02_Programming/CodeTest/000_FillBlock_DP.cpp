#include <iostream>
#include <vector>

using namespace std;

using ll = long long;
constexpr int MOD = 1000000007;

// 행렬 구조체 정의
struct Matrix
{
    int size;
    vector<vector<ll>> mat;

    Matrix(int s) : size(s)
    {
        mat.resize(size, vector<ll>(size, 0));
    }

    // 행렬 곱셈 정의
    Matrix operator*(const Matrix &other) const
    {
        Matrix res(size);

        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                if (mat[i][j] == 0)
                    continue;

                for (int k = 0; k < size; k++)
                    res.mat[i][k] = (res.mat[i][k] + mat[i][j] * other.mat[j][k]) % MOD;
            }
        }
        return res;
    }
};

// 행렬 거듭제곱 (O(log N))
Matrix power(Matrix a, ll n)
{
    Matrix res(a.size);

    for (int i = 0; i < a.size; i++)
        res.mat[i][i] = 1; // 단위 행렬

    while (n > 0)
    {
        if (n % 2 == 1)
            res = res * a;

        a = a * a;
        n /= 2;
    }

    return res;
}

/**
 * DFS를 이용한 전이 행렬 생성
 * row: 현재 열에서 채우고 있는 행 번호
 * curr_mask: 현재 열의 상태 (이전 열에서 삐져나온 블록들)
 * next_mask: 다음 열로 삐져나갈 블록들의 상태
 */
void generateTransitions(int row, int m, int curr_mask, int next_mask, Matrix &T)
{
    if (row == m)
    {
        // 현재 열을 다 채웠다면, 다음 열의 상태(next_mask)로 전이 가능함을 기록
        // T[다음상태][현재상태] += 1
        T.mat[next_mask][curr_mask]++;
        return;
    }

    // 1. 현재 행이 이미 이전 열에서 온 블록으로 채워져 있는 경우
    if (curr_mask & (1 << row))
    {
        generateTransitions(row + 1, m, curr_mask, next_mask, T);
    }
    else
    {
        // 2. 1x2 가로 블록을 놓는 경우 (다음 열로 삐져나감)
        generateTransitions(row + 1, m, curr_mask, next_mask | (1 << row), T);

        // 3. 2x1 세로 블록을 놓는 경우 (현재 열 내에서 두 칸 차지)
        if (row + 1 < m && !(curr_mask & (1 << (row + 1))))
            generateTransitions(row + 2, m, curr_mask, next_mask, T);
    }
}

ll solve(int m, ll n)
{
    if ((m * n) % 2 != 0)
        return 0; // 전체 칸수가 홀수면 절대 못 채움

    int num_states = (1 << m);
    Matrix T(num_states);

    // 모든 가능한 현재 상태(i)에 대해 전이 가능한 다음 상태를 DFS로 찾음
    for (int i = 0; i < num_states; i++)
        generateTransitions(0, m, i, 0, T);

    // T^n 계산
    Matrix final_T = power(T, n);

    // 시작할 때 아무것도 안 삐져나온 상태(0)에서
    // 끝났을 때 아무것도 안 삐져나온 상태(0)의 경우의 수 반환
    return final_T.mat[0][0];
}

int main()
{
    ll n;

    cout << "n을 입력하세요: ";
    cin >> n;

    cout << "2 x " << n << " 채우기: " << solve(2, n) << endl;
    cout << "3 x " << n << " 채우기: " << solve(3, n) << endl;
    cout << "4 x " << n << " 채우기: " << solve(4, n) << endl;

    return 0;
}