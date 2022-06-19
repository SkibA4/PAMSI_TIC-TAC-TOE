#ifndef GAME_H
#define GAME_H
#include <iostream>
#include <cstdlib>
#include <algorithm>
#include <limits.h>

#define INF 100
#define N_INF -100

using namespace std;

class Game {
    
    int size;
    int winningCount;
    int depth;
    char* tab;

    public:

    // Konstruktor klasy Game
    Game(int size, int winningCount, int depth) {
        this->size = size;
        this->winningCount = winningCount;
        this->depth = depth;
        this->tab = new char[size * size];
        clearBoard();
    }

    // Destruktor klasy Game
    ~Game() {
        delete[] tab;
    }

    // Metody
    void clearBoard();
    void drawBoard();
    void showTileNumbers();
    bool draw();
    bool checkWinner(char player);
    int minimax(int currentDepth, int maxDepth, bool maximum, int alpha, int beta);
    int aiMove();
    void game();
};

#endif