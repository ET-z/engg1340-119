#include <iostream>
#include <ncursesw/ncurses.h> // wide-character support
#include <string>
#include <locale.h>
#include <unistd.h>

using namespace std;

// Typewriter animation
void typewriterPrint(WINDOW* win, const string& text, int delay_ms = 20) {
    for (char c : text) {
        waddch(win, c);
        wrefresh(win);
        napms(delay_ms);
    }
}

int main() {
    setlocale(LC_ALL, ""); // for emoji and UTF-8 support
    initscr();             // initialize ncurses
    set_escdelay(25);
    keypad(stdscr, TRUE);
    noecho();
    curs_set(0);

    // create a window to display the tutorial
    WINDOW* win = newwin(LINES, COLS, 0, 0);
    box(win, 0, 0);
    wrefresh(win);

    typewriterPrint(win, "🔫 Buckshot Roulette: Tutorial\n\n");
    typewriterPrint(win, "Welcome to Buckshot Roulette.\n");
    typewriterPrint(win, "A psychological shootout between you and the dealer.\n");
    typewriterPrint(win, "Your life depends on a chambered round.\n\n");

    typewriterPrint(win, "👥 You and the dealer take turns...\n");
    typewriterPrint(win, "🎲 Spin the cylinder, then pull the trigger.\n");
    typewriterPrint(win, "Each round could be a blank... or a live shot.\n\n");

    typewriterPrint(win, "🎯 Goal: Survive and outlast the dealer.\n");
    typewriterPrint(win, "Each shootout has 9 rounds. If one of you reaches 0 HP, game over.\n");

    typewriterPrint(win, "\n🚪 Press any key to begin...");
    wgetch(win); // wait for user input

    delwin(win);
    endwin(); // end ncurses mode

    return 0;
}
