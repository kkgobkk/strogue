#include <ncurses.h>

void init_console(){
	initscr();
	noecho();
	cbreak();
	curs_set(0);

	if(has_colors()){
		start_color();

		init_pair(1, COLOR_GREEN, COLOR_BLACK);
		init_pair(2, COLOR_YELLOW, COLOR_BLACK);
		init_pair(3, COLOR_RED, COLOR_BLACK);
	}
}
