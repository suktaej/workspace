3. 4 dot의 평행 비교
- 기울기를 활용(x1-x2)/(y1-y2)하여 계산할 수 있으나 소수점 단위 비교로 넘어감
- 비교 시 cross를 활용
- 2차원 cross의 경우 0vector 도출 시 평행
- vec(A) x vec(B)일 때 +일 경우 A->B로 CCW, -라면 A->B로 CW
- vector를 도출 시 vector의 뺄셈 활용(B-A)
- 도출해야하는 점의 개수가 N개 일 경우 모든 선들의 기울기를 먼저 도출 후, 이 기울기들을 비교

4. 중복단어 탐지
- std::string 활용
- find(target)으로 string 내부에 substring을 탐색 가능. 반환값은 size_t로 match된 위치
- std::string::npos는 find에서 missmatch시 반환되는 값
- erase(length, position) 사용 시 merge문제가 발생
- replace(position,length,replaceword)로 사용하지 않는 문장을 대체