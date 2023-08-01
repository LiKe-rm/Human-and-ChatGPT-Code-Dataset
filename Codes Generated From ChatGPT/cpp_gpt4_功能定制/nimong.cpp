#include <iostream>
#include <vector>
#include <queue>
#include <utility>
#include <ctime>
#include <cstdlib>

// 生成简单的迷宫
std::vector<std::string> generate_maze(int width, int height) {
    srand(time(0));
    std::vector<std::string> maze(height, std::string(width, '#'));
    
    // 标记已访问过的单元格
    std::vector<std::vector<bool>> visited(height, std::vector<bool>(width, false));

    // 从一个随机起点开始
    int start_x = rand() % (height / 2) * 2 + 1;
    int start_y = rand() % (width / 2) * 2 + 1;
    maze[start_x][start_y] = 'S';
    visited[start_x][start_y] = true;

    // 存储可访问的墙壁
    std::vector<std::pair<int, int>> walls;

    // 将邻近的墙壁添加到列表中
    auto add_walls = [&](int x, int y) {
        const int dx[] = {-1, 0, 1, 0};
        const int dy[] = {0, 1, 0, -1};
        for (int i = 0; i < 4; ++i) {
            int nx = x + 2 * dx[i];
            int ny = y + 2 * dy[i];
            if (is_valid(nx, ny, maze) && !visited[nx][ny]) {
                walls.push_back({nx, ny});
            }
        }
    };

    add_walls(start_x, start_y);

    // 随机Prim算法
    const int dx[] = {-1, 0, 1, 0};
    const int dy[] = {0, 1, 0, -1};

    while (!walls.empty()) {
        int random_index = rand() % walls.size();
        int x = walls[random_index].first;
        int y = walls[random_index].second;
        walls.erase(walls.begin() + random_index);

        for (int i = 0; i < 4; ++i) {
            int nx = x + dx[i];
            int ny = y + dy[i];

            if (is_valid(nx, ny, maze) && visited[nx][ny]) {
                maze[x][y] = '.';
                maze[x - dx[i]][y - dy[i]] = '.';
                visited[x][y] = true;
                add_walls(x, y);
                break;
            }
        }
    }

    // 添加入口和出口，如果需要的话
    // maze[1][0] = '.';
    // maze[height - 2][width - 1] = '.';

    return maze;
}

// 判断是否在迷宫内
bool is_valid(int x, int y, const std::vector<std::string>& maze) {
    return x >= 0 && x < maze.size() && y >= 0 && y < maze[0].size();
}

// 广度优先搜索（BFS）求解迷宫
bool solve_maze(std::vector<std::string>& maze) {
    int start_x, start_y;
    for (int i = 0; i < maze.size(); ++i) {
        for (int j = 0; j < maze[i].size(); ++j) {
            if (maze[i][j] == 'S') {
                start_x = i;
                start_y = j;
                break;
            }
        }
    }

    std::queue<std::pair<int, int>> q;
    q.push({start_x, start_y});

    const int dx[] = {-1, 0, 1, 0};
    const int dy[] = {0, 1, 0, -1};

    while (!q.empty()) {
        int x = q.front().first;
        int y = q.front().second;
        q.pop();

        if (maze[x][y] == 'E') {
            return true;
        }

        for (int i = 0; i < 4; ++i) {
            int nx = x + dx[i];
            int ny = y + dy[i];
            if (is_valid(nx, ny, maze) && (maze[nx][ny] == '.' || maze[nx][ny] == 'E')) {
                q.push({nx, ny});
                maze[nx][ny] = '#';
            }
        }
    }

    return false;
}

int main() {
    std::vector<std::string> maze = generate_maze(17, 13);

    std::cout << "Maze:" << std::endl;
    for (const auto& row : maze) {
        std::cout << row << std::endl;
    }

    if (solve_maze(maze)) {
        std::cout << "Solution found!" << std::endl;
    } else {
        std::cout << "No solution found." << std::endl;
    }

    return 0;
}
