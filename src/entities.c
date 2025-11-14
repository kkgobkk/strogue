#include <stdlib.h>
#include <ncurses.h>
#include "console.h"
#include "player.h"

typedef struct _Enemy{
	int y;
	int x;
} Enemy;

void spawn_gold(WINDOW* play_win){
	int max_y, max_x;
	getmaxyx(play_win, max_y, max_x);
	max_y -= 2;
	max_x -= 2;

	wattron(play_win, A_BOLD);
	wattron(play_win, COLOR_GOLD);
	mvwprintw(
		play_win,
		rand() % max_y + 1,
		rand() % max_x + 1,
		"%c", '*'
	);
	wattroff(play_win, A_BOLD);
	wattroff(play_win, COLOR_GOLD);
}

void spawn_enemy(WINDOW* play_win, Enemy* enemy_arr, size_t* enemy_number){
	int max_y, max_x;
	getmaxyx(play_win, max_y, max_x);
	max_y -= 2;
	max_x -= 2;
	
	Enemy new_enemy = {
		rand() % max_y + 1,
		rand() % max_x + 1,
	};

	enemy_arr[*enemy_number] = new_enemy;
	*enemy_number = *enemy_number + 1;
}

void update_enemy_position(Enemy* enemy_arr, size_t* enemy_number, Player* p){
	int distance_y, distance_x;
	size_t i = 0;
	while(i < *enemy_number){
		if(enemy_arr[i].y == p->y && enemy_arr[i].x == p->x){
			for(size_t j = i; j < *enemy_number-1; j++){
				enemy_arr[j] = enemy_arr[j+1];
			}

			(*enemy_number)--;

			if(i >= *enemy_number)
				break;
		}
		else{
			mvwaddch(p->win, enemy_arr[i].y, enemy_arr[i].x, ' ');
			distance_y = enemy_arr[i].y - p->y;
			distance_x = enemy_arr[i].x - p->x;

			if(distance_y < 0)
				enemy_arr[i].y ++;
			else if(distance_y > 0)
				enemy_arr[i].y --;

			if(distance_x < 0)
				enemy_arr[i].x ++;
			else if(distance_x > 0)
				enemy_arr[i].x --;

			if(enemy_arr[i].y == p->y && enemy_arr[i].x == p->x)
				kill_player(p);

			i++;
		}
	}
}

void draw_enemy(WINDOW* play_win, Enemy e){
	wattron(play_win, COLOR_ENEMY);
	mvwprintw(
		play_win,
		e.y,
		e.x,
		"%c", 'E'
	);
	wattroff(play_win, COLOR_ENEMY);
}
