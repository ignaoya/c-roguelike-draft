#include "rogue.h"

int MAX_ROOMS = 12;
int MIN_SIZE = 4;
int MAX_SIZE = 9;

Room** mapSetUp(void)
{
	int y, x, height, width;
	Room** rooms;
	rooms = malloc(sizeof(Room) * MAX_ROOMS);

	for (int i = 0; i < MAX_ROOMS; i++)
	{
		y = rand() % (GAMEMAP_HEIGHT - 5) + 2;
		x = rand() % (GAMEMAP_WIDTH - 15) + 2;
		height = rand() % MAX_SIZE + MIN_SIZE;
		width = rand() % MAX_SIZE + MIN_SIZE;

		rooms[i] = createRoom(y, x, height, width);
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
