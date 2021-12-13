
game.x:  main.o getChar.o Cell.o Screen.o Worm.o
	g++ -ggdb -o game.x main.o getChar.o Cell.o Screen.o Worm.o -lcurses -ltermcap

main.o: main.cpp Cell.hpp Screen.hpp Worm.hpp
	g++ -c -ggdb main.cpp -o main.o

getChar.o: getChar.cpp 
	gcc -c -ggdb getChar.cpp -o getChar.o

Cell.o: Cell.cpp Cell.hpp
	gcc -c -ggdb Cell.cpp -o Cell.o

Screen.o: Screen.cpp Screen.hpp
	gcc -c -ggdb Screen.cpp -o Screen.o

Worm.o: Worm.cpp Worm.hpp
	gcc -c -ggdb Worm.cpp -o Worm.o

clean:
	/bin/rm -f game.x main.o getChar.o Cell.o Screen.o Worm.o *~
