### 1. 4 dot의 평행 비교
- 기울기를 활용(x1-x2)/(y1-y2)하여 계산할 수 있으나 소수점 단위 비교로 넘어감
- 비교 시 cross를 활용
- 2차원 cross의 경우 0vector 도출 시 평행
- vec(A) x vec(B)일 때 +일 경우 A->B로 CCW, -라면 A->B로 CW
- vector를 도출 시 vector의 뺄셈 활용(B-A)
- 도출해야하는 점의 개수가 N개 일 경우 모든 선들의 기울기를 먼저 도출 후, 이 기울기들을 비교

### 2. 중복단어 탐지
- std::string 활용
- find(target)으로 string 내부에 substring을 탐색 가능. 반환값은 size_t로 match된 위치
- std::string::npos는 find에서 missmatch시 반환되는 값
- erase(length, position) 사용 시 merge문제가 발생
- replace(position,length,replaceword)로 사용하지 않는 문장을 대체

### 3. 요세푸스 순열
1. circuit linked list
- 원형 연결리스트에 1부터 n까지의 수를 순서대로 넣는다. 이때 각 수는 시계방향 순서로 배열되어 있다고 가정한다.
- n부터 시작하여 다음을 n-1회 반복한다.
- 시계방향으로 k칸 이동한다.
- 가리키고 있는 수를 삭제한다. 삭제된 수가 다음으로 제거되는 수이다. 삭제 후에는 그 반시계방향 바로 옆에 있는 수를 가리킨다.
- 리스트에 남아있는 수가 마지막에 남는 수이다.

2. Queue
- 큐에 1부터 n까지 작은 수부터 순서대로 삽입한다.
- 다음을 n-1회 반복한다.
- k-1회 큐에서 수를 꺼낸 다음 곧바로 다시 삽입한다.
- 큐에서 수를 하나 꺼낸다. 이 수가 다음으로 제거되는 수이며, 다시 삽입하지 않는다.
- 큐에 남아있는 수가 마지막에 남는 수이다.

## TIP
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