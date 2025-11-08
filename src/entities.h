#ifndef LIB_ENTITIES_H
#define LIB_ENTITIES_H

#include <ncurses.h>

void spawn_gold();

int take_gold(WINDOW* msg_win, int* score);

#endif
