#include <iostream>
#include <cstdlib>
using namespace std;

class Board {
    public:

        Board() {
            for (int i = 0; i < 9; i++) {
                for (int j = 0; j < 9; j++) {
                    board[i][j] = 0;
                }
            }
            generateBoard();
        }

        void printBoard() {
            cout << "\n";
            for (int i = 0; i < 9; i++) {
                for (int j = 0; j < 9; j++) {
                    cout << playerboard[i][j];
                    if (j!= 8) {
                        cout << " ";
                        if (j%3 == 2) {
                            cout << "| ";
                        }
                    } else {
                        cout << "\n";
                    }
                }
                if (i != 8 && i%3 == 2) {
                    for (int k = 0; k < 21; k++) {
                        cout << "-";
                    }
                    cout << "\n";
                }
            }
            cout << "\n";
        }

        void generateBoard() {
            int row, col;
            int c1, c2, c3, c4, c5, c6;
            c1 = c2 = c3 = c4 = c5 = c6 = 0;
            while (!finished(row, col)) {
                int num = (rand()%9) + 1;
                bool vert = vertCheck(col, num);
                bool hor = horCheck(row, num);
                bool box = boxCheck(row, col, num);
                if (vert && box && hor) {
                    board[row][col] = num;
                } else {
                    c1++;
                    if (c1 > 9) {
                    c1 = 0;
                    c2++;
                    if (c2 > 9) {
                        c2 = 0;
                        c3++;
                        if (c3 > 9) {
                            c3 = 0;
                            c4++;
                            if (c4 > 9) {
                                c4 = 0;
                                c5++;
                                if (c5 > 9) {
                                    c5 = 0;
                                    c6++;
                                    if (c6 > 3) {
                                        c6 = 0;
                                        reset();
                                    }
                                    back(row, col);
                                }
                                back(row, col);
                            }
                            back(row, col);
                        }
                        back(row, col);
                    }
                    back(row, col);
                }
                }
            }
            for (int l = 0; l < 9; l++) {
                for (int m = 0; m < 9; m++) {
                    playerboard[l][m] = board[l][m] + '0';
                }
            }    
        }

        void reset() {
            for (int i = 0; i < 9; i++) {
                for (int j = 0; j < 9; j++) {
                    board[i][j] = 0;
                }
            }
        }

        void back (int row, int col) {
            if ((row == 0 && col == 1) || (row == 0 && col == 0)) {
                return;
            } else if (col == 0) {
                col = 8;
                row--;
            } else {
                col--;
            }
            board[row][col] = 0;
        }

        bool vertCheck(int col, int num) {
            for (int i = 0; i < 9; i++) {
                if (board[i][col] == num) {
                    return false;
                }
            }
            return true;
        }

        bool horCheck(int row, int num) {
            for (int i = 0; i < 9; i++) {
                if (board[row][i] == num) {
                    return false;
                }
            }
            return true;
        }

        bool checkWin() {
            for (int i = 0; i < 9; i++) {
                for (int j = 0; j < 9; j++) {
                    if ((playerboard[i][j] - '0') != board[i][j]) {
                        return false;
                    }
                }
            }
            return true;
        }

        bool boxCheck(int row, int col, int num) {
            for (int i = (row/3)*3; i < (row/3)*3 + 3; i++) {
                for (int j = (col/3)*3; j < (col/3)*3 + 3; j++) {
                    if (board[i][j] == num) {
                        return false;
                    }
                }
            }
            return true;
        }
        void setDifficulty(char difficulty) {
            int hiddenSquares = 0;
            if (difficulty == 'E') {
                hiddenSquares = 0.5 * 81;
            } else if (difficulty == 'M') {
                hiddenSquares = 0.65 * 81;
            } else {
                hiddenSquares = 0.8 * 81;
            }
            while (hiddenSquares > 0) {
                int row = (rand()%9);
                int col = (rand()%9);
                if (playerboard[row][col] != ' ') {
                    playerboard[row][col] = ' ';
                    hiddenSquares--;
                }
            }
            
        }

        bool finished(int& row, int& col) {
            for (int i = 0; i < 9; i++) {
                for (int j = 0; j < 9; j++) {
                    if (board[i][j] == 0) {
                        row = i;
                        col = j;
                        return false;
                    }
                }
            }
            return true;
        }

        int board[9][9];
        char playerboard[9][9];
};

int main() {
    srand(time(NULL));
    cout << "\nWelcome to Sudoku!" << endl;

        Board b;
        char difficulty;
        cout << "\nSelect your difficulty: E for Easy, M for Medium, and H for Hard." << endl;
        cin >> difficulty;
        while (difficulty != 'E' && difficulty != 'M' && difficulty != 'H') {
            cout << "\nPlease select a valid difficulty." << endl;
            cout << "\nSelect your difficulty: E for Easy, M for Medium, and H for Hard." << endl;
            cin >> difficulty;
        }
        b.setDifficulty(difficulty);
        while (true) {
            b.printBoard();
            int row, col, num;
            cout << "Enter the number you want to guess or 0 to quit: ";
            cin >> num;
            if (num == 0) {
                cout << "\nThanks for playing!" << endl;
                break;
            } else if (num < 1 || num > 9) {
                cout << "\nPlease enter a valid number." << endl;
            } else {
            cout << "\nEnter the row and column for your guess: ";
            cin >> row >> col;
            if (row < 0 || row > 8 || col < 0 || col > 8) {
                cout << "\nInvalid row and column values. Guess again." << endl;
            } else if (b.playerboard[row][col] != ' ') {
                cout << "\nYou can't guess there! Guess again." << endl;
            } else if (b.board[row][col] != num) {
                cout << "\nIncorrect! Guess again." << endl;
            } else {
                b.playerboard[row][col] = '0' + num;
                cout << "\nCorrect!" << endl;
                if (b.checkWin()) {
                    cout << "\nCongratulations! You won!" << endl;
                    b.printBoard();
                    break;
                }
            }
            }
        }
    
}

