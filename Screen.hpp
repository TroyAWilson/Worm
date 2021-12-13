#ifndef SCREEN_HPP
#define SCREEN_HPP

#include "Cell.hpp"
#include<curses.h>
#include<iostream>
#include "getChar.hpp"
#include <stdlib.h>
#include <string>
#include "vector"

class Screen{
public:
    Screen(int r, int c);//Parameterized constructor

    void buildScreen(int row, int col, std::vector<std::vector<Cell> > &, std::vector<Cell> &, int &);
    
    /*Getters/Setters*/
    std::vector<std::vector<Cell> > getScreenMap(){return screenMap;};
    std::vector<Cell> getFreePool(){return freePool;};
    int getFreePoolSize(){return freePoolSize;};
    void setFreePoolSize(int x){freePoolSize = x;};
    Cell getCellFromMap(int row, int col){return screenMap.at(row).at(col);};
    void setMunchyValue(int row, int col, int NewMunchyValue);
    void setNewMapCell(Cell takeCell,Cell setCell);
    void setMapFI(int row, int col,int value);
    
    void reduceFreePool(){freePoolSize--;}
    
    //debug print
    void printMap();
    std::vector<Cell> freePool;
private:
    std::vector<std::vector<Cell> > screenMap;
    int freePoolSize;
    int row;
    int col;
};

#endif