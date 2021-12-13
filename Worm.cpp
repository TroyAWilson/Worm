#include "Worm.hpp"

Worm::Worm(Cell c, int size){ //Parameterized Contstructor
    head = tail = c;
    gameEnd = false;
    head.munchyValue = -1;
    tail.munchyValue = -1;
    wormSize = 0;
    headIndex = tailIndex = 0;
    maxSize = size;

    for(int i = 0; i < size; i++){ //Fill body with garbage to be overwritten later
        Cell emptyCell;
        emptyCell.freeIndex = -2;
        emptyCell.munchyValue = -2;
        emptyCell.row = -2;
        emptyCell.col = -2;
        body.push_back(emptyCell);
    }

     body.at(0) = head;
}

void Worm::sizeBoost(int n){ //increases max size of worm
    wormSize += n; 
}

void Worm::freePoolSwap(Cell &nextCell,Cell &tailCell,Screen &screen){//Swaps Cells
     //Local Variables
     int poolSize = screen.getFreePoolSize()-1;
     Cell lastFP = screen.freePool.at(poolSize);
     
     //change incoming value to -1 and outgoing value to 0
     nextCell.munchyValue = -1;
     tailCell.munchyValue = 0;

     //change position in freepoll
     screen.freePool.at(nextCell.freeIndex) = lastFP;
     screen.freePool.at(poolSize) = tailCell;
     
     //change FPindex
     screen.freePool.at(nextCell.freeIndex).freeIndex = lastFP.freeIndex;
     screen.freePool.at(poolSize).freeIndex = tailCell.freeIndex;

     //change freeindex as represented on the 2d array
     screen.setMapFI(lastFP.row,lastFP.col,nextCell.freeIndex);
}

void Worm::freePoolTake(Cell &nextCell, Screen &screen){//Takes from and reduces freepool
     //Local varibales
     int poolSize = screen.getFreePoolSize()-1;
     Cell lastFP = screen.freePool.at(poolSize);

     //change incoming value to -1
     nextCell.munchyValue = -1;

     //change position
     screen.freePool.at(nextCell.freeIndex) = lastFP;

     // change FPindex
     screen.freePool.at(nextCell.freeIndex).freeIndex = nextCell.freeIndex;
     
     //change freeindex as representedon the 2d array
     screen.setMapFI(lastFP.row,lastFP.col,nextCell.freeIndex); //<--important

     //reduce size of accessible freepool
     screen.reduceFreePool();

}


void Worm::headShiftCheck(){//Checks to see if head is at the end and makes vector circular
     if(headIndex == maxSize-1){
          headIndex = 0;
          body.at(headIndex) = head;
          head = body.at(headIndex);
     }
}

void Worm::tailShiftCheck(){// same as head but with tail
     if(tailIndex == maxSize-1){
          tailIndex = 0;
     }
}

bool Worm::gameEndCheck(Cell nextCell){//check for failure state
     if(nextCell.munchyValue == -1){
          this->gameEnd = true;//end game
          return true;
     }
     return false;
}

void Worm::munchyMove(Cell &nextCell, Screen &screen, int prevRow, int prevCol, int nextRow, int nextCol){
     //How the worm should move when reacting to picking up munchies

     if(wormGrow == 0){ //standard movement on first munchy move
          mvaddch(prevRow,prevCol,' ');
          
          freePoolSwap(nextCell,body.at(tailIndex),screen);

          head = nextCell;
          headIndex++;
          body.at(headIndex) = nextCell;
          tailIndex++;
          
          //set MV of cells not in the active worm to 0
          body.at(tailIndex-1).munchyValue = 0;
          
          mvaddch(nextRow,nextCol,'@');
          wormGrow++;
     }
     else{
          // take cell from freepool and reduce size
          freePoolTake(nextCell,screen);

          Cell oldHead = head;
          head = nextCell;
          headIndex++;
          body.at(headIndex) = nextCell;

          screen.setMunchyValue(oldHead.row,oldHead.col,-1);
          
          // draw o where head was
          mvaddch(oldHead.row + 1,oldHead.col,'o');
          // draw @ where head is
          mvaddch(nextRow,nextCol,'@');

          wormGrow++;
     }
}

