#include "Screen.hpp"

Screen::Screen(int r, int c){ //Paramaterized constructor
    row = r;
    col = c;
    buildScreen(row,col,screenMap,freePool,freePoolSize);
}


void Screen::setMunchyValue(int row, int col, int NewMunchyValue){ //sets munchy value
        screenMap.at(row).at(col).munchyValue = NewMunchyValue;
}


void Screen::setNewMapCell(Cell takeCell,Cell setCell){ //replace a cell
    screenMap.at(takeCell.row).at(takeCell.col) = setCell;
}


void Screen::buildScreen(int mapRow, int mapCol, std::vector<std::vector<Cell> > &screenMap, std::vector<Cell> &freePool,int &freePoolSize){
    //Builds the screen, freepool, and fills both with Cells
    int x = 0;
    for (int i = 0; i < mapRow; i++) {
        std::vector<Cell> cellVec;
        screenMap.push_back(cellVec);
        for (int j = 0; j < mapCol; j++) {
            Cell c;
            c.row = i;
            c.col = j;
            if(i == 0 || i == mapRow-1){// top and bottom border
                c.freeIndex = -1;
                c.munchyValue = -1;
            }
            else if(j == 0 || j == mapCol-1){ // left and right border
                c.freeIndex = -1;
                c.munchyValue = -1;
            }
            else {
                c.freeIndex = x;
                c.munchyValue = 0;
                freePool.push_back(c);
                x++;
            }
            screenMap.at(i).push_back(c);
        }
    }

     freePoolSize = freePool.size();
}


void Screen::setMapFI(int row, int col,int value){//set the FreeIndex of a cell
    screenMap.at(row).at(col).freeIndex = value;
}


void Screen::printMap(){ //Debug print
    for (int i = 0; i < screenMap.size(); i++){
        for (int j = 0; j < screenMap.at(i).size(); j++){
            std::cout << screenMap.at(i).at(j).freeIndex << " "; 
        }
        std::cout << std::endl;
    }
}