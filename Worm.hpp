#ifndef WORM_HPP
#define WORM_HPP

#include<curses.h>
#include<iostream>
#include "getChar.hpp"
#include <stdlib.h>
#include <string>
#include "vector"

//My classes
#include "Screen.hpp"
#include "Cell.hpp"

class Worm{
public:
    Worm(Cell c, int size); //paramaterized contructor

    /*Getters/Setters */
    bool getGameEnd(){return gameEnd;};
    int getWormSize(){return wormSize;};
    int getTailIndex(){return tailIndex;};
    int getHeadIndex(){return headIndex;};
    void setHead(Cell c){head = c;};
    void setTail(Cell c){tail = c;};
    Cell getHead(){return head;};
    Cell getTail(){return tail;};
    std::vector<Cell> getBody(){return body;};
    int getBodySize(){return body.size();};

    /*Movement related Methods*/
    void headShiftCheck();
    void tailShiftCheck();
    bool gameEndCheck(Cell nextCell);
    void munchyMove(Cell &nextCell, Screen &screen, int PrevRow, int prevCol, int nextCol, int nextRow);
    void standardMove(Cell &nextCell, Screen &screen, int PrevRow, int prevCol, int nextCol, int nextRow);
    void OmniMove(char c,Screen &screen);
    void freePoolSwap(Cell &nextCell,Cell &tailCell,Screen &screen);
    void freePoolTake(Cell &nextCell, Screen &screen);
    void sizeBoost(int n);
    
    //print for debug
    void print();

private:
    std::vector<Cell> body;
    Cell head;
    Cell tail;
    int difference;
    int headIndex;
    int tailIndex;
    int wormSize;
    int maxSize;
    int gameEnd;
    int wormGrow = 0;
    Cell emptyCell;
};


#endif