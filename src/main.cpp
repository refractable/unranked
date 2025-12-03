#include <ncurses.h>

int main() {
    initscr();
    cbreak();
    noecho();
    keypad(stdscr, TRUE);

    mvprintw(0, 0, "UNRANKED");
    mvprintw(1, 0, "--------");
    mvprintw(2, 0, "A college basketball management sim.");
    mvprintw(4, 0, "Press any key to exit.");

    refresh();
    getch();

    endwin();

    return 0;
}
