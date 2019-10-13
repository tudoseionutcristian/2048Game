#include <iostream>
#include <iomanip>
#include <conio.h>
#include <ctime>
#include <stdlib.h>

void newGame();
void printBoard();
std :: pair<int, int> generateFreePosition();
void makeMove(int, int &, int &);
bool checkMove(int,int,int,int);
void newNumber();
bool moveForGameOver();
int getScore();
bool checkWin();
void undoMove();
