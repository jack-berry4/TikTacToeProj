#ifndef GAMEPLAY_H
#define GAMEPLAY_H

#include <iostream>
#include "GameState.h"
#include "Graph.h"
#include "Menu.h"

Vec validMove(GameState game){
    for (int i = 0; i < game.size; i++){
        for (int j = 0; j < game.size; j++){
            if (game.grid[i][j] == -1){
                return Vec(i, j);
            }
        }
    }
    return Vec(0,0);

}

int getReward(Vertex<GameState>* start, int player){
    if (start->neighbors.size() == 0){
        int currPlayer = start->data.currentTurn;
        if (start->data.hasWon(player)){
            return 100;
        }
        else if (start->data.hasWon(!player)){
            return -100;
        }
        else{
            return 50;
        }
    }
    else{
        int reward = getReward(start->neighbors[0]->location, player);
        for (int i = 1; i < start->neighbors.size(); i++){
            int curr = getReward(start->neighbors[i]->location, player);
            if (start->data.currentTurn == player){
                if (curr > reward){
                    reward = curr;
                }
            }
            else{
                if (curr < reward){
                    reward = curr;
                }
            }
        }
        return reward;
    }
}

bool isTie(int** board, int size) {
    for(int i = 0; i < size; ++i){
        for(int j = 0; j < size; ++j){
            if(board[i][j] == -1){
                return false;

            }
        }
    }
    return true;
}

int countEmptyCells(int** grid, int size) {
    int emptyCount = 0;
    for (int i = 0; i < size; i++) {
        for (int j = 0; j < size; j++) {
            if (grid[i][j] == -1) {
                emptyCount++;
            }
        }
    }
    return emptyCount;
}

int minimax(GameState& game, int depth, bool isMax, int alpha, int beta) {
    if (game.hasWon(0)) {
        return -1000 + depth;
    }
    if (game.hasWon(1)) {
        return 1000 - depth;
    }
    if (isTie(game.grid, game.size)) {
        return 0;
    }

    if (game.size == 4 && game.turnCount <= 3) {
        int preferredMoves[4][2] = {{1, 1}, {2, 2}, {1, 2}, {2, 1}};
        for (auto& move : preferredMoves) {
            int i = move[0], j = move[1];
            if (game.grid[i][j] == -1) {
                game.grid[i][j] = isMax ? 1 : 0;
                int score = minimax(game, depth + 1, !isMax, alpha, beta);
                game.grid[i][j] = -1;
                if (isMax) {
                    alpha = std::max(alpha, score);
                    if (beta <= alpha) break;
                } else {
                    beta = std::min(beta, score);
                    if (beta <= alpha) break;
                }
            }
        }
        return isMax ? alpha : beta;
    }


    if (isMax) {
            int bestScore = -1000;
            for (int i = 0; i < game.size; i++) {
                for (int j = 0; j < game.size; j++) {
                    if (game.grid[i][j] == -1) {
                        game.grid[i][j] = 1;
                        int score = minimax(game, depth + 1, false, alpha, beta);
                        game.grid[i][j] = -1;
                        bestScore = std::max(score, bestScore);
                        alpha = std::max(alpha, bestScore);

                        if (beta <= alpha) {
                            return bestScore;
                        }
                    }
                }
            }
            return bestScore;
        } else {
            int bestScore = 1000;
            for (int i = 0; i < game.size; i++) {
                for (int j = 0; j < game.size; j++) {
                    if (game.grid[i][j] == -1) {
                        game.grid[i][j] = 0;
                        int score = minimax(game, depth + 1, true, alpha, beta);
                        game.grid[i][j] = -1;
                        bestScore = std::min(score, bestScore);
                        beta = std::min(beta, bestScore);

                        if (beta <= alpha) {
                            return bestScore; 
                        }
                    }
                }
            }
            return bestScore;
        }
}






