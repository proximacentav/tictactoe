//название файла: tictactoe.cpp
//крестики-нолики версия 0.1.0 от proximacentav на github (https://github.com/proximacentav)

#include <iostream>
#include <cstdlib>
#include <ctime>
#include <limits>

using namespace std;

//константы для цветов
const string BLUE = "\033[34m";
const string RED = "\033[31m";
const string RESET = "\033[0m";

//поле 3x3 в виде матрицы
char board[9];


void initBoard() {
    for (int i = 0; i < 9; i++) {
        board[i] = ' ';
    }
}

//вывод поля с номерами свободных клеток
void printBoard() {
    cout << endl;
    for (int i = 0; i < 9; i++) {
        if (board[i] == ' ') {
            cout << " " << i+1 << " ";
        } else {
            if (board[i] == 'X') {
                cout << RED << " " << board[i] << " " << RESET;
            } else { // '0'
                cout << BLUE << " " << board[i] << " " << RESET;
            }
        }
        //разделение между столбцами
        if (i % 3 != 2) {
            cout << "|";
        } else if (i != 8) {
            cout << endl;
            cout << "---+---+---" << endl;
        }
    }
    cout << endl << endl;
}

char checkWin() {
    //все выигрышные комбинации 
    int wins[8][3] = {
        {0,1,2}, {3,4,5}, {6,7,8}, // горизонтальныи
        {0,3,6}, {1,4,7}, {2,5,8}, // вертикальные
        {0,4,8}, {2,4,6}           // искозовые
    };
    for (int i = 0; i < 8; i++) {
        char a = board[wins[i][0]];
        char b = board[wins[i][1]];
        char c = board[wins[i][2]];
        if (a != ' ' && a == b && b == c) {
            return a;
        }
    }
    return ' ';
}

//если на поле нет больше СВОбодного места
bool isFull() {
    for (int i = 0; i < 9; i++) {
        if (board[i] == ' ') return false;
    }
    return true;
}

bool makeMove(int pos, char player) {
    if (pos < 1 || pos > 9) return false;
    if (board[pos-1] != ' ') return false;
    board[pos-1] = player;
    return true;
}

int main() {
    srand(time(0));   //для того кто ходит первым то есть смена сида для генератора рандома

    bool playAgain = true;

    while (playAgain) {
        initBoard();

        //кто ходит первым: 0-0, 1-x
        int first = rand() % 2;
        char currentPlayer;
        if (first == 0) {
            currentPlayer = '0';
            cout << BLUE << "blue (0) goes first" << RESET << endl;
        } else {
            currentPlayer = 'X';
            cout << RED << "red (X) goes first" << RESET << endl;
        }

        bool gameOver = false;
        char winner = ' ';

        while (!gameOver) {
            printBoard();

            int move;
            bool valid = false;
            while (!valid) {
                if (currentPlayer == 'X') {
                    cout << RED << "red X turn, choose cell (1-9): " << RESET;
                } else {
                    cout << BLUE << "blue 0 turn, choose cell (1-9): " << RESET;
                }
                cin >> move;

                if (cin.fail()) {
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "invalid input, enter a number." << endl;
                    continue;
                }
                valid = makeMove(move, currentPlayer);
                if (!valid) {
                    cout << "ERROR: maybe cell isn't valid " << endl;
                }
            }

            //проверка победы после хода
            winner = checkWin();
            if (winner != ' ') {
                printBoard();
                gameOver = true;
                break;
            }

            //проверка ничьей
            if (isFull()) {
                printBoard();
                cout << "it's a draw!" << endl;
                gameOver = true;
                break;
            }

            //смена игрока
            currentPlayer = (currentPlayer == 'X') ? '0' : 'X';
        }

        //при победе кого то
        if (winner != ' ') {

            if (winner == 'X') {
                cout << RED << "you win!" << RESET << endl;
                cout<< RED << "X is winned" << RESET << endl;
            } else {
                cout << BLUE << "you win!" << RESET << endl;
                cout << BLUE << "0 is winned" << RESET << endl;
            }
        }

        char ans;
        cout << "play again? (y/n): ";
        cin >> ans;
        if (ans != 'y' && ans != 'Y') {
            playAgain = false;
        }
        cout << endl;
    }

    return 0;
}