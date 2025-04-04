#include <ncurses.h>
#include <string>
#include <cmath>
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

WINDOW * menuwin = newwin(6, xMax-12, yMax-8, 5);
box(menuwin, 0, 0);
refresh();
wrefresh(menuwin);

keypad(menuwin, true);

string choices[3] = {"Walk", "Jog", "Run"};
int choice;
int highlight = 0;

while (1){
	for(int i = 0; i < 3; i++)
	{
	if(i == highlight)
		wattron(menuwin, A_REVERSE);
	mvwprintw(menuwin, i+1, 1, "%s" , choices[i].c_str());
	wattroff(menuwin, A_REVERSE);
	}
	choice = wgetch(menuwin);
	switch(choice)
	{
	case KEY_UP:
		highlight--;
		break;
	case KEY_DOWN:
		highlight++;
		break;
	default:
		break;
	}
	if(choice == 10)
		break;
	highlight = (int)fabs(highlight) % 3;
}

printw("Your choice was: %s", choices[highlight].c_str());
getch();

endwin();

return 0;

}
