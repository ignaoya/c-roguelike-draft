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

		init_pair(BLACK_COLOR, COLOR_BLACK, COLOR_BLACK);
		init_pair(PLAYER_COLOR, COLOR_BLACK, COLOR_WHITE);
		init_pair(VISIBLE_COLOR, COLOR_WHITE, COLOR_BLACK);
		init_pair(SEEN_COLOR, COLOR_BLUE, COLOR_BLACK);

		move(20, 60);
		printw("Your terminal supports %d colors.\n", COLORS);
		getch();
		return true;
	}
	printf("Your system does not support colors. Cannot start game!");
	return false;
}
