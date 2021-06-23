#include "rogue.h"

int main(void)
{
	srand(time(NULL));
	Player* user;
	int ch;
	Position* newPosition;
	Tile** level;
	screenSetUp();

	mapSetUp();

	level = saveLevelTiles();

	user = playerSetUp();

	/* main game loop */
	while ((ch = getch()) != 'q')
	{
		newPosition = handleInput(ch, user);
		checkPosition(newPosition, user, level);
	}

	clear();
	move(20, 60);
	printw("Thank you for playing!");
	getch();
	endwin();

	return 0;
}

void screenSetUp(void)
{
	initscr();
	noecho();
	refresh();
}
