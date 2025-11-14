#ifndef LIB_CONSOLE_H
#define LIB_CONSOLE_H

#include <ncurses.h>

//color pairs for output
#define COLOR_PLAYER COLOR_PAIR(1)
#define COLOR_GOLD COLOR_PAIR(2)
#define COLOR_ENEMY COLOR_PAIR(3)

//size of the play area
#define PLAY_WIN_ROWS 30
#define PLAY_WIN_COLS 80

//vi keys
#define VI_KEYS_N 'k'
#define VI_KEYS_NE 'u'
#define VI_KEYS_E 'l'
#define VI_KEYS_SE 'n'
#define VI_KEYS_S 'j'
#define VI_KEYS_SW 'b'
#define VI_KEYS_W 'h'
#define VI_KEYS_NW 'y'

//initializes the console, including color and basic ncurses settings
void init_console();

#endif
