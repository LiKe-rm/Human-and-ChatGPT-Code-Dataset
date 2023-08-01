#include <iostream>
#include <vector>

using namespace std;

// 打印数独棋盘
void printBoard(vector<vector<char>>& board) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cout << board[i][j] << " ";
            if ((j + 1) % 3 == 0 && j != 8) {
                cout << "| ";
            }
        }
        cout << endl;
        if ((i + 1) % 3 == 0 && i != 8) {
            cout << "------+-------+------" << endl;
        }
    }
}

// 判断某个数字是否在当前行中出现过
bool isInRow(vector<vector<char>>& board, int row, char num) {
    for (int col = 0; col < 9; col++) {
        if (board[row][col] == num) {
            return true;
        }
    }
    return false;
}

// 判断某个数字是否在当前列中出现过
bool isInCol(vector<vector<char>>& board, int col, char num) {
    for (int row = 0; row < 9; row++) {
        if (board[row][col] == num) {
            return true;
        }
    }
    return false;
}

// 判断某个数字是否在当前3x3宫格中出现过
bool isInBox(vector<vector<char>>& board, int startRow, int startCol, char num) {
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            if (board[startRow + row][startCol + col] == num) {
                return true;
            }
        }
    }
    return false;
}

// 判断当前位置是否可以放置数字
bool isValid(vector<vector<char>>& board, int row, int col, char num) {
    return !isInRow(board, row, num) &&
           !isInCol(board, col, num) &&
           !isInBox(board, row - row % 3, col - col % 3, num);
}

// 在数独棋盘中找到一个空白位置，返回其行列值
bool findEmpty(vector<vector<char>>& board, int& row, int& col) {
    for (row = 0; row < 9; row++) {
        for (col = 0; col < 9; col++) {
            if (board[row][col] == '.') {
                return true;
            }
        }
    }
    return false;
}

// 使用回溯算法求解数独
bool solve(vector<vector<char>>& board) {
    int row, col;
    if (!findEmpty(board, row, col)) {
        return true; // 找到了一个可行解
    }
    for (char num = '1'; num <= '9'; num++) {
        if (isValid(board, row, col, num)) {
            board[row][col] = num;
            if (solve(board)) {
                return true; // 找到了一个可行解
            }
            board[row][col] = '.'; // 撤销当前选择
        }
    }
    return false; // 没有找到可行
}

int main() {
    vector<vector<char>> board(9, vector<char>(9));
    cout << "Please input the Sudoku board: " << endl;
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cin >> board[i][j];
        }
    }
    if (solve(board)) {
        cout << "Solution:" << endl;
        printBoard(board);
    } else {
        cout << "No solutions" << endl;
    }
    return 0;
}