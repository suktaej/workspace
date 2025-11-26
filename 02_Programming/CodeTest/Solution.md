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

### 4. 등차수열의 합
1. 1항이 a, n(마지막) 번째 항이 l이라면

$$
S_n = \frac{n}{2} \cdot (a+l)
$$

2. 1항이 a, n개의 항이 있을 때, 공차(common difference)가 d라면

$$
l = a+(a+(n-1) \cdot d)
$$

$$
S_n = \frac{n}{2} \cdot (a+(a+(n-1) \cdot d)
$$

3. 수식변경으로 int계산

$$
S_n = \frac{n}{2} \cdot (2a + (n-1)d)
$$

- n이 짝수이면 `n/2`가 정수 → `int` 연산 가능
- n이 홀수이면 `n/2`가 소수 → float 사용 필요
- 곱셈 순서를 바꾸면 항상 정수 연산 가능

$$
S_n = a \cdot n + \frac{n(n-1)}{2} \cdot d
$$

- `a*n` → 정수
- `n*(n-1)`은 짝수이므로 `n*(n-1)/2` → 항상 정수연산 가능 
- 따라서 `d`가 정수라면 전체 합도 정수 → `int`로 계산 가능

### 5. 등비수열의 합

- 공비 (r = 1)일 때
$$ S_n = an $$

- 공비 (r ≠ 1)일 때
1. 일반수식
$$ S_n = a + ar + ar^2 + \cdots + ar^{n-1} $$
2. 양 변에 r을 곱
$$ rS_n = ar + ar^2 + ar^3 + \cdots + ar^{\,n} $$
3. 두 식의 뺄셈
$$ S_n = a \cdot \frac{1 - r^n}{1 - r} $$
$$ S_n = a \cdot \frac{r^n - 1}{r - 1} $$
- r > 1일 경우 전자를, r < 1 일 경우 후자로 연산하는 것이 편리
