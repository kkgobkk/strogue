#ifndef LIB_PLAYER_H
#define LIB_PLAYER_H

#include <ncurses.h>
#include "player.h"
#include "entities.h"
#include "colors.h"

typedef struct _Player{
	WINDOW* win;
	WINDOW* msgbox;
	int score;
	int y;
	int x;
	int max_y;
	int max_x;
	char glyph;
} Player;

Player new_player(WINDOW* win, WINDOW* msgbox, int y, int x, char glyph){
	Player p;
	p.win = win;
	p.msgbox = msgbox;
	p.score = 0;
	getmaxyx(p.win, p.max_y, p.max_x);
	p.max_y -= 2;
	p.max_x -= 2;
	p.y = y;
	p.x = x;
	p.glyph = glyph;

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
	int retv = wgetch(p->win);
	mvwaddch(p->win, p->y, p->x, ' ');
	refresh();
	switch(retv){
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

	if((char)mvwinch(p->win, p->y, p->x) == '*'){
		take_gold(p->msgbox, &(p->score));
	}

	return retv;
}

void draw_player(Player p){
	wattron(p.win, COLOR_PLAYER);
	mvwprintw(p.win, p.y, p.x, "%c", p.glyph);
	wattroff(p.win, COLOR_PLAYER);
}

#endif
