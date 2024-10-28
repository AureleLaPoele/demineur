#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

struct tab {
    bool revl;
    bool bombe;
};

bool Game = true;
const int BOARD_SIZE = 16;
const char PLAIN = 'B';
const char EMPTY = ' ';
struct tab board[BOARD_SIZE][BOARD_SIZE];

void displayBoard() {
    cout << "   ";
    for (int i = 0; i < BOARD_SIZE ; i++) {
        cout << " " << i << " ";
    }
    cout << endl;
    for (int i = 0; i < BOARD_SIZE; i++) {

        cout << i;
        if (i < 10) {
            cout << "  ";
        }
        else {
            cout << " ";
        }
        cout << "|";

        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j].bombe == true && board[i][j].revl == true) {
                cout << PLAIN << "|";
            }
            else if (board[i][j].bombe == false && board[i][j].revl == true) {
                int abomb = 0;
                for (int x = i - 1; x <= i + 1; x++) {
                    for (int y = j - 1; y <= j + 1; y++) {
                        if (x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE) {
                            if (board[x][y].bombe) {
                                abomb++;
                            }
                        }
                    }
                }
                if (abomb > 0) {
                    cout << abomb << "|";
                }
                else {
                    cout << EMPTY << "|";
                }
            }
            else {
                cout << "X" << "|";
            }
        }
        cout << endl;
    }
}


void generate_bomb() {
    int n_bombe = (BOARD_SIZE * BOARD_SIZE) * (15.0f / 100.0f);
    srand((unsigned int)time(0));
    while (n_bombe > 0) {
        for (int i = 1; i < BOARD_SIZE; i++) {
            for (int j = 1; j < BOARD_SIZE; j++) {
                if (n_bombe == 0) {
                    break;
                    break;
                }
                else {
                    int bombe = rand() % 100 + 1;
                    if (bombe < 15 and board[i][j].bombe == false) {
                        board[i][j].bombe = true;
                        n_bombe--;
                    }
                }
            }
        }
    }
}

bool revl(int j, int i) {
    if (board[i][j].bombe == true) {
        board[i][j].revl = true;
        cout << "PERDU !" << endl;
        return Game = false;
    }
    else {
        board[i][j].revl = true;
    }

}

void revlall() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j].revl = true;
        }
    }
}

int main()
{
    generate_bomb();
    displayBoard();
    while (Game) {
        int j;
        int i;
        cout << "Quelle case veux tu reveler ?" << endl;
        cin >> j;
        cin >> i;
        revl(j, i);
        //revlall();
        displayBoard();
    }
}