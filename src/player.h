#ifndef LIB_PLAYER_H
#define LIB_PLAYER_H

#include <ncurses.h>

typedef struct _Player{
	WINDOW* win;
	WINDOW* msgbox;
	int score;
	int y;
	int x;
	int max_y;
	int max_x;
	char glyph;
	unsigned int alive;
} Player;

Player new_player(WINDOW* win, WINDOW* msgbox, int y, int x, char glyph);

int take_gold(WINDOW* msg_win, int* score);

void kill_player(Player* p);

int get_player_action(Player* p);

void draw_player(Player p);

void move_up(Player* p);

void move_down(Player* p);

void move_left(Player* p);

void move_right(Player* p);
#endif
