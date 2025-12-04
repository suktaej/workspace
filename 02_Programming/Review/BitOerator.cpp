#include <iostream>
#include <vector>

constexpr int POISON = 1 << 0;  // 0001
constexpr int STUN   = 1 << 1;  // 0010
constexpr int BUFF   = 1 << 2;  // 0100
constexpr int DEBUFF = 1 << 3;  // 1000

// 상태 이름 테이블
std::vector<std::string> stateName = {
    "POISON", "STUN", "BUFF", "DEBUFF"
};

// 특정 상태 보유 여부 확인
bool hasState(int mask, int stateFlag) {
    return mask & stateFlag;
}

// 상태 추가
int addState(int mask, int stateFlag) {
    return mask | stateFlag;
}

// 상태 제거
int removeState(int mask, int stateFlag) {
    return mask & ~stateFlag;
}

// 현재 상태 출력
void printStates(int mask) {
    for (int i = 0; i < 4; ++i) {
        if (mask & (1 << i)) {
            std::cout << stateName[i] << " ";
        }
    }
    if (mask == 0)
        std::cout << "NONE";
    std::cout << "\n";
}

// BitCounter
int Counter(int mask)
{
    unsigned int umask = static_cast<unsigned int>(mask);
    int counter = 0;
    
    while(umask)
    {
        umask &= umask - 1;
        ++counter;
    }

    return counter;
}

// Rotation
int Rot(int mask, int shift, bool right)
{
    // 음수 비트 처리를 위해 unsigned로 변환
    unsigned int umask = static_cast<unsigned int>(mask);

    // int의 전체 비트 수
    int totalBits = sizeof(int) * 8;

    // shift 값이 32 이상 또는 0일 경우를 대비해 나머지 연산
    shift &= (totalBits - 1); 
    if(0 == shift)
        return mask;

    if(right)
        return (umask >> shift) | (umask << (totalBits - shift));
    else
        // 왼쪽으로 밀고(<<), 넘쳐난 비트를 오른쪽 끝으로 가져옴(>>)
        return (umask << shift) | (umask >> (totalBits - shift));
}

bool getPixel(const uint8_t* bitmap, int width, int height, int n)
{
    int row = n / width;   // y
    int col = n % width;   // x

    // row가 범위를 벗어나면 false
    if (row >= height) 
        return false;

    // Row를 구성하는 바이트 수
    // width가 10일 때 -> 10비트 -> 2바이트 필요 (8비트 + 2비트)
    // (width + 7) / 8
    int stride = (width + 7) >> 3;

    // 바이트 위치 찾기
    // (현재 줄 * 한 줄당 바이트 수) + (현재 칸 / 8)
    int byteIndex = (row * stride) + (col >> 3);

    // 바이트 내부의 비트 위치 (0 ~ 7)
    int bitIndex = col & 7;

    // 값 추출 (MSB가 왼쪽 픽셀인 경우)
    uint8_t byte = bitmap[byteIndex];
    return (byte >> (7 - bitIndex)) & 1;
}

bool getPixel(const uint8_t* bitmap, int totalPixels, int n)
{
    // 범위 체크
    if (n < 0 || n >= totalPixels)
        return false;

    // 몇 번째 바이트(Byte)에 있는지 찾기
    // n / 8
    int byteIndex = n >> 3;

    // 그 바이트 내에서 몇 번째 비트(Bit)인지 찾기
    // n % 8
    int bitIndex = n & 7;

    // 해당 바이트 가져오기
    uint8_t byte = bitmap[byteIndex];

    // 비트 확인 (MSB가 0번 인덱스라고 가정)
    // 예: n=0 -> bitIndex=0 -> 7번 쉬프트 (1000 0000) 확인
    // 예: n=7 -> bitIndex=7 -> 0번 쉬프트 (0000 0001) 확인
    return (byte >> (7 - bitIndex)) & 1;
}

int main() 
{
    int mask;

    // 상태 추가
    mask = addState(mask, POISON);
    mask = addState(mask, BUFF);

    std::cout << "현재 상태 : ";
    printStates(mask);   // → POISON BUFF

    // 조합(부분집합) 탐색
    std::cout << "\n=== 가능한 모든 상태 조합(부분집합) ===\n";

    // 가능한 비트: 4개 → 0~(1<<4)-1 = 0~15
    for (int subset = 0; subset < (1 << 4); ++subset) {
        std::cout << subset << " : ";
        printStates(subset);
    }

    return 0;
}