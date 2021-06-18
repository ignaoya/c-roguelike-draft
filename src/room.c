#include "rogue.h"

Room* createRoom(int y, int x, int height, int width)
{
	Room* newRoom;
	newRoom = malloc(sizeof(Room));

	newRoom->position.y = y;
	newRoom->position.x = x;
	newRoom->height = height;
	newRoom->width = width;

	newRoom->doors = malloc(sizeof(Position) * 4);


	/* top door */
	newRoom->doors[0] = malloc(sizeof(Position));
	newRoom->doors[0]->x = rand() % (width - 2) + newRoom->position.x + 1;
	newRoom->doors[0]->y = newRoom->position.y;

	/* bottom door */
	newRoom->doors[2] = malloc(sizeof(Position));
	newRoom->doors[2]->x = rand() % (width - 2) + newRoom->position.x + 1;
	newRoom->doors[2]->y = newRoom->position.y + height - 1;

	/* left door */
	newRoom->doors[1] = malloc(sizeof(Position));
	newRoom->doors[1]->x = newRoom->position.x;
	newRoom->doors[1]->y = rand() % (height - 2) + newRoom->position.y + 1;

	/* right door */
	newRoom->doors[3] = malloc(sizeof(Position));
	newRoom->doors[3]->x = newRoom->position.x + width - 1;
	newRoom->doors[3]->y = rand() % (height - 2)  + newRoom->position.y + 1;

	return newRoom;
}

void drawRoom(Room* room)
{
	int y;
	int x;

	// draw top and bottom
	for (x = room->position.x; x < room->position.x + room->width; x++)
	{
		mvprintw(room->position.y, x, "-"); // top
		mvprintw(room->position.y + room->height - 1, x, "-"); // bottom
	}
	
	// draw floors and side walls
	for (y = room->position.y + 1; y < room->position.y + room->height - 1; y++)
	{
		// draw side walls
		mvprintw(y, room->position.x, "|");
		mvprintw(y, room->position.x + room->width - 1, "|");

		// draw floors
		for (x = room->position.x + 1; x < room->position.x + room->width - 1; x++)
		{
			mvprintw(y, x, ".");
		}
	}

	/* draw doors */
	for (int i = 0; i < 4; i++)
	{
		mvprintw(room->doors[i]->y, room->doors[i]->x, "+");
	}
}

void connectDoors(Position* doorOne, Position* doorTwo)
{
	Position temp;
	Position previous;
	temp.x = doorOne->x;
	temp.y = doorOne->y;
	int count = 0;

	previous = temp;

	while (true)
	{
		if ((abs((temp.x - 1) - doorTwo->x) < abs(temp.x - doorTwo->x)) && (mvinch(temp.y, temp.x - 1) == ' '))
		{
			previous.x = temp.x;
			temp.x = temp.x - 1;

		} else if ((abs((temp.x + 1) - doorTwo->x) < abs(temp.x - doorTwo->x)) && (mvinch(temp.y, temp.x + 1) == ' '))
		{
			previous.x = temp.x;
			temp.x = temp.x + 1;

		} else if ((abs((temp.y + 1) - doorTwo->y) < abs(temp.y - doorTwo->y)) && (mvinch(temp.y + 1, temp.x) == ' '))
		{
			previous.y = temp.y;
			temp.y = temp.y + 1;

		} else if ((abs((temp.y - 1) - doorTwo->y) < abs(temp.y - doorTwo->y)) && (mvinch(temp.y - 1, temp.x) == ' '))
		{
			previous.y = temp.y;
			temp.y = temp.y - 1;
		} else
		{
			if (count == 0)
			{
				temp = previous;
				count++;
				continue;
			}
			else
			{
				break;
			}
		}
		mvprintw(temp.y, temp.x, "#");
	}
}