void Worm::standardMove(Cell &nextCell, Screen &screen, int prevRow, int prevCol, int nextRow, int nextCol){
     //Basic movement when not interacting with munchies
     freePoolSwap(nextCell,body.at(tailIndex),screen); //Swamp out cells

     Cell oldHead = head;
     head = nextCell;
     headIndex++;
     body.at(headIndex) = nextCell;


     if(wormSize < 1){ //before the first munchy
          tailIndex = headIndex;

          //set MV of cells not in the active worm to 0
          body.at(tailIndex-1).munchyValue = 0;
          
          tail = head;
          mvaddch(prevRow,prevCol,' ');
          mvaddch(nextRow,nextCol,'@');
     }
     else{// after first munchy
          screen.setMunchyValue(oldHead.row,oldHead.col,-1);
          tail = body.at(tailIndex);
          screen.setMunchyValue(tail.row,tail.col,0);
          
          mvaddch(tail.row+1,tail.col,' ');
          mvaddch(oldHead.row + 1,oldHead.col,'o');
          mvaddch(nextRow,nextCol,'@');
          
          body.at(tailIndex).munchyValue = 0;
          tail.munchyValue = -1;
          tailIndex++;
     }
}


/***************************************

-----------------Omni Move--------------


**************************************/
void Worm::OmniMove(char c,Screen &screen){
     //dynamically reacts to and adjust for all 4 directions depending on the input
     
     //Initialize local variables 
     int row = head.row+1;
     int col = head.col;
     int nextColumn;
     int nextRow;
     Cell nextCell;

     switch(c){

          //Alternative controls
          case 'w': //up
               nextCell = screen.getCellFromMap(head.row-1,head.col);
               nextColumn = col;
               nextRow = row-1;
               break;
          case 'a': //left
               nextCell = screen.getCellFromMap(head.row,head.col-1);
               nextColumn = col-1;
               nextRow = row;
               break;
          case 's': //down
               nextCell = screen.getCellFromMap(head.row+1,head.col);
               nextColumn = col;
               nextRow = row+1;
               break;
          case 'd': //right
               nextCell = screen.getCellFromMap(head.row,head.col+1);
               nextColumn = col+1;
               nextRow = row;
               break;

          //Required controls

          case 'k': //up
               nextCell = screen.getCellFromMap(head.row-1,head.col);
               nextColumn = col;
               nextRow = row-1;
               break;
          case 'h': //left
               nextCell = screen.getCellFromMap(head.row,head.col-1);
               nextColumn = col-1;
               nextRow = row;
               break;
          case 'j': //down
               nextCell = screen.getCellFromMap(head.row+1,head.col);
               nextColumn = col;
               nextRow = row+1;
               break;
          case 'l': //right
               nextCell = screen.getCellFromMap(head.row,head.col+1);
               nextColumn = col+1;
               nextRow = row;
               break;
     }

     //Check if the player has reached a failure state
     if(gameEndCheck(nextCell)){
          return;
     }

     //Check if the circular queue needs to rotate
     headShiftCheck(); //rotate head
     tailShiftCheck(); //rotate tail

     //check if the next spot has a munchy in it 
     if(nextCell.munchyValue > 0){
          sizeBoost(nextCell.munchyValue); //if so grow
     }

     nextCell.munchyValue = -1; //set value to -1 as it enters the worm

     if(wormSize >= wormGrow && wormSize != 0){ //if worm is currently growing
          munchyMove(nextCell,screen,row,col,nextRow,nextColumn);
     }
     else{//if worm is not currently growing
          standardMove(nextCell,screen,row,col,nextRow,nextColumn);
     }
}