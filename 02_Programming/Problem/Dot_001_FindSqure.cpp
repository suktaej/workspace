#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Point {
    long long x, y;
};

int main() {
    // 입력을 빠르게 받기 위한 설정
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, K;
    if (!(cin >> N >> K)) return 0;

    vector<Point> points(N);
    vector<long long> x_coords;

    for (int i = 0; i < N; ++i) {
        cin >> points[i].x >> points[i].y;
        x_coords.push_back(points[i].x);
    }

    // 1. x좌표 후보들을 정렬하고 중복을 제거함 (좌표 압축 준비)
    sort(x_coords.begin(), x_coords.end());
    x_coords.erase(unique(x_coords.begin(), x_coords.end()), x_coords.end());

    // 최소 면적을 저장할 변수 (최대 가능한 면적보다 큰 값으로 초기화)
    // 2*10^9 * 2*10^9 까지 고려하면 long long 범위를 생각해야 함
    unsigned long long min_area = -1ULL; // unsigned long long의 최대값으로 초기화

    int x_size = x_coords.size();

    // 2. x축의 왼쪽 경계(i)와 오른쪽 경계(j)를 선택함 (O(N^2))
    for (int i = 0; i < x_size; ++i) {
        for (int j = i; j < x_size; ++j) {
            long long x_low = x_coords[i];
            long long x_high = x_coords[j];

            // 3. 현재 x_low와 x_high 사이에 있는 점들의 y좌표만 따로 모음
            vector<long long> y_candidates;
            for (int p = 0; p < N; ++p) {
                if (points[p].x >= x_low && points[p].x <= x_high) {
                    y_candidates.push_back(points[p].y);
                }
            }

            // 선택된 점의 개수가 K개보다 적으면 이 x구간은 불가능
            if (y_candidates.size() < K) continue;

            // 4. 모인 y좌표들을 정렬 (O(N log N))
            sort(y_candidates.begin(), y_candidates.end());

            // 5. 정렬된 y좌표들 중 연속된 K개의 점을 포함하는 최소 높이를 구함 (O(N))
            for (int m = 0; m <= (int)y_candidates.size() - K; ++m) {
                long long y_low = y_candidates[m];
                long long y_high = y_candidates[m + K - 1];

                unsigned long long width = x_high - x_low;
                unsigned long long height = y_high - y_low;
                unsigned long long current_area = width * height;

                if (current_area < min_area) {
                    min_area = current_area;
                }
            }
        }
    }

    cout << min_area << endl;

    return 0;
}