#include <string>
#include <vector>
#include <unordered_set>

using namespace std;

int dfs(vector<vector<int>>& land, vector<vector<bool>>& visited, const int row, const int column, const int number)
{
    static const int dx[]{ 1, -1, 0, 0 };
    static const int dy[]{ 0, 0, 1, -1 };

    int oilCount = 1;

    visited[row][column] = true;
    land[row][column] = number;

    int landRowSize = static_cast<int>(land.size());
    int landColumnSize = static_cast<int>(land[0].size());

    for (int i = 0; i < 4; ++i)
    {
        int nextRow = row + dy[i];
        int nextColumn = column + dx[i];

        if (nextRow < 0 || nextRow >= landRowSize || nextColumn < 0 || nextColumn >= landColumnSize)
            continue;

        if (visited[nextRow][nextColumn] || land[nextRow][nextColumn] == 0)
            continue;

        oilCount += dfs(land, visited, nextRow, nextColumn, number);
    }

    return oilCount;
}

int solution(vector<vector<int>> land)
{
    int answer = 0;
    int landRowSize = static_cast<int>(land.size());
    int landColumnSize = static_cast<int>(land[0].size());

    vector<int> oilCounts;
    vector<vector<bool>> visited(landRowSize, vector<bool>(landColumnSize, false));

    for (int i = 0; i < landRowSize; ++i)
    {
        for (int j = 0; j < landColumnSize; ++j)
        {
            // 땅이거나 방문 했을 경우 continue;
            if (land[i][j] == 0 || visited[i][j])
                continue;

            int oilCount = dfs(land, visited, i, j, static_cast<int>(oilCounts.size()) + 1);
            oilCounts.emplace_back(oilCount);
        }
    }

    for (int i = 0; i < landColumnSize; ++i)
    {
        unordered_set<int> set;
        int oilCount = 0;

        for (int j = 0; j < landRowSize; ++j)
        {
            if (land[j][i] == 0 || set.find(land[j][i] - 1) != set.end())
                continue;

            oilCount += oilCounts[land[j][i] - 1];
            set.insert(land[j][i] - 1);
        }

        answer = max(oilCount, answer);
    }

    return answer;
}


int main()
{
    solution({ {0, 0, 0, 1, 1, 1, 0, 0} ,{0, 0, 0, 0, 1, 1, 0, 0},{1, 1, 0, 0, 0, 1, 1, 0},{1, 1, 1, 0, 0, 0, 0, 0},{1, 1, 1, 0, 0, 0, 1, 1 } });
}