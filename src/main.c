#include <stdlib.h>
#include <ncurses.h>
#include <time.h>

#include "console.h"
#include "dungen.h"
#include "entities.h"
#include "player.h"

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

	int turn = 0, score = 0;
	Entity enemy_arr[MAX_ENEMIES];
	size_t enemy_num = 0;
	Entity gold_arr[MAX_GOLD];
	size_t gold_num = 0;
	Map map = generate_map(play_y, play_x, enemy_arr, &enemy_num, gold_arr, &gold_num);
	Player p = new_player(play_win, message_box, map.entrance_y, map.entrance_x);
	unsigned int game_running = 1;

	//game loop
	do{
		wclear(play_win);
		if(p.alive){
			turn ++;
			print_map(play_win, map);

			//handle enemies
			update_enemy_position(enemy_arr, &enemy_num, &p, map.grid);
			for(size_t i = 0; i < enemy_num; i++){
				draw_entity(play_win, enemy_arr[i], COLOR_ENEMY, 'A'+i);
			}

			//handle gold
			for(size_t i = 0; i < gold_num; i++){
				//pick up the gold if it's collding with the player
				if(gold_arr[i].y == p.y && gold_arr[i].x == p.x){
					take_gold(message_box, &score);
					for(size_t j = i; j < gold_num-1; j++){
						gold_arr[j] = gold_arr[j+1];
					}
					gold_num --;
				}
				draw_entity(play_win, gold_arr[i], COLOR_GOLD, '1'+i);
			}

			draw_player(p);

			//display stats
			wattron(play_win, A_STANDOUT);
			mvwprintw(play_win, 0, 1, "  score:%d  turn:%d, depth:%ld", score, turn, map.depth);
			mvwprintw(play_win, 0, play_x - 20, "  x: %3d   y: %3d  ", p.x, p.y);
			wattroff(play_win, A_STANDOUT);
		}

		//handle game over
		if(!(p.alive)){
			wclear(play_win);
			box(play_win, 0, 0);
			mvwprintw(play_win, play_y/2 - 2, play_x/2 - 5, "GAME OVER!");
			mvwprintw(play_win, play_y/2, play_x/2 - 13, "Score:%6d, turn:%6d", score, turn);
			mvwprintw(play_win, play_y/2 + 2, play_x/2 - 11, "press any key to quit.");
			game_running = 0;
		}

		//refresh windows
		refresh();
		wrefresh(play_win);
		wrefresh(message_box);

		get_player_action(&p, map.grid);
	}while(game_running);

	//release resources and exit
	endwin();
	return 0;
}
