#include "functions.h"


using namespace std;

int boardGame[4][4]; // the board
// The direction for down is 0, for right is 1, for up is 2 and for left is 3. If you want to move
//in one of those directions you need to switch the line or the column.  For example, if I want to
// go down, I need to increment the line by 1(switchLine[0]), and so on..
int oldboardGame[4][4]; // one step back board, in case of UNDO
int switchLine[] = {1, 0, -1, 0};
int switchColumn[] = {0, 1, 0, -1};

// Initializing the board.
void newGame(){

    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            boardGame[i][j] = 0;
    pair<int, int> rPos = generateFreePosition();
    boardGame[rPos.first][rPos.second] = 2; // place a random piece on a free spot on table.
}

//printing the board
void printBoard(){
    system("cls");
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < 4; j++)
            if(boardGame[i][j] == 0)
                std :: cout<<setw(6)<<"O";
            else
                cout<<setw(6)<<boardGame[i][j];
        cout<<endl;
    }
}
// Generate a random free position on the board
pair<int, int> generateFreePosition(){
    int notFree = 1, line, col;

    while(notFree){
        line = rand() % 4;
        col = rand() % 4;
        if(boardGame[line][col] == 0)
            notFree = 0;
    }
    return make_pair(line,col);
}
//Checking if the player can make the move or not.
bool checkMove(int currentLine, int currentCol, int nextLine, int nextCol){

    if(nextLine < 0 || nextCol < 0 || nextLine >=4 || nextCol >= 4 ||
        ((boardGame[currentLine][currentCol] != boardGame[nextLine][nextCol])
        && boardGame[nextLine][nextCol] != 0))
            return false;
    return true;
}

// Calculate score
int getScore(){
    int sum = 0;
        for(int i = 0; i < 4; i++)
            for(int j = 0; j < 4; j++)
                sum += boardGame[i][j];
    return sum;
}
// Checking if there are no more available moves
bool moveForGameOver(){
    for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            if(boardGame[i][j] == 0)
                return false;

    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            if(boardGame[i][j] == boardGame[i][j+1] || boardGame[i][j] == boardGame[i+1][j] || boardGame[i][j] == 0)
                return false;
    return true;
}
// Generate a new random number on the board.
void newNumber(){
    pair<int, int> rPos = generateFreePosition();
    boardGame[rPos.first][rPos.second] = 2;
}

bool checkWin(){

      for(int i = 0; i < 4; i++)
        for(int j = 0; j < 4; j++)
            if(boardGame[i][j] == 2048)
                return true;
        return false;
}

void undoMove(){

    for(int ii = 0; ii < 4; ii++)
        for(int jj = 0; jj < 4; jj++)
            boardGame[ii][jj] = oldboardGame[ii][jj];
}

// Moving the pieces and add them up together on the board.
void makeMove(int direction, int &GameOver, int &score){
    int initialLine = 0, initialCol = 0, lineDir = 1, colDir = 1; // pieces are going up or left

    //Check if player wants to move the piece down
    if(direction == 0){
        initialLine = 3;
        lineDir = -1;
    }
    //Check if the player wants to move the piece right
    if(direction == 1) {
        initialCol = 3;
        colDir = -1;
    }
    int movePossible = 0, addPiecePossible = 0;

    do{
        movePossible = 0;

        for(int i = initialLine; i < 4 && i >= 0; i += lineDir)
            for(int j = initialCol; j < 4 && j >= 0; j += colDir)
            {
                int nextLine = i + switchLine[direction];
                int nextCol = j + switchColumn[direction];
                if(checkMove(i, j, nextLine, nextCol) && boardGame[i][j]){
                    for(int ii = 0; ii < 4; ii++)
                        for(int jj = 0; jj < 4; jj++)
                            oldboardGame[ii][jj] = boardGame[ii][jj];
                    boardGame[nextLine][nextCol] += boardGame[i][j];
                    score = getScore();
                    boardGame[i][j] = 0;
                    movePossible = addPiecePossible = 1;
                }
            }
    }while(movePossible);
    if(addPiecePossible)
        newNumber();
    if(addPiecePossible == 0 && moveForGameOver())
        GameOver = 1;
}

