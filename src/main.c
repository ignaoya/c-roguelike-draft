#include "rogue.h"

const int GAMEMAP_HEIGHT = 35;
const int GAMEMAP_WIDTH = 120;
Tile** level;
Actor* actors[15] = { NULL };
int n_actors = 0;
Message** message_log;
int message_count = 0;

int main(void)
{
	srand(time(NULL));
	bool compatibleTerminal;
	Actor* player;
	int ch;
	Position* newPosition;
	Room** rooms;


	level = createLevelTiles();
	compatibleTerminal = screenSetUp();
	rooms = mapSetUp();
	player = playerSetUp(rooms[0]);
	message_log = createLog();

	makeFOV(player->entity);
	mapDraw();
	drawAllMonsters();
	playerDraw(player->entity);

	/* main game loop */
	if (compatibleTerminal)
	{
		while ((ch = getch()) != 'q')
		{
			if (player->dead)
			{
				getch();
				break;
			}
			newPosition = handleInput(ch, player->entity);
			checkPosition(newPosition, player->entity);
			allMonstersTakeTurns(player);
			printMessages();
			playerDraw(player->entity);
			move(0, 0);
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
	curs_set(0);
	if (has_colors())
	{
		start_color();

		init_pair(BLACK_COLOR, COLOR_BLACK, COLOR_BLACK);
		init_pair(PLAYER_COLOR, COLOR_WHITE, COLOR_BLACK);
		init_pair(VISIBLE_COLOR, COLOR_WHITE, COLOR_BLACK);
		init_pair(SEEN_COLOR, COLOR_BLUE, COLOR_BLACK);
		init_pair(GREEN_COLOR, COLOR_GREEN, COLOR_BLACK);
		init_pair(RED_COLOR, COLOR_RED, COLOR_BLACK);

		move(20, 60);
		printw("Your terminal supports %d colors.\n", COLORS);
		getch();
		return true;
	}
	printf("Your system does not support colors. Cannot start game!");
	return false;
}
