#include <stdlib.h>
#include <ncurses.h>
#include "colors.h"

void spawn_gold(WINDOW* play_win){
	int max_y, max_x;
	getmaxyx(play_win, max_y, max_x);
	max_y -= 2;
	max_x -= 2;

	wattron(play_win, COLOR_GOLD);
	mvwprintw(
		play_win,
		rand() % max_y + 1,
		rand() % max_x + 1,
		"%c", '*'
	);
	wattroff(play_win, COLOR_GOLD);
}

int take_gold(WINDOW* msg_win, int* score){
	int amount = rand() % 126 + 25;
	wclear(msg_win);
	box(msg_win, 0, 0);
	wattron(msg_win, COLOR_GOLD);
	mvwprintw(msg_win, 1, 5, "you pick up %d gold coins", amount);
	wattroff(msg_win, COLOR_GOLD);
	*score += amount;
}
