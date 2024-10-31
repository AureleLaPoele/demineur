#include <iostream>
#include <cstdlib>
#include <ctime>
#include <windows.h>
using namespace std;


struct tab {
    bool revl;
    bool bombe;
    bool flag;
    bool vide;
    bool recursion;
    bool start;
};

bool Game = true;
const int BOARD_SIZE = 10;
const char PLAIN = 'B';
const char EMPTY = ' ';
const char FLAG = 'F';
struct tab board[BOARD_SIZE][BOARD_SIZE];

void endl() {
    cout << endl;
}

//void coul(int nombre) {
//    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
//
//    // Définir la couleur en fonction du nombre
//    if (nombre < 0) {
//        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_INTENSITY); // Rouge
//    }
//    else if (nombre == 0) {
//        SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_INTENSITY); // Jaune
//    }
//    else {
//        SetConsoleTextAttribute(hConsole, FOREGROUND_GREEN | FOREGROUND_INTENSITY); // Vert
//    }
//
//}
//
//void defaultColor() {
//    SetConsoleTextAttribute(hConsole, FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE);
//}

void displayBoard() {
    cout << "   ";
    for (int i = 0; i < BOARD_SIZE; i++) {
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
            board[i][j].recursion = false;
            if (board[i][j].bombe == true && board[i][j].revl == true) {
                //coul(-5);
                cout << PLAIN << "|";
                //defaultColor();
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

void update() {
    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            if (board[i][j].bombe == false) {
                int aqbomb = 0;
                for (int x = i - 1; x <= i + 1; x++) {
                    for (int y = j - 1; y <= j + 1; y++) {
                        if (x >= 0 && x < BOARD_SIZE && y >= 0 && y < BOARD_SIZE) {
                            if (board[x][y].bombe) {
                                aqbomb++;
                            }
                        }
                    }
                }
                if (!(aqbomb > 0)) {
                    board[i][j].vide = true;
                }
            }
        }
    }
}


void startProtection(int j, int i) {
    for (int k = 0; k < 9; k++)
    {
        int y = k / 3;
        int x = k % 3;
        int xNDC = (2.0f * x) / 2 - 1.0f;
        int yNDC = (2.0f * y) / 2 - 1.0f;
        if ((i + xNDC) >= 0 && (i + xNDC) < BOARD_SIZE) {
            if ((j + yNDC) >= 0 && (j + yNDC) < BOARD_SIZE) {
                board[i + xNDC][j + yNDC].start = true;
            }
        }
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
                    if (bombe < 15 && board[i][j].bombe == false) {
                        if (!board[i][j].start) {
                            board[i][j].bombe = true;
                            n_bombe--;
                        }
                    }
                }
            }
        }
    }
    update();
}

void revlArround(int j, int i) {
    for (int k = 0; k < 9; k++)
    {
        int y = k / 3;
        int x = k % 3;
        int xNDC = (2.0f * x) / 2 - 1.0f;
        int yNDC = (2.0f * y) / 2 - 1.0f;
        if ((i + xNDC) >= 0 && (i + xNDC) < BOARD_SIZE) {
            if ((j + yNDC) >= 0 && (j + yNDC) < BOARD_SIZE) {
                board[i + xNDC][j + yNDC].revl = true;
                if (board[i + xNDC][j + yNDC].vide && !(board[i + xNDC][j + yNDC].recursion)) {
                    board[i + xNDC][j + yNDC].recursion = true;
                    revlArround(j + yNDC, i + xNDC);
                }
            }
        }
    }
}

//void revlArround(int j, int i) {
//    if (board[i][j].vide) {
//        board[i - 1][j - 1].revl = true;
//        if (board[i - 1][j - 1].vide) {
//            revlArround(j-1, i-1);
//        }
//        board[i][j - 1].revl = true;
//        if (board[i][j - 1].vide) {
//            revlArround(j-1, i);
//        }
//        board[i + 1][j - 1].revl = true;
//        if (board[i + 1][j - 1].vide) {
//            revlArround(j-1, i+1);
//        }
//        board[i - 1][j].revl = true;
//        if (board[i - 1][j].vide) {
//            revlArround(j, i-1);
//        }
//        board[i + 1][j].revl = true;
//        if (board[i + 1][j].vide) {
//            revlArround(j, i+1);
//        }
//        board[i - 1][j + 1].revl = true;
//        if (board[i - 1][j + 1].vide) {
//            revlArround(j+1, i-1);
//        }
//        board[i][j + 1].revl = true;
//        if (board[i][j + 1].vide) {
//            revlArround(j+1, i);
//        }
//        board[i + 1][j + 1].revl = true;
//        if (board[i + 1][j + 1].vide) {
//            revlArround(j+1, i+1);
//        }
//    }
//}

bool revl(int j, int i) {
    if (board[i][j].bombe == true) {
        board[i][j].revl = true;
        cout << "PERDU !" << endl;
        return Game = false;
    }
    else if (board[i][j].vide == true) {
        board[i][j].revl = true;
        revlArround(j, i);
    }
    else {
        board[i][j].revl = true;
    }
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

void revlStart() {
    int j;
    int i;
    cout << "\nColonne : ";
    cin >> j;
    cout << "\nLigne : ";
    cin >> i;
    board[i][j].revl = true;
    startProtection(j, i);
    generate_bomb();
    revlArround(j, i);


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
    displayBoard();
    //generate_bomb();
    int selectedItem = 0;
    revlStart();
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
        else if (selectedItem == 3) {
            revlall();
        }
        displayBoard();
        update();
    }
}