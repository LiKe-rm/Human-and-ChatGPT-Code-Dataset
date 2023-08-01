#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

const int MAX_ROUNDS = 27;
const int BOARD_ROWS = 11;
const int BOARD_COLS = 10;

void print_board(int board[BOARD_ROWS][BOARD_COLS]) {
    for (int i = 0; i < BOARD_ROWS; i++) {
        for (int j = 0; j < BOARD_COLS; j++) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    srand(time(0));

    int dice, player1_health = 100, player2_health = 100;
    int player1_row = 0, player1_col = 0, player2_row = 0, player2_col = 0;
    int current_round = 0;
    bool game_over = false;

    int game_board[BOARD_ROWS][BOARD_COLS] = {
        {0, 0, 0, 1, 2, 0, 0, 3, 0, 0},
        {0, 0, 1, 0, 0, 0, 2, 0, 0, 0},
        {0, 2, 0, 0, 0, 1, 0, 0, 0, 0},
        {1, 0, 0, 0, 0, 0, 0, 0, 2, 0},
        {0, 0, 0, 1, 0, 0, 0, 0, 0, 3},
        {0, 0, 0, 0, 0, 2, 0, 0, 1, 0},
        {3, 0, 0, 0, 0, 0, 0, 1, 0, 0},
        {0, 0, 0, 0, 2, 0, 0, 0, 0, 1},
        {0, 0, 1, 0, 0, 0, 2, 0, 0, 0},
        {0, 3, 0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 1, 2, 0, 0, 3, 0, 0}
    };

    do {
        current_round++;
        cout << "Round: " << current_round << endl;
        print_board(game_board);

        dice = (rand() % 6) + 1;
        cout << "Player 1 rolls: " << dice << endl;
        player1_col += dice;
        if (player1_col >= BOARD_COLS) {
            player1_row++;
            player1_col %= BOARD_COLS;
        }

        int tile = game_board[player1_row][player1_col];
        switch (tile) {
            case 1:
                player1_health += 10;
                break;
            case 2:
                player1_health -= 10;
                break;
            case 3:
                player1_health -= 20;
                break;
        }

        if (player1_health <= 0) {
            game_over = true;
            cout << "Player 2 wins!" << endl;
            break;
        }

        dice = (rand() % 6) + 1;
        cout << "Player 2 rolls: " << dice << endl;
        player2_col += dice;
        if (player2_col >= BOARD_COLS) {
            player2_row++;
            player2_col %= BOARD_COLS;
        }

        tile = game_board[player2_row][player2_col];
        switch (tile) {
            case 1:
                player2_health += 10;
                break;
            case 2:
                player2_health -= 10;
                break;
            case 3:
                player2_health -= 20;
                break;
        }

        if (player2_health <= 0) {
            game_over = true;
            cout << "Player 1 wins!" << endl;
            break;
        }

        if (player1_row == BOARD_ROWS - 1 && player1_col == BOARD_COLS - 1) {
            game_over = true;
            cout << "Player 1 wins!" << endl;
            break;
        }

        if (player2_row == BOARD_ROWS - 1 && player2_col == BOARD_COLS - 1) {
            game_over = true;
            cout << "Player 2 wins!" << endl;
            break;
        }

        cout << "Player 1 health: " << player1_health << endl;
        cout << "Player 2 health: " << player2_health << endl;
        cout << "--------------------------" << endl;

    } while (!game_over && current_round < MAX_ROUNDS);

    if (!game_over) {
        cout << "Game over. No winner!" << endl;
    }

    return 0;
}

