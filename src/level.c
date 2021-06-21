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


char** saveLevelPositions(void)
{
	int x, y;
	char** positions;
	positions = malloc(sizeof(char*) * 25);


	for (y = 0; y < 25; y++)
	{
		positions[y] = malloc(sizeof(char) * 100);
		for (x = 0; x < 100; x++)
		{
			positions[y][x] = mvinch(y, x);
		}
	}

	return positions;
}
