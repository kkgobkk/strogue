#include <stdlib.h>
#include <ncurses.h>
#include <time.h>
#include "player.h"
#include "entities.h"
#include "console.h"

int main(void){
	init_console();
	srand(time(NULL));

	//windows setups and variable declarations (messy)
	int scr_y, scr_x, play_y, play_x;
	getmaxyx(stdscr, scr_y, scr_x);
	WINDOW* play_win = newwin(PLAY_WIN_ROWS, PLAY_WIN_COLS, scr_y/2 - PLAY_WIN_ROWS/2, scr_x/2 - PLAY_WIN_COLS/2);
	WINDOW* message_box = newwin(3, PLAY_WIN_COLS, scr_y/2 + PLAY_WIN_ROWS/2 + 1, scr_x/2 - PLAY_WIN_COLS/2);
	refresh();
	getmaxyx(play_win, play_y, play_x);
	keypad(play_win, true);
	box(play_win, 0, 0);
	box(message_box, 0, 0);

	Player p = new_player(play_win, message_box, play_y/2, play_x/2, '@');
	int turn = 0;
	Enemy enemy_arr[MAX_ENEMIES];
	size_t enemy_num = 0;
	unsigned int game_running = 1;

	//game loop
	do{
		if(p.alive){
			turn ++;
			if(rand() % 5 == 0)
				spawn_gold(play_win);
			if(rand() % 10 == 0 && enemy_num < MAX_ENEMIES){
				spawn_enemy(play_win, enemy_arr, &enemy_num);
			}

			//handle enemies
			update_enemy_position(enemy_arr, &enemy_num, &p);
			for(size_t i = 0; i < enemy_num; i++){
				draw_enemy(play_win, enemy_arr[i]);
			}

			draw_player(p);

			//display stats
			wattron(play_win, A_STANDOUT);
			mvwprintw(play_win, 0, 1, "  score:%d  turn:%d", p.score, turn);
			mvwprintw(play_win, 0, play_x - 20, "  x: %3d   y: %3d  ", p.x, p.y);
			wattroff(play_win, A_STANDOUT);

		}
		
		//handle game over
		if(!(p.alive)){
			wclear(play_win);
			box(play_win, 0, 0);
			mvwprintw(play_win, play_y/2 - 2, play_x/2 - 5, "GAME OVER!");
			mvwprintw(play_win, play_y/2, play_x/2 - 13, "Score:%6d, turns:%6d", p.score, turn);
			mvwprintw(play_win, play_y/2 + 2, play_x/2 - 11, "press any key to quit.");
			game_running = 0;
		}

		//refresh windows
		refresh();
		wrefresh(play_win);
		wrefresh(message_box);
	
		get_player_action(&p);
	}while(game_running);

	//release resources and exit
	endwin();
	return 0;
}
