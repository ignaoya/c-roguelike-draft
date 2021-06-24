#include "rogue.h"

int MAX_ROOMS = 6;
int MIN_SIZE = 3;
int MAX_SIZE = 8;

Room** mapSetUp(Tile** level)
{
	int y, x, height, width;
	Room** rooms;
	rooms = malloc(sizeof(Room) * MAX_ROOMS);

	for (int i = 0; i < MAX_ROOMS; i++)
	{
		y = rand() % 15 + 2;
		x = rand() % 85 + 2;
		height = rand() % MAX_SIZE + MIN_SIZE;
		width = rand() % MAX_SIZE + MIN_SIZE;

		rooms[i] = createRoom(y, x, height, width);
		drawRoom(rooms[i], level);
		if (i > 0) 
		{
			connectDoors(rooms[i]->center, rooms[i-1]->center, level);
		}
	}
	return rooms;
}

void mapDraw(Tile** level)
{
	int x, y;
	for (y = 0; y < 25; y++)
	{
		for (x = 0; x < 100; x++)
		{
			if (level[y][x].visible)
			{
				mvprintw(y, x, level[y][x].ch);
			}
			else
			{
				mvprintw(y, x, " ");
			}
		}
	}
}


Tile** createLevelTiles(void)
{
	int x, y;
	Tile** tiles;
	tiles = malloc(sizeof(Tile*) * 25);

	for (y = 0; y < 25; y++)
	{
		tiles[y] = malloc(sizeof(Tile) * 100);
		for (x = 0; x < 100; x++)
		{
			tiles[y][x].ch = "#";
			tiles[y][x].walkable = false;
			tiles[y][x].transparent = false;
			tiles[y][x].visible = false;
		}
	}

	return tiles;
}
