all: ncurses

ncurses.o: ncurses.cpp player.h
	g++ -c ncurses.cpp
ncurses: ncurses.o
	g++ ncurses.o -o ncurses -lncurses

