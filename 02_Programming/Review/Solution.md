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
$$ 
S_n = an 
$$

- 공비 (r ≠ 1)일 때
1. 일반수식
$$ 
S_n = a + ar + ar^2 + \cdots + ar^{n-1} 
$$
2. 양 변에 r을 곱
$$ 
rS_n = ar + ar^2 + ar^3 + \cdots + ar^{\,n} 
$$
3. 두 식의 뺄셈
$$
S_n = a \cdot \frac{1 - r^n}{1 - r}
$$
$$
S_n = a \cdot \frac{r^n - 1}{r - 1} 
$$
- r > 1일 경우 전자를, r < 1 일 경우 후자로 연산하는 것이 편리

### 6. 소수 판정

- N의 소수는 2부터 N-1까지 모두 확인할 필요없음
$$
\lfloor \sqrt(N) \rfloor
$$
- 2에서 위 범위까지만 연산 시 나누어지지 않는다면 소수
- 모든 약수를 출력할 때에는 나누어진 수를 역순으로 연산 필요

### 7. 기댓값(expected value)

- 합의 기댓값은 기댓값의 합과 동일
- 주사위 X 시행 기댓값 E[X], Y 시행 기댓값 E[Y] 일 때 총 기댓값은 E[X]+E[Y]
- 예를 들어 X의 번호가 10,20,30,40,50,60 일 경우 기댓값은 210/6=35
- Y의 번호가 0,1,3,5,6,9 일 경우 기댓값은 24/6=4
- 주사위 X,Y를 함께 던져 나오는 경우의 값은 36가지 경우를 모두 합하여 다시 36으로 나누어야 함
- 이는 선형성에 의해 X의 경우의 값과 Y의 경우의 값을 합한 것과 동일 (35+4=39)

### 8. 나머지 계산
덧셈,뻴셈,곱셈 연산으로만 이루어진 식의 값을 나눈 나머지를 계산할 때, 미리 나눈 후 계산해도 동일

12 x (34 + 56 + 78 + 91)을 10으로 나눈 나머지를 계산 시
- 12 x 77  = 924 (나머지 4)
- <span style="color: red">2 x ( 4 + 6 + 8 - 1 )</span> = 2 x 17 = 34 (계산 전 값을 나눈 후 계산해도 나머지 4)
- 2 x ( 4 + 6 + 8 - 1 ) = 2 x <span style="color: red">7</span> = 14 (계산 중 값을 나눈 후 계산해도 나머지 4)

### 9. 모듈러 역수
어떤 수 b의 모듈러 n에 대한 역수 x는
a / b ≡ c (mod n)이면, a × x ≡ c (mod n)

모듈러 연산에서 뺄셈이 들어가면 반드시 + MOD 후 % MOD
이건 실수 방지가 아니라 정확성 보장 규칙

- 전제조건으로 역수가 존재하려면 b와 n이 서로소여야 한다 (gcd(b,n)==1)
- 10 / 3 ≡ 7 (mod 11)이면, 10 x 4 ≡ 7 (mod 11)  
- 모듈러 역수를 구하기 위해서 (b * x) % mod = 1를 만족하는 x를 탐색
- 위의 경우 제수가 3, 나누는 값이 11이므로 3 * x % 11 = 1을 만족하는 x는 4이므로 모듈러 역수는 4
- 피제수에 모듈러 역수를 곱한 후 mod로 나누면 동일한 나머지를 도출

- 페르마의 소정리
    소수(Prime number) p와 p의 배수가 아닌 정수 a가 있을 때, 다음 식이 성립
    a^(p - 1) ≡ 1(mod p)

    a * x ≡ 1 (mod p)에서의 x를 도출해야 하므로 페르마의 소정리 식으로 양 변을 나누면
    a * a^(p - 2) ≡ 1 (mod p)

    ∴ a의 모듈러 역수는 a^(p - 2)

### 10. 거듭제곱
  모듈러 역수를 구하려면 a^(p-2)를 계산해야하나 p가 매우 클 경우 분할할 필요가 있음

예를 들어 exp가 13일 때, 이를 2진수로 치환시 1101
이는 3^8 * 3^4 * 3^1

1. exp가 홀수일 경우 base를 결과값에 1회 곱, 짝수는 무시

2. 이후 base를 제곱(base * base)하고 exp는 절반으로 나눔
```cpp
while(exp > 0)
{
    // 지수가 홀수라면 현재 base를 결과에 한 번 곱
    if (exp % 2 == 1)
        res = res * base;
    // 지수를 반으로 줄이고 base는 제곱
    base = base * base;
    exp /= 2;
}
```

### 11. 6k 판별
모든 정수는 6으로 나누었을 때
- 6k (6의 배수)
- 6k+1
- 6k+2 (2의 배수)
- 6k+3 (3의 배수)
- 6k+4 (2의 배수)
- 6k+5

그러므로 2,3으로 나누어 떨어지는지 확인했다면 6k-1, 6k+1만 확인 시 빠른 소수판별 가능
```cpp
bool isPrime(long long n) {
    // 1. 1은 소수가 아님
    if (n <= 1) return false;
    
    // 2. 2와 3은 소수임
    if (n <= 3) return true;

    // 3. 2나 3으로 나누어떨어지면 소수가 아님 (가장 빈번한 경우를 먼저 제거)
    if (n % 2 == 0 || n % 3 == 0) return false;

    // 4. 이제 6k ± 1 형태만 확인 (i는 5부터 시작해서 6씩 증가)
    // i는 6k-1, i+2는 6k+1을 의미함
    for (long long i = 5; i * i <= n; i += 6) {
        if (n % i == 0 || n % (i + 2) == 0)
            return false; // 나누어떨어지면 소수가 아님
    }

    return true;
}
```

