#ifndef MENU_H
#define MENU_H


#include <iostream>
#include <string>
int aiDifficulty = 1;
int boardSize = 3;
std::string aiSetting(const int aiDifficulty){
    if (aiDifficulty == 1){
        return "(Easy)";
    }
    return "(Sophisticated)";
}
std::string boardSetting(const int boardSize){
    if (boardSize == 3){
        return "Game Size: 3x3";
    }
    return "Game Size: 4x4";
}

void displayMenu() {
    system("clear");
    std::cout << "Play Tic-Tac-Toe! \n" << std::endl;
    std::cout << std::endl;
    std::cout << boardSetting(boardSize) << std::endl;
    std::cout << std::endl;
    std::cout << "1. Play against another player" << std::endl;
    std::cout << "2. Play against AI " << aiSetting(aiDifficulty) << std::endl;
    std::cout << "3. Difficulty options" << std::endl;
    std::cout << "4. Exit \n" << std::endl;
    std::cout << "Select an option: ";
}

void optionsMenu(){
    system("clear");
    int select;
    std::cout << "Options: " << std::endl;
    std::cout << "1. Easy AI" << std::endl;
    std::cout << "2. Sophisticated AI" << std::endl;
    std::cout << "3. 3 x 3 Board" << std::endl;
    std::cout << "4. 4 x 4 Board \n" << std::endl;
    std::cout << "Select an option: " << std::endl;
    std::cin >> select;

    if(select == 1){
        aiDifficulty = 1;
    } else if (select == 2){
        aiDifficulty = 2;
    } else if (select == 3){
        boardSize = 3;
    } else if (select == 4){
        boardSize = 4;
    } else {
       std::cout << "Invalid option. Please enter a number from 1 to 4." << std::endl;
    }
}

#endif