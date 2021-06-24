#include "rogue.h"

Room* createRoom(int y, int x, int height, int width)
{
	Room* newRoom;
	newRoom = malloc(sizeof(Room));
	Position* center;
	center = malloc(sizeof(Position));
	center->x = x + (int)(width / 2);
	center->y = y + (int)(height / 2);

	newRoom->position.y = y;
	newRoom->position.x = x;
	newRoom->height = height;
	newRoom->width = width;
	newRoom->center = center;

	return newRoom;
}

void drawRoom(Room* room, Tile** level)
{
	int y;
	int x;
	
	for (y = room->position.y + 1; y < room->position.y + room->height - 1; y++)
	{
		for (x = room->position.x + 1; x < room->position.x + room->width - 1; x++)
		{
			if (isInMap(y, x))
			{
				level[y][x].ch = ".";
				level[y][x].walkable = true;
				level[y][x].transparent = true;
			}
		}
	}
}

void connectDoors(Position* doorOne, Position* doorTwo, Tile** level)
{
	Position temp;
	temp.x = doorOne->x;
	temp.y = doorOne->y;

	while (true)
	{
		if ((abs((temp.x - 1) - doorTwo->x) < abs(temp.x - doorTwo->x)))
		{
			temp.x--;

		} else if ((abs((temp.x + 1) - doorTwo->x) < abs(temp.x - doorTwo->x)))
		{
			temp.x++;

		} else if ((abs((temp.y + 1) - doorTwo->y) < abs(temp.y - doorTwo->y)))
		{
			temp.y++;

		} else if ((abs((temp.y - 1) - doorTwo->y) < abs(temp.y - doorTwo->y)))
		{
			temp.y--;
		} else
		{
			break;
		}
		if (isInMap(temp.y, temp.x))
		{
			level[temp.y][temp.x].ch = ".";
			level[temp.y][temp.x].walkable = true;
			level[temp.y][temp.x].transparent = true;
		}
	}
}
