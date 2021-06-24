#include "rogue.h"

Room** mapSetUp(Tile** level)
{
	Room** rooms;
	rooms = malloc(sizeof(Room) * 6);

	rooms[0] = createRoom(13, 13, 6, 8);
	rooms[1] = createRoom(2, 40, 6, 8);
	rooms[2] = createRoom(10, 40, 6, 12);

	drawRoom(rooms[0], level);
	drawRoom(rooms[1], level);
	drawRoom(rooms[2], level);

	connectDoors(rooms[0]->center, rooms[1]->center, level);
	connectDoors(rooms[2]->center, rooms[1]->center, level);

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
