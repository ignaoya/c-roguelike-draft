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

bool roomIntersectsOther(Room* room, Room* other)
{
	int roomX1, roomX2, roomY1, roomY2;
	int otherX1, otherX2, otherY1, otherY2;
	
	roomX1 = room->position.x;
	roomX2 = room->position.x + room->width;
	roomY1 = room->position.y;
	roomY2 = room->position.y + room->height;

	otherX1 = other->position.x;
	otherX2 = other->position.x + other->width;
	otherY1 = other->position.y;
	otherY2 = other->position.y + other->height;

	return roomX1 <= otherX2 && roomX2 >= otherX1 && roomY1 <= otherY2 && roomY2 >= otherY1;
}
