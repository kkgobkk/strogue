#include <ncurses.h>

void spawn_gold(WINDOW* play_win){
	int max_y, max_x;
	getmaxyx(play_win, max_y, max_x);
	max_y -= 2;
	max_x -= 2;
	init_pair(2, COLOR_YELLOW, COLOR_BLACK);

	wattron(play_win, COLOR_PAIR(2));
	mvwprintw(
		play_win,
		rand() % max_y + 1,
		rand() % max_x + 1,
		"%c", '*'
	);
	wattroff(play_win, COLOR_PAIR(2));
}

int take_gold(WINDOW* msg_win, int* score){
	int amount = rand() % 126 + 25;
	mvwprintw(msg_win, 0, 0, "you pick up %d gold coins", amount);
	*score += amount;
}
