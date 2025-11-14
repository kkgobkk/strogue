#ifndef LIB_PLAYER_H
#define LIB_PLAYER_H

#include <ncurses.h>
#include <stdlib.h>
#include "player.h"
#include "console.h"

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
	p.alive = 1;

	return p;
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

void kill_player(Player *p){
	p->alive = 0;
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
		case VI_KEYS_N:
		case KEY_UP:
			move_up(p);
			break;

		case VI_KEYS_NE:
			move_up(p);
			move_right(p);
			break;
		
		case VI_KEYS_E:
		case KEY_RIGHT:
			move_right(p);
			break;

		case VI_KEYS_SE:
			move_down(p);
			move_right(p);
			break;

		case VI_KEYS_S:
		case KEY_DOWN:
			move_down(p);
			break;

		case VI_KEYS_SW:
			move_down(p);
			move_left(p);
			break;

		case VI_KEYS_W:
		case KEY_LEFT:
			move_left(p);
			break;

		case VI_KEYS_NW:
			move_up(p);
			move_left(p);
			break;

		case 'q':
			if(p->alive){
				kill_player(p);
			}
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
