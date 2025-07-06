#include <string>
#include <vector>
#include <algorithm>

using namespace std;

static int dp[41][121][121]; // idx, aSum, bSum

int solution(vector<vector<int>> info, int n, int m)
{
    const int INF = 1e9;
    int sz = info.size();

    for (int i = 0; i <= sz; ++i)
        for (int j = 0; j <= 120; ++j)
            for (int k = 0; k <= 120; ++k)
                dp[i][j][k] = INF;

    dp[0][0][0] = 0; // idx=0, A=0, B=0 에서 시작

    for (int i = 0; i < sz; ++i)
    {
        int aTrace = info[i][0];
        int bTrace = info[i][1];
        for (int a = 0; a < n; ++a)
        {
            for (int b = 0; b < m; ++b)
            {
                if (dp[i][a][b] == INF) continue;

                // A가 훔치는 경우
                if (a + aTrace < n)
                    dp[i + 1][a + aTrace][b] = min(dp[i + 1][a + aTrace][b], dp[i][a][b] + aTrace);

                // B가 훔치는 경우
                if (b + bTrace < m)
                    dp[i + 1][a][b + bTrace] = min(dp[i + 1][a][b + bTrace], dp[i][a][b]);
            }
        }
    }

    int answer = INF;
    for (int a = 0; a < n; ++a)
        for (int b = 0; b < m; ++b)
            answer = min(answer, dp[sz][a][b]);

    return (answer == INF ? -1 : answer);
}

int main()
{
    solution({ {2,1}, {3,3}}, 4, 4);

    return 1;
}