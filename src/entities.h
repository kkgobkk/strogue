#ifndef LIB_ENTITIES_H
#define LIB_ENTITIES_H

#include <ncurses.h>
#include "player.h"

#define MAX_ENEMIES 20
#define MAX_GOLD 20

typedef struct _Entity{
	int y;
	int x;
} Entity;

void update_enemy_position(Entity* enemy_arr, size_t* enemy_number, Player* p, short** map);

void draw_entity(WINDOW* play_win, Entity e, unsigned int color, char c);

#endif
