#include "rogue.h"

const int GAMEMAP_HEIGHT = 35;
const int GAMEMAP_WIDTH = 120;
Tile** level;

int main(void)
{
	srand(time(NULL));
	Player* player;
	int ch;
	Position* newPosition;
	Room** rooms;

	level = createLevelTiles();
	screenSetUp();
	rooms = mapSetUp();
	player = playerSetUp(rooms[0]);
	playerMove(&(player->position), player);

	/* main game loop */
	while ((ch = getch()) != 'q')
	{
		newPosition = handleInput(ch, player);
		checkPosition(newPosition, player);
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
