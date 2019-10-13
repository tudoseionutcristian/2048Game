#include "functions.h"


int main()
{
    char keyPressed;
    //117
    bool startGame = false;
    if(!startGame){
        std::cout<< "2048, made by Tudose Ionut-Cristian"<<std::endl;
        std::cout<< "You can move the pieces left by pressing A on keyboard, right by pressing D, up by pressing W and down by pressing S.\nYou can also undo only one move by pressing U. "<<std::endl;
        std::cout<< "Press Y to start the game! Have fun!"<<std::endl;
        if(getch() == 121){
            startGame = true;
            newGame();
        }
    }
    int GameOver = 0;
    int score = 0;
    bool YouWin = true;
    while(startGame){

        printBoard();
        std::cout<<"Your score: "<<score<<std::endl;
        if(YouWin && checkWin()){
            std::cout<<"You won! Now try your best!";
            YouWin = 0;
        }
        std::cout<<std:: endl<<std ::endl;
        if(GameOver == 1){
            std::cout<<"Game Over!";
            break;
        }
        keyPressed = getch();
        if(keyPressed == 97){
            int direction = 3;
            makeMove(direction, GameOver, score);
            continue;
        }
        if(keyPressed == 100){
            int direction = 1;
            makeMove(direction,GameOver, score);
            continue;
        }
        if(keyPressed == 115){
            int direction = 0;
            makeMove(direction,GameOver, score);
            continue;
        }
        if(keyPressed == 119){
            int direction = 2;
            makeMove(direction,GameOver, score);
            continue;
        }
        if(keyPressed == 117){
            undoMove();
            continue;
        }


    }
    return 0;
}
