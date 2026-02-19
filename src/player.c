#ifndef LIB_PLAYER_H
#define LIB_PLAYER_H

#include <ncurses.h>
#include <stdlib.h>
#include "player.h"
#include "console.h"

typedef struct _Player{
	WINDOW* win;
	WINDOW* msgbox;
	int y;
	int x;
	int max_y;
	int max_x;
	unsigned int alive;
} Player;

Player new_player(WINDOW* win, WINDOW* msgbox, int y, int x){
	Player p;
	p.win = win;
	p.msgbox = msgbox;
	getmaxyx(p.win, p.max_y, p.max_x);
	p.max_y -= 2;
	p.max_x -= 2;
	p.y = y;
	p.x = x;
	p.alive = 1;

	return p;
}

int take_gold(WINDOW* msg_win, int* score){
	int amount = rand() % 126 + 25;
	wclear(msg_win);
	box(msg_win, 0, 0);
	wattron(msg_win, A_BOLD);
	wattron(msg_win, COLOR_GOLD);
	mvwprintw(msg_win, 1, 5, "you pick up %d gold coins", amount);
	wattroff(msg_win, COLOR_GOLD);
	wattron(msg_win, A_BOLD);
	*score += amount;
}

void kill_player(Player *p){
	p->alive = 0;
}

int get_player_action(Player* p, short** map){
	int retv = wgetch(p->win);
	int old_y = p->y;
	int old_x = p->x;

	switch(retv){
		case VI_KEYS_N:
		case KEY_UP:
			p->y --;
			break;

		case VI_KEYS_NE:
			p->y --;
			p->x ++;
			break;

		case VI_KEYS_E:
		case KEY_RIGHT:
			p->x ++;
			break;

		case VI_KEYS_SE:
			p->y ++;
			p->x ++;
			break;

		case VI_KEYS_S:
		case KEY_DOWN:
			p->y ++;
			break;

		case VI_KEYS_SW:
			p->y ++;
			p->x --;
			break;

		case VI_KEYS_W:
		case KEY_LEFT:
			p->x --;
			break;

		case VI_KEYS_NW:
			p->y --;
			p->x --;
			break;

		case 'q':
			if(p->alive){
				kill_player(p);
			}
			break;
			
		default:
			break;
	}
	
	if(map[p->y][p->x] == WALL){
		p->y = old_y;
		p->x = old_x;
	}

	return retv;
}

void draw_player(Player p){
	wattron(p.win, COLOR_PLAYER);
	mvwprintw(p.win, p.y, p.x, "%c", '@');
	wattroff(p.win, COLOR_PLAYER);
}

#endif
