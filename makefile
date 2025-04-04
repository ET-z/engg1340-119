all: ncurses

ncurses: ncurses.cpp
	g++ ncurses.cpp -o ncurses -lncurses

