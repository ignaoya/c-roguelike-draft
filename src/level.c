#include "rogue.h"

Room** mapSetUp(void)
{
	Room** rooms;
	rooms = malloc(sizeof(Room) * 6);

	rooms[0] = createRoom(13, 13, 6, 8);
	rooms[1] = createRoom(2, 40, 6, 8);
	rooms[2] = createRoom(10, 40, 6, 12);

	drawRoom(rooms[0]);
	drawRoom(rooms[1]);
	drawRoom(rooms[2]);

	connectDoors(rooms[0]->doors[3], rooms[2]->doors[1]);
	connectDoors(rooms[0]->doors[0], rooms[1]->doors[1]);
	connectDoors(rooms[2]->doors[0], rooms[1]->doors[2]);

	return rooms;
}


Tile** saveLevelTiles(void)
{
	int x, y;
	Tile** tiles;
	tiles = malloc(sizeof(Tile*) * 25);


	for (y = 0; y < 25; y++)
	{
		tiles[y] = malloc(sizeof(Tile) * 100);
		for (x = 0; x < 100; x++)
		{
			tiles[y][x].ch = mvinch(y, x);
			tiles[y][x].walkable = true;
			tiles[y][x].transparent = true;
		}
	}

	return tiles;
}
