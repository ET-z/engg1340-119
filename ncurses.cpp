#include <ncurses.h>
#include <string>
#include <cstdlib>
#include "player.h"
#include <ctime>
using namespace std;

int main(int argc, char ** argv)
{
initscr();
cbreak();
// raw();
noecho();



int yMax, xMax;

//getyx(stdscr, y, x);
//getbegyx(stdscr, yBeg, xBeg);
getmaxyx(stdscr, yMax, xMax);

WINDOW * playwin = newwin(20, 50, (yMax/2)-10, 10);
box(playwin, 0, 0);
refresh();
wrefresh(playwin);

Player * p = new Player(playwin, 1, 1, '@');

do {
	p->display();
	wrefresh(playwin);

} while(p->getmv()!='x');


endwin();

return 0;

}
