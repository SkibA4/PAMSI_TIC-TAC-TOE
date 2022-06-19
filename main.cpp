#include "game.h"

int main() {
    int depth = 3, size = 3, winningCount = 3;
    char choice = ' ';
    enum { easy, medium, hard };
    int difficulty = medium;
    string unuseable;

    while (true) {
        cout << endl;
		cout << "--------------------------------------" << endl;
		cout << "----- Tic-Tac-Toe vs AI by SkibA -----" << endl;
		cout << "--------------------------------------" << endl;
        cout << "            Game Info:               " << endl;
        cout << "            size: " << size << "x" << size << endl;
        if (difficulty == easy) cout << "            difficulty: easy" << endl;
        if (difficulty == medium) cout << "            difficulty: medium" << endl;
        if (difficulty == hard) cout << "            difficulty: hard" << endl;
        cout << "            winning count: " << winningCount << endl;
        cout << "--------------------------------------" << endl;
        cout << "  1 - Change board size" << endl;
		cout << "  2 - Change winning count" << endl;
		cout << "  3 - Difficulty" << endl;
		cout << "  4 - START!" << endl;
		cout << "  0 - Exit" << endl;
		cout << "  Your choice: ";
        cin >> choice;
        cout << "--------------------------------------" << endl;
        switch (choice) {
            case '1': {
                cout << "Insert board size: ";
                cin >> size;
                while (size < 3) {
                    cout << "Size too small! Try again..." << endl;
                    cout << "Insert board size: ";
                    cin >> size;
                }
                break;
            }
            case '2': {
                cout << "Insert winning count: ";
                cin >> winningCount;
                while (winningCount > size) {
                    cout << "winning count can't be larger than board size!"<< endl;
                    cout << "Insert winning count: ";
                    cin >> winningCount;
                }
                while (winningCount < 3) {
                    cout << "Winning count can't be too small!" << endl;
                    cout << "Insert winning count: ";
                    cin >> winningCount;
                }
                break;
            }
            case '3': {
                cout << "1 - easy" << endl;
                cout << "2 - medium" << endl;
                cout << "3 - hard" << endl;
                cout << "Choose difficulty: ";
                cin >> choice;
                if (choice == '1') { difficulty = easy; depth = 1; }
                else if (choice == '2') { difficulty = medium; depth = 5; }
                else if (choice == '3') { difficulty = hard; depth = 9; }
                else {cout << "Wrong choice. Try again..." << endl;}
                break;
            }
            case '4': {
                Game *ticTacToe = new Game(size, winningCount, depth);
                ticTacToe->game();
                cout << "\nPress any key and enter to return to the menu.";
                cin >> unuseable;
                delete ticTacToe;
                break;
            }
            case '0': {
                cout << "               See ya!" << endl;
                cout << "--------------------------------------" << endl;
                return 0;
                break;
            }
            default: {
                cout << "Wrong choice. Try again..." << endl;
                break;
            }
        }
    }

    return 0;
}