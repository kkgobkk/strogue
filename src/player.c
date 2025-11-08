#ifndef LIB_PLAYER_H
#define LIB_PLAYER_H

#include <ncurses.h>
#include "player.h"

typedef struct _Player{
	WINDOW* win;
	int y;
	int x;
	int max_y;
	int max_x;
	char glyph;
} Player;

Player new_player(WINDOW* win, int y, int x, char glyph, int color){
	Player p;
	p.win = win;
	getmaxyx(p.win, p.max_y, p.max_x);
	p.max_y -= 2;
	p.max_x -= 2;
	p.y = y;
	p.x = x;
	p.glyph = glyph;
	init_pair(1, color, COLOR_BLACK);

	return p;
}


void move_up(Player* p){
	p->y --;
	if(p->y < 1)
		p->y = 1;
}

void move_down(Player* p){
	p->y ++;
	if(p->y > p->max_y)
		p->y = p->max_y;
}

void move_left(Player* p){
	p->x --;
	if(p->x < 1)
		p->x = 1;
}

void move_right(Player* p){
	p->x ++;
	if(p->x > p->max_x)
		p->x = p->max_x;
}

int get_player_action(Player* p){
	int retv;
	switch(retv = wgetch(p->win)){
		case KEY_UP:
			move_up(p);
			break;
		case KEY_DOWN:
			move_down(p);
			break;
		case KEY_LEFT:
			move_left(p);
			break;
		case KEY_RIGHT:
			move_right(p);
			break;
		default:
			break;
	}

	return retv;
}

void draw_player(Player p){
	wattron(p.win, COLOR_PAIR(1));
	mvwprintw(p.win, p.y, p.x, "%c", p.glyph);
	wattroff(p.win, COLOR_PAIR(1));
}

#endif
