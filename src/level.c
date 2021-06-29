#include "rogue.h"

int MIN_SIZE = 4;
int MAX_SIZE = 9;
int MAX_MONSTERS = 3;

Room** mapSetUp(void)
{
	int y, x, height, width, max_rooms, n_monsters;
	max_rooms = rand() % 15 + 5;
	Room** rooms;
	rooms = malloc(sizeof(Room) * max_rooms);

	for (int i = 0; i < max_rooms; i++)
	{
		y = rand() % (GAMEMAP_HEIGHT - 15) + 1;
		x = rand() % (GAMEMAP_WIDTH - 15) + 1;
		height = rand() % MAX_SIZE + MIN_SIZE;
		width = rand() % MAX_SIZE + MIN_SIZE;
		n_monsters = rand() % MAX_MONSTERS;

		rooms[i] = createRoom(y, x, height, width);
		for (int j = 0; j < n_monsters; j++)
		{
			if (n_actors >= 15 || i == 0)
			{
				break;
			}
			int monster_y = rand() % height + y;
			int monster_x = rand() % width + x;
			int monster_level = rand() % 3;
			actors[n_actors] = createMonster(monster_y, monster_x, goblin, monster_level);
			n_actors++;
		}

		drawRoom(rooms[i]);
		

		if (i > 0) 
		{
			connectRoomCenters(rooms[i]->center, rooms[i-1]->center);
		}
	}
	return rooms;
}

void mapDraw(void)
{
	int x, y;
	for (y = 0; y < GAMEMAP_HEIGHT; y++)
	{
		for (x = 0; x < GAMEMAP_WIDTH; x++)
		{
			if (level[y][x].visible)
			{
				mvaddch(y, x, level[y][x].ch[0] | COLOR_PAIR(VISIBLE_COLOR));
			}
			else if (level[y][x].seen)
			{
				mvaddch(y, x, level[y][x].ch[0] | COLOR_PAIR(SEEN_COLOR));
			}
			else
			{
				mvprintw(y, x, " ");
			}
		}
	}
}

void showWholeMap(void)
{
	int x, y;
	for (y = 0; y < GAMEMAP_HEIGHT; y++)
	{
		for (x = 0; x < GAMEMAP_WIDTH; x++)
		{
			mvprintw(y, x, level[y][x].ch);
		}
	}
}


Tile** createLevelTiles(void)
{
	int x, y;
	Tile** tiles;
	tiles = malloc(sizeof(Tile*) * GAMEMAP_HEIGHT);

	for (y = 0; y < GAMEMAP_HEIGHT; y++)
	{
		tiles[y] = malloc(sizeof(Tile) * GAMEMAP_WIDTH);
		for (x = 0; x < GAMEMAP_WIDTH; x++)
		{
			tiles[y][x].ch = "#";
			tiles[y][x].walkable = false;
			tiles[y][x].transparent = false;
			tiles[y][x].visible = false;
			tiles[y][x].seen = false;
		}
	}

	return tiles;
}
