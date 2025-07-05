#include <string>
#include <vector>

using namespace std;

bool check(vector<vector<int>>& q, vector<int>& ans, vector<int>& gen, int n) {
    for (int i = 0; i < q.size(); ++i) 
    {
        int count = 0;
        vector<int> seen(n + 1);

        for (auto j : q[i]) seen[j]++;
        for (auto j : gen) seen[j]++;
        for (auto j : seen) {
            if (j > 1) ++count;
        }
        if (count != ans[i]) return false;
    }
    return true;
}

int combi(vector<vector<int>>& q, vector<int>& ans, int n, int s = 1, vector<int> gen = {}) 
{
    static int cnt = 0;
    if (gen.size() == 5) {
        if (check(q, ans, gen, n)) return 1;
    }

    int num = 0;
    for (int i = s; i <= n; ++i) {
        if (5 - gen.size() > n - i + 1) continue;

        gen.push_back(i);
        num += combi(q, ans, n, i + 1, gen);
        gen.pop_back();
    }
    return num;
}

int solution(int n, vector<vector<int>> q, vector<int> ans) {
    return combi(q, ans, n);
}

int main()
{
    solution(15, { {2, 3, 9, 12, 13},{1, 4, 6, 7, 9},{1, 2, 8, 10, 12},{6, 7, 11, 13, 15},{1, 4, 10, 11, 14} }, { 2,1,3,0,1 });
}