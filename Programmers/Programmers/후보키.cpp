#include <string>
#include <vector>
#include <unordered_set>
#include <algorithm>

using namespace std;

vector<vector<int>> uniqueCandidateKey; // 후보키를 담을 컨테이너

bool checkUnique(const vector<vector<string>>& relation, const vector<int>& tuple)
{
    unordered_set<string> set;

    int relationSize = static_cast<int>(relation.size());
    for (int row = 0; row < relationSize; ++row)
    {
        string combination;

        for (const int column : tuple)
        {
            combination += relation[row][column];
        }

        if (set.find(combination) != set.end())
            return false;

        set.insert(combination);
    }

    return true;
}

bool checkMinimality(const vector<int>& candidateKey)
{
    // 이미 나온 후보키들 중에서 최소성을 어기는 키가 있는지 확인
    for (const vector<int> uniqueKey : uniqueCandidateKey)
    {
        bool isSame = true;
        for (const int attribute : uniqueKey)
        {
            if (find(candidateKey.begin(), candidateKey.end(), attribute) == candidateKey.end())
            {
                isSame = false;
                break;
            }
        }

        if (isSame)
            return false;
    }

    return true;
}

void dfs(const vector<vector<string>>& relation, vector<int> tuple, int count, int idx = 0)
{
    // 유효성과 최소성 검사 시작
    if (tuple.size() == count)
    {
        if (checkUnique(relation, tuple) && checkMinimality(tuple))
        {
            uniqueCandidateKey.push_back(tuple);
        }

        return;
    }

    int columnSize = static_cast<int>(relation[0].size());
    for (int i = idx; i < columnSize; ++i)
    {
        tuple.push_back(i);
        dfs(relation, tuple, count, i + 1);
        tuple.pop_back();
    }
}

int solution(vector<vector<string>> relation)
{
    for (int i = 1; i <= relation[0].size(); ++i)
    {
        dfs(relation, {}, i);
    }

    return uniqueCandidateKey.size();
}

int main()
{
    solution({ {"100","ryan","music","2"}, {"200","apeach","math","2"}, {"300","tube","computer","3"}, {"400","con","computer","4"}, {"500","muzi","music","3"}, {"600","apeach","music","2"} });

    return 0;
}