### 12. 크라메르 공식
크라메르 공식은 **선형 연립방정식의 해를 행렬식(det)**을 이용해 구하는 방법이다.
단, **계수행렬의 행렬식이 0이 아닐 때만 적용 가능**하다.
## 1. 2×2 연립방정식

다음 연립방정식을 고려하자.

$$
\begin{cases}
a_1 x + b_1 y = c_1 \\
a_2 x + b_2 y = c_2
\end{cases}
$$
이를 행렬 형태로 쓰면:

$$
A \mathbf{x} = \mathbf{b}
$$

$$
A =
\begin{pmatrix}
a_1 & b_1 \\
a_2 & b_2
\end{pmatrix},
\quad
\mathbf{x} =
\begin{pmatrix}
x \\
y
\end{pmatrix},
\quad
\mathbf{b} =
\begin{pmatrix}
c_1 \\
c_2
\end{pmatrix}
$$

---

### (1) 계수행렬의 행렬식

$$
\det(A) =
\begin{vmatrix}
a_1 & b_1 \\
a_2 & b_2
\end{vmatrix}
= a_1 b_2 - a_2 b_1
$$

$$
\det(A) \neq 0 \quad \Rightarrow \quad \text{해가 유일하게 존재}
$$

---

### (2) 크라메르 공식

$$
x =
\frac{
\begin{vmatrix}
c_1 & b_1 \\
c_2 & b_2
\end{vmatrix}
}{
\det(A)
}
=

\frac{c_1 b_2 - c_2 b_1}{a_1 b_2 - a_2 b_1}
$$

$$
y =
\frac{
\begin{vmatrix}
a_1 & c_1 \\
a_2 & c_2
\end{vmatrix}
}{
\det(A)
}
=

\frac{a_1 c_2 - a_2 c_1}{a_1 b_2 - a_2 b_1}
$$

---

## 2. 3×3 연립방정식

$$
\begin{cases}
a_1 x + b_1 y + c_1 z = d_1 \\
a_2 x + b_2 y + c_2 z = d_2 \\
a_3 x + b_3 y + c_3 z = d_3
\end{cases}
$$

$$
x = \frac{\det(A_x)}{\det(A)}, \quad
y = \frac{\det(A_y)}{\det(A)}, \quad
z = \frac{\det(A_z)}{\det(A)}
$$

* (A_x): x열을 상수항으로 치환
* (A_y): y열을 상수항으로 치환
* (A_z): z열을 상수항으로 치환

---

## 3. 크라메르 공식의 특징

* 계산량이 큼 (행렬식 계산)
* **이론적 증명, 수학적 분석에 적합**
* 실제 수치 계산에는 비효율적
* 행렬식이 0이면 사용 불가

---

# 역행렬을 이용한 해법

연립방정식:

$$
A \mathbf{x} = \mathbf{b}
$$

에서 **행렬 (A)가 가역(invertible)** 이면:

$$
\mathbf{x} = A^{-1} \mathbf{b}
$$

---

## 1. 2×2 행렬의 역행렬

$$
A =
\begin{pmatrix}
a & b \\
c & d
\end{pmatrix}
$$

### (1) 행렬식

$$
\det(A) = ad - bc
$$

$$
\det(A) \neq 0 \Rightarrow A^{-1} \text{ 존재}
$$

---

### (2) 역행렬 공식

$$
A^{-1} =
\frac{1}{ad - bc}
\begin{pmatrix}
d & -b \\
-c & a
\end{pmatrix}
$$

---

## 2. 역행렬을 이용한 해 구하기

$$
\mathbf{x} =
A^{-1} \mathbf{b}
=

\frac{1}{\det(A)}
\begin{pmatrix}
d & -b \\
-c & a
\end{pmatrix}
\begin{pmatrix}
e \\
f
\end{pmatrix}
$$

---

## 3. 여인수(cofactor) 기반 역행렬 (일반 n×n)

$$
A^{-1} = \frac{1}{\det(A)} \operatorname{adj}(A)
$$

여기서:

* adj(A): **수반행렬 (adjugate)**
* 각 원소는 여인수의 전치

---

## 4. 크라메르 공식과 역행렬의 관계

크라메르 공식은 사실상:

$$
x_i = (A^{-1} \mathbf{b})_i
$$

를 **행렬식 형태로 전개한 것**이다.

즉,

* 크라메르 공식 → 이론적 표현
* 역행렬 → 계산 및 구현 관점
---
“구하려는 쪽의 벡터를 Target으로 바꿔치기한다”

- a를 구할 때

    V1 대신 **Target**을 넣고 다시 `AD - BC`를 계산합니다.

$$
\begin{pmatrix}
X & x_2 \\
Y & y_2
\end{pmatrix}
\Rightarrow
\text{molA} = (X \cdot y_2 - x_2 \cdot Y)
$$

- b를 구할 때

    V2 대신 **Target**을 넣고 다시 `AD - BC`를 계산합니다.

$$
\begin{pmatrix}
x_1 & X \\
y_1 & Y
\end{pmatrix}
\Rightarrow
\text{molB} = (x_1 \cdot Y - X \cdot y_1)
$$

### 게임 승자
- N개의 돌이 존재하고 m개씩 주워갈 수 있을 때
- m = 3일 경우 N이 3 이하라면 선이 승리
- N이 4일 경우 후가 승리
- 그러므로 N이 m의 배수인 경우, 후수는 선수가 잡은 x개의 돌 만큼 m-x개를 선택
- 선수는 첫 번째에서 남은 돌의 개수가 m의 배수가 되도록 선택 후 후수가 직전에 잡은 x개의 돌 만큼 m-x를 선택

