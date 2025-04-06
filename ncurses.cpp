#include <ncurses.h>
#include <string>
#include <cstdlib>
#include "player.h"
#include <ctime>
using namespace std;

bool collision(WINDOW *win, int y, int x) {
    char ch = mvwinch(win, y, x) & A_CHARTEXT;
    return (ch == '#');
}

int main(int argc, char ** argv)
{
initscr();
cbreak();
// raw();
noecho();
curs_set(0);


int yMax, xMax;

//getyx(stdscr, y, x);
//getbegyx(stdscr, yBeg, xBeg);
getmaxyx(stdscr, yMax, xMax);

WINDOW * playwin = newwin(20, 50, (yMax/2)-10, 10);
box(playwin, 0, 0);
refresh();

mvwaddch(playwin, 10, 25, '#');
wrefresh(playwin);

// Set the window input to non-blocking so the game loop can run continuously
nodelay(playwin, true);


wrefresh(playwin);

Player * p = new Player(playwin, 1, 1, '@');

int gravityDelay = 200; // milliseconds between gravity updates
clock_t lastTime = clock();

int ch;
bool running = true;

while (running)
    {
        // Process input (if any)
        ch = wgetch(playwin);
        switch (ch) {
            case KEY_LEFT:
                // Check collision to the left before moving
                if (!collision(playwin, /*player's current y*/ p->getY(), /*player's current x*/ p->getX() - 1))
                    p->mvleft();
                break;
            case KEY_RIGHT:
                if (!collision(playwin, p->getY(), p->getX() + 1))
                    p->mvright();
                break;
            case KEY_UP:
                if (!collision(playwin, p->getY() - 1, p->getX()))
                    p->mvup();
                break;
            case KEY_DOWN:
                if (!collision(playwin, p->getY() + 1, p->getX()))
                    p->mvdown();
                break;
            case 'x':
                running = false;
                break;
            default:
                break;
        }

        // Apply gravity based on a timer
        clock_t currentTime = clock();
	mvwprintw(stdscr, 0, 0,"%s" ,to_string(((currentTime - lastTime) * 1000 / CLOCKS_PER_SEC)).c_str());
        wrefresh(stdscr);
	if (((currentTime - lastTime) * 800000 / CLOCKS_PER_SEC) > gravityDelay) {
            // Only apply gravity if the space below is free
            if (!collision(playwin, p->getY() + 1, p->getX()))
                p->mvdown();
            lastTime = currentTime;
        }

        // Clear and redraw the window
        werase(playwin);
        box(playwin, 0, 0);
        // Redraw the obstacle
        mvwaddch(playwin, 10, 25, '#');
        // Draw the player in its new position
        p->display();
        wrefresh(playwin);

        napms(50); // Small delay to control loop speed
    }





endwin();

return 0;

}
