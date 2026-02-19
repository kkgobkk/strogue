#include <stddef.h>
#include <stdlib.h>
#include <ncurses.h>

#include "console.h"
#include "dungen.h"
#include "entities.h"

#define NUM_ROOMS 5

typedef struct _Room{
	int y;
	int x;
	int height;
	int width;
} Room;

short** alloc_grid(size_t height, size_t width){
	short** grid = (short**)malloc(sizeof(short**) * height);
	for(size_t i = 0; i < height; i++){
		grid[i] = (short*)malloc(sizeof(short*) * width);
	}
	return grid;
}

void fill_grid(short** grid, size_t offset_y, size_t offset_x, size_t height, size_t width, short value){
	for(size_t y = 0; y < height; y++){
		for(size_t x = 0; x < width; x++){
			grid[offset_y + y][offset_x + x] = value;
		}
	}
}

void fill_line(short** grid, size_t y1, size_t x1, size_t y2, size_t x2, short value){
	size_t start, end;
	if(y1 == y2){
		if(x1 < x2){
			start = x1;
			end = x2;
		}else{
			start = x2;
			end = x1;
		}
		for(size_t x = start; x <= end; x++){
			grid[y1][x] = value;
		}
	}
	else if(x1 == x2){
		if(y1 < y2){
			start = y1;
			end = y2;
		}else{
			start = y2;
			end = y1;
		}
		for(size_t y = start; y <= end; y++){
			grid[y][x1] = value;
		}
	}
	else{
		return;
	}
}

void generate_rooms(Map* map, Room* room_list, size_t amount){
	//divide the grid into k subdivisions, where k is the smallest power of 2 that is greater than amount
	size_t subdivisions = 1, horizontal_subs = 1, vertical_subs = 1;
	size_t sub_height, sub_width;
	while(subdivisions < amount){
		subdivisions *= 2;
	}

	while(horizontal_subs * vertical_subs != subdivisions){
		if(horizontal_subs <= vertical_subs){
			horizontal_subs *= 2;
		}
		else{
			vertical_subs *= 2;
		}
	}
	
	sub_height = map->max_y / vertical_subs;
	sub_width = map->max_x / horizontal_subs;
	if(sub_width <= 8 || sub_height <= 8){
		return;
	}

	//generates one room for each subvision. if subdivions < amount, only amount rooms are generated, 
	//skipping random subdivisions
	size_t generated_rooms = 0, skipped_subs = 0;

	for(size_t i = 0; i < vertical_subs && generated_rooms < amount ; i++){
		for(size_t j = 0; j < horizontal_subs && generated_rooms < amount; j++){
			if(skipped_subs >= subdivisions - amount || rand() % subdivisions >= amount){
				Room r;
				r.height = rand() % (sub_height - 7) + 5;
				r.width = rand() %  (sub_width - 7) + 5;
				r.y = i * sub_height + rand() % (sub_height - r.height - 1) + 1;
				r.x = j * + sub_width + rand() % (sub_width - r.width - 1) + 1;
		
				fill_grid(map->grid, r.y, r.x, r.height, r.width, FLOOR);
				room_list[generated_rooms] = r;
				generated_rooms ++;
			}
			else{
				skipped_subs ++;
			}
		}
	}
}

void connect_rooms(Map* map, Room* room_list, size_t room_list_lenght){
	for(size_t i = 1; i < room_list_lenght; i++){
		//choose whether to connect vertically or horizontally first
		size_t y1 = room_list[i-1].y + rand() % room_list[i-1].height;
		size_t x1 = room_list[i-1].x + rand() % room_list[i-1].width;
		size_t y2 = room_list[i].y + rand() % room_list[i].height;
		size_t x2 = room_list[i].x + rand() % room_list[i].width;

		if(rand() % 2){
			fill_line(map->grid, y1, x1, y1, x2, FLOOR);
			fill_line(map->grid, y1, x2, y2, x2, FLOOR);
		}
		else{
			fill_line(map->grid, y1, x1, y2, x1, FLOOR);
			fill_line(map->grid, y2, x1, y2, x2, FLOOR);
		}
	}
}

