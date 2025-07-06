#include <string>
#include <vector>
#include <queue>

using namespace std;

int solution(vector<int> players, int m, int k)
{
    int answer = 0;
    queue<int> q; // 서버가 끝나는 시간을 가지고 있다.

    int playersSize = static_cast<int>(players.size());
    for (int i = 0; i < playersSize; ++i)
    {
        while (q.empty() == false && q.front() <= i)
        {
            q.pop();
        }

        int count = players[i] / m;
        while (q.size() < count)
        {
            ++answer;
            q.push(i + k);
        }
    }

    return answer;
}

int main()
{
    solution({ 0, 2, 3, 3, 1, 2, 0, 0, 0, 0, 4, 2, 0, 6, 0, 4, 2, 13, 3, 5, 10, 0, 1, 5 }, 3, 5);

    return 0;
}