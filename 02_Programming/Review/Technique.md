### 1. 원형 큐, 원형 링크드리스트

- 정식으로 구현 시 포인터를 활용하여 시작과 끝을 연결해줘야 함
- 실제 구현 시 list의 경우 iterator 사용
```cpp
   // 시작 iterator 지정
    auto it = lst.begin();

    // 2개가 남을 때까지 반복
    while(lst.size() > 2)
    {   
        // 현재 iterator가 가르키는 값 제거
        // iterator는 다음 원소의 주소로 이전
        it = lst.erase(it);

        // iterator가 마지막 요소를 가리키면
        // 처음으로 반환
        if(it == lst.end())
            it = lst.begin();

        // 건너뛰기
        for(int i=0;i<term-1;++i)
        {
            ++it;

            if(it == lst.end())
                it = lst.begin();
        }
    }    
```
- queue의 경우 값을 push, pop하여 원형유지
```cpp
    // 2개가 남을 때 까지 반복
    while(que.size() > 2)
    {
        // 첫 해당 조각 추출
        que.pop();

        // term만큼 건너뛰기
        for (int j = 0; j < term - 1; ++j)
        {
            que.push(que.front());
            que.pop();
        }
    }

```

### 2. 방향탐색
- 순회할 방향을 지정 후 반복
```cpp
    constexpr int dx[dirSize] = {-1, 0, 1, -1, 1, -1, 0, 1};
    constexpr int dy[dirSize] = {-1, -1, -1, 0, 0, 1, 1, 1};

    for(int dir = 0; dir < dirSize; ++dir)
    {
        int nextX = x + dx[dir];
        int nextY = y + dy[dir];
    }
``` 

### 3. GCD, LCM
```cpp
    int gcd(int a, int b)
    {
        if (0 == b)
            return a;

        return gcd(b, a%b);
    }

    int lcm(int a, int b)
    {
        return (a*b)/gcd(a,b);
    }
```

### 4. 수열 확인
- 등비수열 확인 시 정수의 나눗셈 연산이 있을 경우 오류발생 여부 존재
```cpp
vector[2] - vector[1] == vector[1] - vector[0];  // 등차수열 확인
vector[1] * vector[1] == vector[0] * vector[2];  // 등비수열 확인
```
```cpp
    const std::vector<int> common;

    int a = common[0];
    int b = common[1];
    int c = common[2];

    // 등차수열 체크
    if (b - a == c - b) 
        int d = b - a;
    // 등비수열 체크 
    else if(b * b == a * c)
        int r = b / a;
```