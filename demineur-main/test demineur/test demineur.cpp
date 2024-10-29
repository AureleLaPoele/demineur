#include <iostream>
#include <cstdlib>
#include <ctime>
using namespace std;

struct tab {
    bool revl;
    bool bombe;
    bool flag;
    bool vide;
};

bool Game = true;
const int BOARD_SIZE = 16;
const char PLAIN = 'B';
const char EMPTY = ' ';
const char FLAG = 'F';
struct tab board[BOARD_SIZE][BOARD_SIZE];

void endl() {
    cout << endl;
}

void displayBoard() {
    cout << "   ";
    for (int i = 0; i < BOARD_SIZE ; i++) {
        if (i < 10) {
            cout << " " << i;
        }
        else {
            cout << i;
        }
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
            else if (board[i][j].flag == true) {
                cout << FLAG << "|";
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

void revealAround() {

}

void flag(int j, int i) {
    if (board[i][j].flag != true && board[i][j].revl != true) {
        board[i][j].flag = true;
    }
    else if (board[i][j].flag == true) {
        board[i][j].flag = false;
    }
    else {
        cout << "Cette case ne peut pas être marqué car elle est reveal";
        endl();
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
    int selectedItem = 0;
    generate_bomb();
    displayBoard();
    while (Game) {
        int i;
        int j;
        endl();
        cout << "1. Reveler une case\n";
        cout << "2. Placer ou enlever un drapeau\n";
        cout << "Veuillez choisir une action : ";
        cin >> selectedItem;
        endl();
        if (selectedItem == 1) {
            cout << "Colonne : ";
            cin >> j;
            cout << "\nLigne : ";
            cin >> i;
            revl(j, i);
        }
        else if (selectedItem == 2) {
            cout << "Colonne : ";
            cin >> j;
            cout << "\nLigne : ";
            cin >> i;
            flag(j, i);
        }
        //revlall();
        displayBoard();
        
    }
}