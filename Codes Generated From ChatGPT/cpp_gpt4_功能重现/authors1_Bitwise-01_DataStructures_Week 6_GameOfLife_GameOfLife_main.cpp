#include <iostream>
#include <vector>
#include <algorithm>
#include <unistd.h>

using namespace std;

void print_grid(const vector<vector<int>>& grid);
vector<vector<int>> generate_next_generation(const vector<vector<int>>& grid);
bool check_bounds(int row, int col, const vector<vector<int>>& grid);
int count_neighbors(int row, int col, const vector<vector<int>>& grid);

int main() {
    int max_generations;
    int num_cells_to_activate;
    int grid_size = 10;

    cout << "请输入最大代数（-1 表示无限）：";
    cin >> max_generations;

    cout << "请输入要激活的细胞数：";
    cin >> num_cells_to_activate;

    vector<vector<int>> grid(grid_size, vector<int>(grid_size, 0));

    cout << "请输入要激活的细胞的坐标（行 列），以空格分隔：" << endl;
    for (int i = 0; i < num_cells_to_activate; i++) {
        int row, col;
        cin >> row >> col;
        grid[row][col] = 1;
    }

    print_grid(grid);

    int generation = 0;
    while ((max_generations == -1 || generation < max_generations) && count_alive_cells(grid) > 0) {
        grid = generate_next_generation(grid);
        print_grid(grid);
        usleep(200000); // 暂停200毫秒
        generation++;
    }

    return 0;
}

void print_grid(const vector<vector<int>>& grid) {
    system("clear");
    for (const auto& row : grid) {
        for (int cell : row) {
            if (cell == 1) {
                cout << "O ";
            } else {
                cout << ". ";
            }
        }
        cout << endl;
    }
}

vector<vector<int>> generate_next_generation(const vector<vector<int>>& grid) {
    vector<vector<int>> next_grid = grid;

    for (size_t row = 0; row < grid.size(); row++) {
        for (size_t col = 0; col < grid[row].size(); col++) {
            int neighbors = count_neighbors(row, col, grid);

            if (grid[row][col] == 1 && (neighbors < 2 || neighbors > 3)) {
                next_grid[row][col] = 0;
            } else if (grid[row][col] == 0 && neighbors == 3) {
                next_grid[row][col] = 1;
            }
        }
    }

    return next_grid;
}

bool check_bounds(int row, int col, const vector<vector<int>>& grid) {
    return row >= 0 && col >= 0 && row < grid.size() && col < grid[row].size();
}

int count_neighbors(int row, int col, const vector<vector<int>>& grid) {
    int count = 0;

    for (int r = row - 1; r <= row + 1; r++) {
        for (int c = col - 1; c <= col + 1; c++) {
            if ((r != row || c != col) && check_bounds(r, c, grid) && grid[r][c] == 1) {
                count++;
            }
        }
    }

    return count;
}

int count_alive_cells(const vector<vector<int>>& grid) {
    int count = 0;
    for (const auto& row : grid) {
        for (int cell : row) {
            if (cell == 1) {
                count++;
            }
        }
    }
    return count;
}