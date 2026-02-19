#include <stdlib.h>
#include <ncurses.h>
#include "console.h"
#include "player.h"

typedef struct _Entity{
	int y;
	int x;
} Entity;

void update_enemy_position(Entity* enemy_arr, size_t* enemy_number, Player* p, short** map){
	int old_y, old_x, distance_y, distance_x;
	size_t i = 0;
	while(i < *enemy_number){
		//kill enemy if it the player moved on top of it
		if(enemy_arr[i].y == p->y && enemy_arr[i].x == p->x){
			for(size_t j = i; j < *enemy_number-1; j++){
				enemy_arr[j] = enemy_arr[j+1];
			}

			(*enemy_number)--;

			if(i >= *enemy_number)
				break;
		}
		else{
			old_y = enemy_arr[i].y;
			old_x = enemy_arr[i].x;
			distance_y = enemy_arr[i].y - p->y;
			distance_x = enemy_arr[i].x - p->x;
			
			//move toward the player on the y axis
			if(distance_y < 0){
				enemy_arr[i].y ++;
			}
			else if(distance_y > 0){
				enemy_arr[i].y --;
			}

			//revert enemy position if they are colliding with a wall
			if(map[enemy_arr[i].y][enemy_arr[i].x] == WALL){
				enemy_arr[i].y = old_y;
			}

			//move toward the player on the x axis
			if(distance_x < 0){
				enemy_arr[i].x ++;
			}
			else if(distance_x > 0){
				enemy_arr[i].x --;
			}

			//revert enemy position if they are colliding with a wall
			if(map[enemy_arr[i].y][enemy_arr[i].x] == WALL){
				enemy_arr[i].x = old_x;
			}

			//kill player if the enemy moved on top of them
			if(enemy_arr[i].y == p->y && enemy_arr[i].x == p->x)
				kill_player(p);

			i++;
		}
	}
}

void draw_entity(WINDOW* play_win, Entity e, unsigned int color, char c){
	wattron(play_win, A_BOLD);
	wattron(play_win, color);
	mvwprintw(play_win, e.y, e.x, "%c", c);
	wattroff(play_win, color);
	wattroff(play_win, A_BOLD);
}