Vec findBestMove(GameState game, bool isMax){
    int bestScore = isMax ? -1000 : 1000;
    Vec bestMove(-1, -1);
    int bestMaximizer = -1000;
    int bestMinimizer = 1000;

    for(int i = 0; i < game.size; i++){
        for(int j = 0; j < game.size; j++){
            if(game.grid[i][j] == -1){
                game.grid[i][j] = isMax ? 1 : 0;
                int score = minimax(game, 0, !isMax, bestMaximizer, bestMinimizer);
                game.grid[i][j] = -1;
                if((isMax && score > bestScore) ||(!isMax && score < bestScore)){
                    bestScore = score;
                    bestMove.set(i , j);
                }
                if(isMax){
                    bestMaximizer = std::max(bestMaximizer, bestScore);
                } else {
                    bestMinimizer = std::min(bestMinimizer, bestScore);
                }
            }
        }
    }
    return bestMove;
}

void players(){
    GameState game(boardSize);

    while(!game.done){
        system("clear");
        std::cout << game << std::endl;
        std::cout << std::endl;
        std::cout << "Enter move for (" << (!game.currentTurn ? "X" : "O") << "): ";
        int x, y;
        std::cin >> x >> y;

        game.play(x, y);
    }
    system("clear");
    std::cout << game << std::endl;
    std::cout << std::endl;
    if (game.hasWon(0)){
        std::cin.ignore();
        std::cout << "Player X has won!" << std::endl;
        std::cout << "Press enter to continue";
        std::cin.get();
    }
    else if (game.hasWon(1)){
        std::cin.ignore();
        std::cout << "Player O has won!" << std::endl;
        std::cout << "Press enter to continue";
        std::cin.get();
    }
    else {
        std::cin.ignore();
        std::cout << "It's a tie!" << std::endl;
        std::cout << "Press enter to continue";
        std::cin.get();
    }
    
}

void playEasyAI(){
    GameState game(boardSize);

    while(!game.done){
        system("clear");
        std::cout << game << std::endl;

        int x, y;

        if (game.currentTurn){
            Vec move = validMove(game);
            x = move.x;
            y = move.y;
        }
        else{
            std::cout << std::endl;
            std::cout << "Enter move for (" << (!game.currentTurn ? "X" : "O") << "): ";
            std::cin >> x >> y;
        }

        game.play(x, y);
    }

    system("clear");
    std::cout << game << std::endl;
    std::cout << std::endl;
    if (game.hasWon(0)){
        std::cin.ignore();
        std::cout << "Player X has won!" << std::endl;
        std::cout << "Press enter to continue";
        std::cin.get();
    }
    else if (game.hasWon(1)){
        std::cin.ignore();
        std::cout << "Player O has won!" << std::endl;
        std::cout << "Press enter to continue";
        std::cin.get();
    }
    else {
        std::cin.ignore();
        std::cout << "It's a tie!" << std::endl;
        std::cout << "Press enter to continue";
        std::cin.get();
    }

}

void playHardAI(bool isMax){
    GameState game(boardSize);
    std::cout << "Playing against Hard AI: " << std::endl;
    while(!game.done){
        system("clear");
        std::cout << game << std::endl;

        if(game.currentTurn == isMax){
            Vec move = findBestMove(game, isMax);
            std::cout << "Hard AI choosing move: " << move << std::endl;
            game.play(move.x,move.y);
        } else {
            std::cout << "Enter move for " << (game.currentTurn ? "O" : "X") << ": ";
            int x, y;
            std::cin >> x >> y;
            game.play(x,y);
        }
        if (game.hasWon(0)){
            std::cin.ignore();
            std::cout << "Player X has won!" << std::endl;
            std::cout << "Press enter to continue";
            std::cin.get();
            break;
        
        } else if(game.hasWon(1)){
            std::cin.ignore();
            std::cout << "Player O has won!" << std::endl;
            std::cout << "Press enter to continue";
            std::cin.get();
            
        } else if (game.done){
            std::cin.ignore();
            std::cout << "It's a tie!" << std::endl;
            std::cout << "Press enter to continue";
            std::cin.get();
            break;
        }
    }
    
}


#endif