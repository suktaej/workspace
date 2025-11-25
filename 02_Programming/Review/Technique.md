1. 원형 큐, 원형 링크드리스트

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

3. 방향탐색
- 순회할 방향을 지정 후 반복
```
    constexpr int dx[dirSize] = {-1, 0, 1, -1, 1, -1, 0, 1};
    constexpr int dy[dirSize] = {-1, -1, -1, 0, 0, 1, 1, 1};

    for(int dir = 0; dir < dirSize; ++dir)
    {
        int nextX = x + dx[dir];
        int nextY = y + dy[dir];
    }
``` 