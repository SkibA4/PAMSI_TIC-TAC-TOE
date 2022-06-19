#include "game.h"

// Metoda wypelniajaca tablice pustymi znakami
void Game::clearBoard() {
    for (int i = 0; i < this->size * this->size; i++) {
        this->tab[i] = ' ';
    }
}

// Metoda rysujaca tablice
void Game::drawBoard() {
    cout << endl;
    for (int i = 0; i < this->size; i++) {
        for (int j = 0; j < this->size; j++) {
            cout << " " << this->tab[i * this->size + j] << " ";
            if ((j + 1) % this->size) cout << "|";
            if (j + 1 == this->size && i + 1 != this->size) {
                cout << endl;
                for (int k = 0; k < this->size; k++) {
                    cout << "---";
                    if ((k + 1) % this->size) cout << "+";
                }
                cout << endl;
            }
        }
    }
    cout << endl;
    cout << endl;
}

// Metoda wyświetlająca numery pól na początku gry
void Game::showTileNumbers() {

    int size = this->size;
    int tileNumber = 1;

    cout << "\nTile numbers:\n\n";
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            cout << " ";
            if (tileNumber < 10) cout << "0";
            cout << tileNumber++ << " ";
            if ((j + 1) % size) cout << "|";
            if (j + 1 == size && i + 1 != size) {
                cout << endl;
                for (int k = 0; k < size; k++) {
                    cout << "----";
                    if ((k + 1) % size) cout << "+";
                }
                cout << endl;
            }
        }
    }
    cout << endl;
    cout << endl;
}

// Metoda sprawdzająca czy nie nastąpił remis
bool Game::draw() {

    int size = this->size;
    for (int i = 0; i < size * size; i++) {
        if (this->tab[i] == ' ') return false;
    }
    return true;
}

// Metoda sprawdzająca czy jest zwycięzca
bool Game::checkWinner(char player) {

    int counter = 0, size = this->size;

    // Sprawdzanie wierszy
    for (int i = 0; i < size; i++) {
        for (int j = 0; j <= size - this->winningCount; j++) {
            for (int k = 0; k < this->winningCount; k++) {
                if (this->tab[i * size + j + k] == player) counter++;
            }

            if (counter == this->winningCount) return true;
            counter = 0;
        }
    }

    // Sprawdzanie kolumn
    for (int i = 0; i < size; i++) {
        for (int j = 0; j <= size - this->winningCount; j++) {
            for (int k = 0; k < this->winningCount; k++) {
                if (this->tab[i + j * size + k * size] == player) counter++;
            }

            if (counter == this->winningCount) return true;
            counter = 0;
        }
    }

    // Sprawdzanie przekątnej od lewej strony
    for (int i = 0; i <= size - this->winningCount; i++) {
        for (int j = 0; j <= size - this->winningCount; j++) {
            for (int k = 0; k < this->winningCount; k++) {
                if (this->tab[i + j * size + k * (size + 1)] == player) counter++;
            }

            if (counter == this->winningCount) return true;
            counter = 0;
        }
    }

    // Sprawdzanie przekątnej od prawej strony
    for (int i = size - 1; i >= this->winningCount - 1; i--) {
        for (int j = 0; j <= size - this->winningCount; j++) {
            for (int k = 0; k < this->winningCount; k++) {
                if (this->tab[i + j * size + k * (size - 1)] == player) counter++;
            }

            if (counter == this->winningCount) return true;
            counter = 0;
        }
    }

    return false;
}

