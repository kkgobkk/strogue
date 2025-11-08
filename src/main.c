#include <ncurses.h>
#include "player.h"
#include "entities.h"

#define PLAY_WIN_ROWS 30
#define PLAY_WIN_COLS 80

int main(void){
	//ncurses initialization and settings
	initscr();
	noecho();
	cbreak();
	start_color();
	curs_set(0);

	//windows setups and variable declarations (messy)
	int scr_y, scr_x, play_y, play_x;
	getmaxyx(stdscr, scr_y, scr_x);
	WINDOW* play_win = newwin(PLAY_WIN_ROWS, PLAY_WIN_COLS, scr_y/2 - PLAY_WIN_ROWS/2, scr_x/2 - PLAY_WIN_COLS/2);
	refresh();
	getmaxyx(play_win, play_y, play_x);
	keypad(play_win, true);
	Player p = new_player(play_win, play_y/2, play_x/2, '@', COLOR_GREEN);
	int score = 0;

	//game loop
		do{
		wclear(play_win);
		box(play_win, 0, 0);

		if(rand() % 10 == 0)
			spawn_gold(play_win);

		draw_player(p);
		wattron(play_win, A_STANDOUT);
		mvwprintw(play_win, 0, 1, "  score:%d  ", score);
		mvwprintw(play_win, 0, play_x - 20, "  x: %3d   y: %3d  ", p.x, p.y);
		wattroff(play_win, A_STANDOUT);
		refresh();
		wrefresh(play_win);
	}while(get_player_action(&p) != 'q');

	//release resources and exit
	endwin();
	return 0;
}
