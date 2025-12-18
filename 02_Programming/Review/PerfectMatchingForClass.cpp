#include <iostream>
#include <vector>

class PerfectMatcher {
private:
    int n;                        // 총 인원 수
    int pairSize;                  // 한 그룹의 크기
    std::vector<bool> used;        // 사용 여부
    std::vector<std::vector<int>> current;                      // 현재 그룹 조합
    std::vector<std::vector<std::vector<int>>> result;          // 모든 결과

public:
    PerfectMatcher(int totalPersons, int groupSize)
        : n(totalPersons), pairSize(groupSize), used(totalPersons, false) {}

    void run() 
    {
        perfectMatching();
    }

    const std::vector<std::vector<std::vector<int>>>& getResult() const 
    {
        return result;
    }

private:
    void onComplete(std::vector<int>& temp) {
        for(int x : temp)
            used[x] = true;

        current.push_back(temp);
        perfectMatching();
        current.pop_back();

        for(int x : temp)
            used[x] = false;
    }

    void generateCombinations(int start, int depth, std::vector<int>& temp) {
        if(depth == pairSize - 1) {
            onComplete(temp);
            return;
        }

        for(int i = start; i < n; ++i) {
            if(!used[i]) {
                temp.push_back(i);
                generateCombinations(i + 1, depth + 1, temp);
                temp.pop_back();
            }
        }
    }

    void perfectMatching() {
        int first = -1;

        for(int i = 0; i < n; ++i) {
            if(!used[i]) {
                first = i;
                used[i] = true;
                break;
            }
        }

        if(first == -1) {
            result.push_back(current);
            return;
        }

        std::vector<int> temp;
        temp.push_back(first);

        generateCombinations(first + 1, 0, temp);

        used[first] = false;
    }
};

int main() {
    int n = 4;
    int pairSize = 2;

    PerfectMatcher matcher(n, pairSize);
    matcher.run();

    const auto& result = matcher.getResult();

    for(const auto &grouping : result) {
        for(const auto &group : grouping) {
            std::cout << "(";
            for(int i = 0; i < group.size(); ++i) {
                std::cout << group[i];
                if(i + 1 < group.size()) std::cout << ",";
            }
            std::cout << ") ";
        }
        std::cout << "\n";
    }
}