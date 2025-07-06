#include <string>
#include <vector>
#include <queue>

using namespace std;

static int answer = 0;

void crein(vector<string>& storage, const char target)
{
    const int storageRowSize = static_cast<int>(storage.size());
    const int storageColumnSize = static_cast<int>(storage[0].size());
    for (int i = 0; i < storageRowSize; ++i)
    {
        for (int j = 0; j < storageColumnSize; ++j)
        {
            if (storage[i][j] != target)
                continue;

            storage[i][j] = ' ';
            --answer;
        }
    }
}

void forklitf(vector<string>& storage, const char target)
{
    const int storageRowSize = static_cast<int>(storage.size());
    const int storageColumnSize = static_cast<int>(storage[0].size());

    queue<pair<int, int>> q;

    for (int i = 0; i < storageColumnSize; ++i)
    {
        q.push(std::make_pair(0, i));
        q.push(std::make_pair(storageRowSize - 1, i));
    }

    for (int i = 0; i < storageRowSize; ++i)
    {
        q.push(std::make_pair(i, 0));
        q.push(std::make_pair(i, storageColumnSize - 1));
    }

    static int dx[]{ 0, 0, 1, -1 };
    static int dy[]{ 1, -1, 0, 0 };

    pair<int, int> pos;
    vector<vector<bool>> visited(storageRowSize, vector<bool>(storageColumnSize));

    while (q.empty() == false)
    {
        pos = q.front();
        q.pop();

        const int currentY = pos.first;
        const int currentX = pos.second;

        if (visited[currentY][currentX])
            continue;

        visited[currentY][currentX] = true;

        if (storage[currentY][currentX] == target)
        {
            --answer;
            storage[currentY][currentX] = ' ';
        }
        else if(storage[currentY][currentX] == ' ')
        {
            for (int i = 0; i < 4; ++i)
            {
                const int nextY = currentY + dy[i];
                const int nextX = currentX + dx[i];

                if (nextY >= storageRowSize || nextY < 0 || nextX >= storageColumnSize || nextX < 0)
                    continue;

                if (visited[nextY][nextX])
                    continue;

                q.push(std::make_pair(nextY, nextX));
            }
        }
    }
}

int solution(vector<string> storage, vector<string> requests)
{
    const int storageRowSize = static_cast<int>(storage.size());
    const int storageColumnSize = static_cast<int>(storage[0].size());
    const int requestsSize = static_cast<int>(requests.size());

    answer = storageRowSize * storageColumnSize;

    for (int i = 0; i < requestsSize; ++i)
    {
        // 크레인으로 작업
        if (static_cast<int>(requests[i].size()) > 1)
        {
            crein(storage, requests[i][0]);
        }
        // 지게차로 작업
        else
        {
            forklitf(storage, requests[i][0]);
        }
    }

    return answer;
}

int main()
{
    solution({ "AZWQY", "CAABX", "BBDDA", "ACACA" }, { "A", "BB", "A" });

    return 0;
}