// Algorytm MiniMax z cięciami alfa-beta
int Game::minimax(int currentDepth, int maxDepth, bool maximum, int alpha, int beta) {

    if (checkWinner('O')) return this->depth - currentDepth;    // Zwraca jeżeli wygranym jest X
    if (checkWinner('X')) return currentDepth - this->depth;    // Zwraca jeżeli wygranym jest O
    if (draw() || maxDepth <= 0) return 0;      // Zwraca jeżeli nastąpił remis lub osiągnięto maksymalną głębokość wywołania rekurencyjnego

    // Maksymalizacja zysku dla komputera
    if (maximum) {
        int best = INT_MIN;
        for (int i = 0; i < this->size * this->size; i++) {
            if (this->tab[i] == ' ') {
                this->tab[i] = 'O';
                best = max(best, minimax(currentDepth + 1, maxDepth - 1, !maximum, alpha, beta));
                this->tab[i] = ' ';
                // Cięcia alfa-beta
                alpha = max(alpha, best);
                if (beta <= alpha) break;
            }
        }

        return best;

    // Minimalizacja zysku dla przeciwnika
    } else {
        int best = INT_MAX;
        for (int i = 0; i < this->size * this->size; i++) {
            if (this->tab[i] == ' ') {
                this->tab[i] = 'X';
                best = min(best, minimax(currentDepth + 1, maxDepth - 1, !maximum, alpha, beta));
                this->tab[i] = ' ';
                // Cięcia alfa-beta
                beta = min(beta, best);
                if (beta <= alpha) break;
            }
        }

        return best;        
    }
}

// Ruch komputera
int Game::aiMove() {

    // Deklaracja zmiennych 
    int maxDepth = this->depth, size = this->size;
    int bestMove = INT_MIN, currentMove = INT_MIN;
    int alpha = INT_MIN, beta = INT_MAX;
    int move;

    // Pętla wyszukuje wolne miejsca i dla każdego wywołuje algorytm MiniMax, po czym zwraca index najlepszego pola
    for (int i = 0; i < size * size; i++) {
        if (this->tab[i] == ' ') {
            this->tab[i] = 'O';
            currentMove = minimax(1, maxDepth - 1, false, alpha, beta); // Wywołanie MiniMax 
            tab[i] = ' ';
            if (currentMove > bestMove) {
                bestMove = currentMove;
                move = i;
            }
        }
    }

    return move;
}

// Metoda rozgrywki
void Game::game() {

    int move = 0, size = this->size;
    showTileNumbers();  // Pokazanie numerów pól i wyświetlenie pustej planszy na początku rozgrywki
    drawBoard();

    for (int i = 0; i < (size * size); i++) {
        // Kolej gracza
        if (i % 2 == 0) {
            cout << "--------------------------------------" << endl; 
            cout << "Player move: ";
            cin >> move;
             cout << "--------------------------------------" << endl; 

            // Sprawdzanie poprawności wykonania ruchu
            while (move < 1 || move > (size * size) || this->tab[move - 1] != ' ') {
                if (move < 1 || move > (size * size)) {
                    cout << "Wrong tile number! Try again: ";
                    cin >> move;
                } else if (this->tab[move - 1] != ' ') {
                    cout << "This file is occupied! Try again: ";
                    cin >> move;
                }
            }
            // Zapisanie ruchu do tablicy i rysowanie zaktualizowanej planszy
            this->tab[move - 1] = 'X';
            drawBoard();
            // Sprawdzanie czy gracz wygrał
            if (checkWinner('X')) {
                cout << "YOU WIN!" << endl;
                return;
            }
        // Tura komputera
        } else {
            // Wywołanie ruchu komputera
            move = aiMove();
            cout << "--------------------------------------" << endl;  
            cout << "AI move...: " << move + 1 << endl;
            cout << "--------------------------------------" << endl; 
            // Zapisanie ruchu komputera do tablicy i rysowanie zaktualizowanej planszy
            this->tab[move] = 'O';
            drawBoard();
            // Sprawdzanie czy komputer wygrał
            if (checkWinner('O')) {
                cout << "AI WINS!" << endl;
                return;
            }
        }
    }
    // Jeżeli plansza jest zapełniona i nie ma zwycięzcy, następuje remis
    cout << "DRAW!!!" << endl;
}