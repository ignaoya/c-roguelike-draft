#include "rogue.h"

const int GAMEMAP_HEIGHT = 35;
const int GAMEMAP_WIDTH = 120;
Tile** level;

int main(void)
{
	srand(time(NULL));
	bool compatibleTerminal;
	Player* player;
	int ch;
	Position* newPosition;
	Room** rooms;

	level = createLevelTiles();
	compatibleTerminal = screenSetUp();
	rooms = mapSetUp();
	player = playerSetUp(rooms[0]);
	playerMove(&(player->position), player);

	/* main game loop */
	if (compatibleTerminal)
	{
		while ((ch = getch()) != 'q')
		{
			newPosition = handleInput(ch, player);
			checkPosition(newPosition, player);
		}

		clear();
		move(20, 60);
		printw("Thank you for playing!");
	}

	getch();
	endwin();

	return 0;
}

bool screenSetUp(void)
{
	initscr();
	noecho();
	refresh();
	if (has_colors())
	{
		start_color();
		return true;
	}
	printf("Your system does not support colors. Cannot start game!");
	return false;
}
