#ifndef LIB_ENTITIES_H
#define LIB_ENTITIES_H

#include <ncurses.h>
#include "player.h"

#define MAX_ENEMIES 5

typedef struct _Enemy{
	int y;
	int x;
} Enemy;

void spawn_gold(WINDOW* play_win);

void spawn_enemy(WINDOW* play_win, Enemy* enemy_arr, size_t* enemy_number);

void update_enemy_position(Enemy* enemy_arr, size_t enemy_number, Player p);

void draw_enemy(WINDOW* play_win, Enemy e);

#endif
