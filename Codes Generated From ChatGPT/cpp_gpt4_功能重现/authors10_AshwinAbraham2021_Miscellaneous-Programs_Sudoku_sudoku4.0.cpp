#include <iostream>
#include <vector>

using namespace std;

bool isSafe(vector<vector<char>> &board, int row, int col, char num) {
    for (int i = 0; i < 9; i++) {
        if (board[row][i] == num) return false;
        if (board[i][col] == num) return false;
        if (board[3 * (row / 3) + i / 3][3 * (col / 3) + i % 3] == num) return false;
    }
    return true;
}

bool solve(vector<vector<char>> &board) {
    int row = -1;
    int col = -1;
    bool isEmpty = true;

    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (board[i][j] == '.') {
                row = i;
                col = j;
                isEmpty = false;
                break;
            }
        }
        if (!isEmpty) break;
    }

    if (isEmpty) return true;

    for (char num = '1'; num <= '9'; num++) {
        if (isSafe(board, row, col, num)) {
            board[row][col] = num;
            if (solve(board)) return true;
            board[row][col] = '.';
        }
    }
    return false;
}

void printBoard(const vector<vector<char>> &board) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    vector<vector<char>> board(9, vector<char>(9));
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            cin >> board[i][j];
        }
    }

    if (solve(board)) {
        printBoard(board);
    } else {
        cout << "No solutions" << endl;
    }

    return 0;
}
