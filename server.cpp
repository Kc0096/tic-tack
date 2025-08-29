#include <iostream>
#include <string>
using namespace std;

char board[3][3];
char currentPlayer = 'X';
bool initialized = false;
bool gameOver = false;

void initializeBoard() {
    char pos = '1';
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++)
            board[i][j] = pos++;
}

bool makeMove(int position) {
    int row = (position - 1) / 3;
    int col = (position - 1) % 3;
    if (position < 1 || position > 9 || board[row][col] == 'X' || board[row][col] == 'O')
        return false;
    board[row][col] = currentPlayer;
    return true;
}

bool checkWin() {
    for (int i = 0; i < 3; i++) {
        if ((board[i][0] == currentPlayer && board[i][1] == currentPlayer && board[i][2] == currentPlayer) ||
            (board[0][i] == currentPlayer && board[1][i] == currentPlayer && board[2][i] == currentPlayer))
            return true;
    }
    if ((board[0][0] == currentPlayer && board[1][1] == currentPlayer && board[2][2] == currentPlayer) ||
        (board[0][2] == currentPlayer && board[1][1] == currentPlayer && board[2][0] == currentPlayer))
        return true;
    return false;
}

bool checkDraw() {
    for (int i=0;i<3;i++)
        for (int j=0;j<3;j++)
            if (board[i][j] != 'X' && board[i][j] != 'O')
                return false;
    return true;
}

void switchPlayer() {
    currentPlayer = (currentPlayer=='X') ? 'O' : 'X';
}

int main(int argc, char* argv[]) {
    if (!initialized) {
        initializeBoard();
        initialized = true;
    }

    if (argc > 1) {
        int move = stoi(argv[1]);
        if (!gameOver && makeMove(move)) {
            if (checkWin()) {
                gameOver = true;
                cout << "{ \"status\": \"win\", \"winner\": \"" << currentPlayer << "\" }";
                return 0;
            }
            if (checkDraw()) {
                gameOver = true;
                cout << "{ \"status\": \"draw\" }";
                return 0;
            }
            switchPlayer();
        } else {
            cout << "{ \"status\": \"invalid\" }";
            return 0;
        }
    }

    cout << "{ \"status\": \"ok\", \"currentPlayer\": \"" << currentPlayer << "\", \"board\":[";
    for (int i=0;i<3;i++) {
        cout << "[";
        for (int j=0;j<3;j++) {
            cout << "\"" << board[i][j] << "\"";
            if (j<2) cout << ",";
        }
        cout << "]";
        if (i<2) cout << ",";
    }
    cout << "] }";
    return 0;
}
