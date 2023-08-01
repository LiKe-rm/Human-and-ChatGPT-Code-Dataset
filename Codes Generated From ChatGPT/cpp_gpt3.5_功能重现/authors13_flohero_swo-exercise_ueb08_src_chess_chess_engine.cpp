#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <ctime>
#include <cstdlib>

class ChessBoard {
public:
    ChessBoard() {
        board.resize(8, std::vector<char>(8, ' '));
        initializeBoard();
    }

    void initializeBoard() {
        // 这里仅初始化了一个简单的棋盘，可根据需要进行修改
        for (int i = 0; i < 8; ++i) {
            board[1][i] = 'P';
            board[6][i] = 'p';
        }
        board[0][0] = board[0][7] = 'R';
        board[7][0] = board[7][7] = 'r';
    }

    void printBoard() const {
        for (const auto &row : board) {
            for (char c : row) {
                std::cout << c << ' ';
            }
            std::cout << '\n';
        }
    }

    char getPieceAt(int row, int col) const {
        return board[row][col];
    }

    void movePiece(int fromRow, int fromCol, int toRow, int toCol) {
        board[toRow][toCol] = board[fromRow][fromCol];
        board[fromRow][fromCol] = ' ';
    }

private:
    std::vector<std::vector<char>> board;
};

enum class GameMode {
    PLAYER_VS_PLAYER,
    PLAYER_VS_COMPUTER
};

class ChessGame {
public:
    ChessGame(GameMode gameMode) : gameMode(gameMode), currentPlayer('P') {
    }

    void gameLoop() {
        while (!isGameOver()) {
            chessBoard.printBoard();
            std::cout << "当前执子方: " << (currentPlayer == 'P' ? "白方" : "黑方") << '\n';

            int fromRow, fromCol, toRow, toCol;
            if (gameMode == GameMode::PLAYER_VS_COMPUTER && currentPlayer == 'p') {
                autoMovePiece(fromRow, fromCol, toRow, toCol);
            } else {
                promptPieceSelection(fromRow, fromCol);
                promptPieceMove(fromRow, fromCol, toRow, toCol);
            }

            chessBoard.movePiece(fromRow, fromCol, toRow, toCol);
            if (isGameOver()) {
                std::cout << "游戏结束！胜利者是：" << (currentPlayer == 'P' ? "白方" : "黑方") << '\n';
            }

            switchPlayer();
        }
    }

private:
    bool isGameOver() const {
        // 这里仅实现一个简单的判断，可根据需要进行修改
        return false;
    }

    void promptPieceSelection(int &row, int &col) {
        while (true) {
            std::cout << "请输入棋子的位置：";
            std::cin >> row >> col;
            if (chessBoard.getPieceAt(row, col) == currentPlayer) {
                break;
            }
            std::cout << "无效的输入，请重新选择。\n";
        }
    }

    void promptPieceMove(int fromRow, int fromCol, int &toRow, int &toCol) {
        // 这里仅实现一个简单的移动提示，可根据需要进行修改
        std::cout << "请输入目标位置：";
        std::cin >> toRow >> toCol;
    }

       void autoMovePiece(int &fromRow, int &fromCol, int &toRow, int &toCol) {
        // 这里仅实现一个简单的自动移动，可根据需要进行修改
        std::srand(std::time(nullptr));
        while (true) {
            fromRow = std::rand() % 8;
            fromCol = std::rand() % 8;
            if (chessBoard.getPieceAt(fromRow, fromCol) == currentPlayer) {
                break;
            }
        }
        toRow = std::rand() % 8;
        toCol = std::rand() % 8;
        std::cout << "电脑选择 " << fromRow << "," << fromCol << " 到 " << toRow << "," << toCol << '\n';
    }

    void switchPlayer() {
        currentPlayer = (currentPlayer == 'P') ? 'p' : 'P';
    }

private:
    ChessBoard chessBoard;
    GameMode gameMode;
    char currentPlayer;
};

GameMode promptGameMode() {
    std::cout << "欢迎来到棋盘游戏！请选择游戏模式：\n";
    std::cout << "1. 玩家对战\n";
    std::cout << "2. 玩家对电脑\n";

    int choice;
    std::cin >> choice;
    return (choice == 1) ? GameMode::PLAYER_VS_PLAYER : GameMode::PLAYER_VS_COMPUTER;
}

int main() {
    GameMode gameMode = promptGameMode();
    ChessGame game(gameMode);
    game.gameLoop();
    return 0;
}