void place_stairs(Map* map, Room* room_list, size_t room_list_lenght){
	size_t starting_room_index = rand() % room_list_lenght;
	size_t exit_room_index = rand() % room_list_lenght;
	while(exit_room_index == starting_room_index){
		exit_room_index = rand() % room_list_lenght;
	}
	Room starting_room = room_list[starting_room_index];
	Room exit_room = room_list[exit_room_index];

	map->entrance_y = starting_room.y + rand() % starting_room.height;
	map->entrance_x = starting_room.x + rand() % starting_room.width;

	map->exit_y = exit_room.y + rand() % exit_room.height;
	map->exit_x = exit_room.x + rand() % exit_room.width;

	map->grid[map->entrance_y][map->entrance_x] = UP_STAIRS;
	map->grid[map->exit_y][map->exit_x] = DOWN_STAIRS;
}

void generate_enemies(Room* room_list, size_t room_list_lenght, Entity* enemy_list, size_t* enemy_list_lenght){
	size_t num_enemies;
	Entity e;
	*enemy_list_lenght = 0;

	for(size_t i = 0; i < room_list_lenght; i++){
		num_enemies = rand()%3;
		for(size_t j = 0; j < num_enemies; j++){
			do{
				e.y = room_list[i].y + rand() % room_list[i].height;
				e.x = room_list[i].x + rand() % room_list[i].width;
			}while(num_enemies == 2 && enemy_list_lenght == 0 ? 1 : (e.y == enemy_list[*enemy_list_lenght-1].y && e.x == enemy_list[*enemy_list_lenght-1].x));
			
			enemy_list[*enemy_list_lenght] = e;
			(*enemy_list_lenght) ++;
		}
	}
}

void generate_gold(Room* room_list, size_t room_list_lenght, Entity* gold_arr, size_t* gold_arr_lenght){
	Entity g;
	for(size_t i = 0; i < room_list_lenght; i++){
		if(rand() % 2){
			g.y = room_list[i].y +  rand() % room_list[i].height;
			g.x = room_list[i].x + rand() % room_list[i].width;
			gold_arr[*gold_arr_lenght] = g;
			(*gold_arr_lenght) ++;
		}
	}
}

Map generate_map(size_t height, size_t width, Entity* enemy_arr, size_t* enemy_arr_lenght, Entity* gold_arr, size_t* gold_arr_lenght){
	Room* room_list = malloc(sizeof(Room) * NUM_ROOMS);
	Map map;
	map.depth = 1;
	map.grid = alloc_grid(height, width);
	fill_grid(map.grid, 0, 0, height, width, WALL);
	map.max_y = height;
	map.max_x = width;

	generate_rooms(&map, room_list, NUM_ROOMS);
	connect_rooms(&map, room_list, NUM_ROOMS);
	place_stairs(&map, room_list, NUM_ROOMS);
	generate_enemies(room_list, NUM_ROOMS, enemy_arr, enemy_arr_lenght);
	generate_gold(room_list, NUM_ROOMS, gold_arr, gold_arr_lenght);
	free(room_list);
	return map;
}

int all_neighbors_walls(Map map, size_t center_y , size_t center_x){
	int retv = 1;
	for(int y = -1; y <= 1 && retv; y++){
		for(int x = -1; x <= 1 && retv; x++){
			if(center_y + y >= 0 && center_y + y < map.max_y && center_x + x >= 0 && center_x + x < map.max_x){
				if(map.grid[center_y + y][center_x + x] != 1)
					retv = 0;
			}
		}
	}

	return retv;
}

void print_map(WINDOW* win, Map map){
	for(size_t y = 0; y < map.max_y; y++){
		for(size_t x = 0; x < map.max_x; x++){
			mvwaddch(win, y, x, map.grid[y][x]);
		}
	}
}
