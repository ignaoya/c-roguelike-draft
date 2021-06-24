#include "rogue.h"

int main(void)
{
	srand(time(NULL));
	Player* player;
	int ch;
	Position* newPosition;
	Tile** level;
	Room** rooms;

	level = createLevelTiles();
	screenSetUp();
	rooms = mapSetUp(level);
	player = playerSetUp(rooms);
	playerMove(&(player->position), player, level);

	/* main game loop */
	while ((ch = getch()) != 'q')
	{
		newPosition = handleInput(ch, player);
		checkPosition(newPosition, player, level);
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
