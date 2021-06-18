#include "rogue.h"

int main(void)
{
	srand(time(NULL));
	Player* user;
	int ch;
	screenSetUp();

	mapSetUp();

	user = playerSetUp();

	/* main game loop */
	while ((ch = getch()) != 'q')
	{
		handleInput(ch, user);
	}

	endwin();

	return 0;
}

void screenSetUp(void)
{
	initscr();
	printw("Hello world!");
	noecho();
	refresh();
}

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



	


