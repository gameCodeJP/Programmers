#include <string>
#include <vector>
#include <algorithm>

using namespace std;

bool isValid(const vector<int>& combination, const vector<vector<int>>& q, const vector<int>& ans)
{
    int qSize = static_cast<int>(q.size());
    for (int i = 0; i < qSize; ++i)
    {
        int count = 0;
        for (int j = 0; j < 5; ++j)
        {
            if (find(q[i].begin(), q[i].end(), combination[j]) != q[i].end())
            {
                ++count;
            }
        }

        if (ans[i] != count)
            return false;
    }

    return true;
}

int dfs(int idx, vector<int>& combination, const vector<vector<int>>& q, const vector<int>& ans, const int n)
{
    // 조합이 완성되었다면 유효한지 확인 후 return
    if (idx == 5)
        return isValid(combination, q, ans);

    int answer = 0;

    // 오름차순이기에 만약 Idx가 0이라면 1부터 시작, Idx가 0이 아니라면 이전 Idx에 값보다 +1
    int start = idx == 0 ? 1 : combination[idx - 1] + 1;
    for (start; start <= n; ++start)
    {
        // 재귀를 통해 돌아오면 이전 값들로 되어 있을텐데 어차피 재귀를 다시 돌리게 되면 idx위치에 값이 변하기 때문에 상관없다.
        combination[idx] = start;
        answer += dfs(idx + 1, combination, q, ans, n);
    }

    return answer;
}

int solution(int n, vector<vector<int>> q, vector<int> ans)
{
    vector<int> combination(5, 0);
    int answer = dfs(0, combination, q, ans, n);

    return answer;
}

int main()
{
    solution(15, { {2, 3, 9, 12, 13},{1, 4, 6, 7, 9},{1, 2, 8, 10, 12},{6, 7, 11, 13, 15},{1, 4, 10, 11, 14} }, { 2,1,3,0,1 });
}