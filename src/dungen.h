#ifndef LIB_DUNGEN_H
#define LIB_DUNGEN_H

#include <stddef.h>
#include <ncurses.h>

#include "entities.h"

#define NUM_ROOMS 5

typedef struct _Room Room;

typedef struct _Map{
	short** grid;
	size_t max_y;
	size_t max_x;
	size_t entrance_y;
	size_t entrance_x;
	size_t exit_y;
	size_t exit_x;
	size_t depth;
} Map;

short** alloc_grid(size_t height, size_t width);

void fill_grid(short** grid, size_t offset_y, size_t offset_x, size_t height, size_t width, short value);

void fill_line(short** grid, size_t y1, size_t x1, size_t y2, size_t x2, short value);

Map generate_map(size_t height, size_t width, Entity* enemy_list, size_t* enemy_list_lenght, Entity* gold_arr, size_t* gold_arr_lenght);

void print_map(WINDOW* win, Map map);

#endif
