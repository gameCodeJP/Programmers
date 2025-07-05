#include <vector>
#include <queue>

using namespace std;

// 전역 변수를 정의할 경우 함수 내에 초기화 코드를 꼭 작성해주세요.
vector<int> solution(int m, int n, vector<vector<int>> picture) 
{
    vector<int> answer(2);

    int mx[4] = { 1, 0, -1, 0 };
    int my[4] = { 0, 1, 0, -1 };

    for (int i = 0; i < m; ++i)
    {
        for (int j = 0; j < n; ++j)
        {
            // 방문 했거나 색칠하지 않은 영역이라면 패스
            if (picture[i][j] == 0)
                continue;

            // 새로운 영역을 발견했으니 영역수 증가
            ++answer[0];
            
            const int color = picture[i][j]; // 탐색할 색상
            int count = 0; // 같은 색상이 몇개인지 체크하는 용도

            // 현재 노드를 시작으로 탐색
            queue<pair<int, int>> q;
            q.push({ i, j });

            // BFS탐색을 통해 같은 색상의 영역이 있는지 찾는다.
            while (q.empty() == false)
            {
                pair<int, int> currentPos = q.front();
                q.pop();

                // 이미 방문한 곳일수도 있기에 체크
                if (picture[currentPos.first][currentPos.second] == 0)
                    continue;

                // 방문 표시 및 수 증가
                picture[currentPos.first][currentPos.second] = 0;
                ++count;

                for (int i = 0; i < 4; ++i)
                {
                    int nx = mx[i] + currentPos.first;
                    int ny = my[i] + currentPos.second;

                    // 범위를 벗어나거나 색상이 다를 경우
                    if (nx < 0 || nx >= m || ny < 0 || ny >= n || picture[nx][ny] != color)
                        continue;

                    q.push({ nx, ny });
                }
            }

            // 같은 색상 수가 이전에 나온 값보다 높은 경우 대입
            if (count > answer[1])
            {
                answer[1] = count;
            }
        }
    }

    return answer;
}

int main()
{
    solution(6, 4, { {1, 1, 1, 0}, {1, 1, 1, 0}, {0, 0, 0, 1}, {0, 0, 0, 1}, {0, 0, 0, 1}, {0, 0, 0, 1} });

    return 0;
}