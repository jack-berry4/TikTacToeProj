#include <iostream>
#include "GameState.h"
#include "Graph.h"
#include "Menu.h"
#include "GamePlay.h"

using namespace std;

//Try 4x4 hard AI!! 
// On move 3 have a bit of patience.

int main(){
    system("clear");
    int option;
    displayMenu();
    cin >> option;
    cin.ignore();

    while(option != 4){
        if(option == 1){
            players();
        } else if (option == 2){
            if(aiDifficulty == 1){
                playEasyAI();
            } else if(aiDifficulty == 2){
                GameState game(boardSize);
                playHardAI(true);
            }
        } else if (option == 3){
            optionsMenu();
        }
        displayMenu();
        cin >> option;
        cin.ignore();
    }
    system("clear");
    cout << "Thanks for playing Tic-Tac-Toe!" << endl;
    
    return 0;
}