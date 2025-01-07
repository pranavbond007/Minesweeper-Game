#include <iostream>
#include <vector>
#include <ctime>
#include <cstdlib>

using namespace std;

const int BOARD_SIZE = 5;
const int NUM_BOMBS = 5;

void placeBombs(vector<vector<bool>> &bombs) {
    int placedBombs = 0;
    while (placedBombs < NUM_BOMBS) {
        int row = rand() % BOARD_SIZE;
        int col = rand() % BOARD_SIZE;

        if (!bombs[row][col]) {
            bombs[row][col] = true;
            placedBombs++;
        }
    }
}


int countAdjacentBombs(const vector<vector<bool>> &bombs, int row, int col) {
    int count = 0;
    for (int i = -1; i <= 1; ++i) {
        for (int j = -1; j <= 1; ++j) {
            int newRow = row + i;
            int newCol = col + j;
            if (isValidCell(newRow, newCol) && bombs[newRow][newCol]) {
                count++;
            }
        }
    }
    return count;
}



void displayBoard(const vector<vector<char>> &board) {
    cout << "\nCurrent Board:" << endl;
    for (int i = 0; i < BOARD_SIZE; ++i) {
        for (int j = 0; j < BOARD_SIZE; ++j) {
            cout << board[i][j] << ' ';
        }
        cout << endl;
    }
}

bool revealCell(vector<vector<char>> &board, const vector<vector<bool>> &bombs, int row, int col) {
    if (bombs[row][col]) {
        board[row][col] = '*';
        return false;
    }

    int adjacentBombs = countAdjacentBombs(bombs, row, col);
    board[row][col] = '0' + adjacentBombs;

    return true;
}

bool isValidCell(int row, int col) {
    return row >= 0 && row < BOARD_SIZE && col >= 0 && col < BOARD_SIZE;
}

void initializeBoard(vector<vector<char>> &board, vector<vector<bool>> &bombs) {
    placeBombs(bombs);
}

int main() {
    srand(static_cast<unsigned int>(time(0)));
    vector<vector<char>> board(BOARD_SIZE, vector<char>(BOARD_SIZE, '-'));
    vector<vector<bool>> bombs(BOARD_SIZE, vector<bool>(BOARD_SIZE, false));

    initializeBoard(board, bombs);

    bool gameOver = false;
    int revealedCells = 0;
    int totalCells = BOARD_SIZE * BOARD_SIZE - NUM_BOMBS;

    cout << "Welcome to Minesweeper!" << endl;

    while (!gameOver) {
        displayBoard(board);

        int row, col;
        cout << "Enter the row and column to reveal (0-based index): ";
        cin >> row >> col;

        if (!isValidCell(row, col)) {
            cout << "Invalid input. Please try again." << endl;
            continue;
        }

        if (revealCell(board, bombs, row, col)) {
            revealedCells++;
        } else {
            gameOver = true;
            cout << "Game Over! You hit a bomb!" << endl;
        }

        if (revealedCells == totalCells) {
            cout << "Congratulations! You've cleared the board!" << endl;
            gameOver = true;
        }
    }

    displayBoard(board);
    return 0;
}






