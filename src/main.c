#include "rogue.h"

int main(void)
{
	srand(time(NULL));
	Player* user;
	int ch;
	Position* newPosition;
	char** level;
	screenSetUp();

	mapSetUp();

	level = saveLevelPositions();

	user = playerSetUp();

	/* main game loop */
	while ((ch = getch()) != 'q')
	{
		newPosition = handleInput(ch, user);
		checkPosition(newPosition, user, level);
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
