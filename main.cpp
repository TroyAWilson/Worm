#include<curses.h>
#include<iostream>
#include "getChar.hpp"
#include <stdlib.h>
#include <string>
#include "vector"
#include <ctime>

//My classes
#include "Screen.hpp"
#include "Cell.hpp"
#include "Worm.hpp"

void startup( void );
void terminate( void );


int main(int argc, char *argv[])
{    //random seed for munchy values
     srand(time(0));
     
     //variable declarations
     int mapRow;
     int mapCol;
     bool rightSize = false;

     //check if arguments are valid
     if(argc > 1){
          mapRow = atoi(argv[1]);
          mapCol = atoi(argv[2]);

          if((mapRow < 9 || mapRow > 25) || (mapCol < 9 || mapCol > 80)){
               rightSize = false;
          }else{
               rightSize = true;
          }
     }

     /* INITIALIZATIONS */
     //Initialize game screen
     Screen screen(mapRow,mapCol);
     
     //Find start cell
     Cell startCell = screen.getCellFromMap((mapRow)/2,(mapCol)/2);

     //Initialize worm
     Worm worm(startCell,(mapRow*mapCol)); //change this back to startCell
     worm.freePoolTake(startCell,screen);


     startup();
     //Draw screen
     move(0, 1);  // move the curser to the top- and left-most block.
     addstr("Worm");
     if (mapCol > 20){
          move(0,mapCol - 9);
          addstr("Score: ");
     }
     else{ //If the map is too small write score to static location
         move(0,20);
          addstr("Score: "); 
     }
     
  
     for(int i = 0; i < mapCol; i++){
     	mvaddch(1, i,'*'); // Top barrier
     }
 
     for(int i = 1; i < mapRow; i++){
     	mvaddch(i,0,'*'); //Left barrier
     }
     
     
     for(int i = 0; i < mapCol; i++){
     	mvaddch(mapRow,i,'*'); // Bottom barrier
     }
     
 	
     for(int i = 1; i < mapRow; i++){
     	mvaddch(i,mapCol-1,'*'); // Right barrier
     }    

     //Places head at center
     mvaddch(worm.getHead().row+1, worm.getHead().col,'@');

     //Initialize Munchy
     int munchyValue = rand() % 9 + 1;
     int whereTheSnack = rand() % screen.getFreePoolSize();
     
     Cell justASnack = screen.freePool.at(whereTheSnack);
     screen.setMunchyValue(justASnack.row,justASnack.col,munchyValue);
     std::string snackString = std::to_string(munchyValue);
     mvaddch( justASnack.row +1, justASnack.col, snackString[0]);
     
     int wrmSize = worm.getWormSize();

     /* PRIMARY GAMEPLAY LOOP */
     while(!worm.getGameEnd() && rightSize){

          char input = getChar(); // get inpuut

          //Munchy check logic
          if(worm.getWormSize() > wrmSize){ //replaces munchy after being picked up
               int munchyValue = rand() % 9 + 1;
               int whereTheSnack = rand() % screen.getFreePoolSize();
               Cell justASnack = screen.freePool.at(whereTheSnack);
               screen.setMunchyValue(justASnack.row,justASnack.col,munchyValue);

               std::string whereSnackString = std::to_string(whereTheSnack);

               std::string snackString = std::to_string(munchyValue);
               mvaddch( justASnack.row+1, justASnack.col, snackString[0]);

          }

          wrmSize = worm.getWormSize();


          //Draw score value
          std::string wormScore = std::to_string(worm.getWormSize());
          if(mapCol > 20)
               mvaddstr(0,mapCol-3 ,&wormScore[0]);
          else mvaddstr(0,26 ,&wormScore[0]);//if map is too small write score to static location


          switch(input){
               
               //Alternative controls

               case 'w':
                    worm.OmniMove(input,screen);
                    break;
               case 'a':
                    worm.OmniMove(input,screen);
                    break;
               case 's':
                    worm.OmniMove(input,screen);
                    break;
               case 'd':
                    worm.OmniMove(input,screen);
                    break;

               
               //Required controls
               
               case 'k':
                    worm.OmniMove(input,screen);
                    break;
               case 'h':
                    worm.OmniMove(input,screen);
                    break;
               case 'j':
                    worm.OmniMove(input,screen);
                    break;
               case 'l':
                    worm.OmniMove(input,screen);
                    break;
          }

	  refresh();
     }	  
     terminate();

     //Error message for incorrect dimensions
     if(!rightSize){
          std::cout << "dimensions provided are unsupported\n";
     }

     if(worm.getGameEnd()){
          std::cout << "The worm died since it ran into something!\n";
          std::cout << "Your final score was: " << worm.getWormSize() << std::endl;
     }
}

void startup( void )
{
     initscr();	 /* activate the curses */
     curs_set(0);/* do not display the cursor */
     clear();	 /* clear the screen that curses provides */
     noecho();	 /* prevent the input chars to be echoed to the screen */
     cbreak();	 /* change the stty so that characters are delivered to the
		    program as they are typed--no need to hit the return key!*/
}

void terminate( void )
{
     mvcur( 0, COLS - 1, LINES - 1, 0 );
     clear();
     refresh();
     endwin();
}
