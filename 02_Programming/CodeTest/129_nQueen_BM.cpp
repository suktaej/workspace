#include <iostream>

int N;
int totalCount = 0;
unsigned int target; // 모든 열에 퀸이 찼을 때의 상태 (예: N=4이면 1111)

/**
 * @param cols : 현재까지 퀸이 놓인 열 (수직 공격 범위)
 * @param ld   : 현재 행에서 왼쪽 대각선 공격 범위 (Left Diagonal)
 * @param rd   : 현재 행에서 오른쪽 대각선 공격 범위 (Right Diagonal)
 */
void solve(unsigned int cols, unsigned int ld, unsigned int rd) {
    // 1. 기저 사례: 모든 열이 다 찼다면 (예: 1111 == 1111) 성공!
    if (cols == target) {
        totalCount++;
        return;
    }

    // 2. 현재 행에서 퀸을 놓을 수 있는 자리(비트) 찾기
    // (cols | ld | rd)는 현재 행에서 공격받는 모든 위치를 1로 표시함.
    // ~ 연산으로 이를 뒤집으면 1인 자리가 '안전한 자리'가 됨.
    // & target을 통해 체스판 범위 밖의 비트들을 0으로 제거함.
    unsigned int pos = target & ~(cols | ld | rd);

    // 3. 안전한 자리(pos에서 비트가 1인 곳)가 있는 동안 반복
    while (pos) {
        // 현재 pos에서 가장 오른쪽에 있는 1비트 하나만 추출 (퀸을 놓을 위치)
        // 예: pos가 1010이면 bit는 0010이 됨
        unsigned int bit = pos & -pos;

        // 4. 다음 행으로 이동
        // cols | bit : 현재 열을 공격 범위에 추가
        // (ld | bit) << 1 : 현재 퀸의 왼쪽 대각선 공격 범위를 다음 행 기준 왼쪽으로 한 칸 밀기
        // (rd | bit) >> 1 : 현재 퀸의 오른쪽 대각선 공격 범위를 다음 행 기준 오른쪽으로 한 칸 밀기
        solve(cols | bit, (ld | bit) << 1, (rd | bit) >> 1);

        // 5. 사용한 비트 제거 (백트래킹)
        // pos에서 방금 퀸을 놓은 위치(bit)를 0으로 바꿔서 다음 가능성을 체크
        pos &= ~bit; // 또는 pos -= bit;
    }
}

int main() 
{
    std::cin >> N;
    // N=4라면 (1 << 4) - 1 = 16 - 1 = 15 (이진수 1111)
    target = (1 << N) - 1;
    solve(0, 0, 0);
    
    std::cout << totalCount << std::endl;

    return 0;
}