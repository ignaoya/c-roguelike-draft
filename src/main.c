#include "rogue.h"

const int GAMEMAP_HEIGHT = 35;
const int GAMEMAP_WIDTH = 120;
const int MAX_MONSTERS = 15;
const int MAX_ITEMS = 15;
Tile** level;
Actor* actors[16] = { NULL };
Item* items[15] = { NULL };
Entity* entities[31] = { NULL };
int n_actors = 0;
int n_items = 0;
int n_entities = 0;
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
	actors[n_actors] = player;
	entities[n_entities] = player->entity;
	message_log = createLog();

	intro();

	makeFOV(player->entity);
	drawEverything();

	/* main game loop */
	if (compatibleTerminal)
	{
		while ((ch = getch()) != 'q')
		{
			if (player->dead)
			{
				lostGame();
				break;
			}
			else if (checkVictory())
			{
				wonGame();
				break;
			}
			newPosition = handleInput(ch, player->entity);
			checkPosition(newPosition, player->entity);
			allMonstersTakeTurns(player);
			drawEverything();
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
		init_pair(BLUE_COLOR, COLOR_BLUE, COLOR_BLACK);

		move(20, 60);
		printw("Your terminal supports %d colors.\n", COLORS);
		getch();
		return true;
	}
	printf("Your system does not support colors. Cannot start game!");
	return false;
}

void intro(void)
{
	clear();
	mvprintw(10, 50, "####################################");
	mvprintw(11, 50, "######## THE MOURNING ABYSS ########");
	mvprintw(12, 50, "####################################");
	mvprintw(13, 50, "# a roguelike by Ignacio Oyarzabal #");
	mvprintw(17, 50, "###### Press Any Key to Start ######");

	getch();
}

void wonGame(void)
{
	mvprintw(10, 50, "####################################");
	mvprintw(11, 50, "######### CONGRATULATIONS! #########");
	mvprintw(12, 50, "####################################");
	mvprintw(13, 50, "# You have killed all the goblins! #");
	mvprintw(17, 50, "###### Press Any Key to Leave ######");

	getch();
}

void lostGame(void)
{
	mvprintw(10, 50, "####################################");
	mvprintw(11, 50, "#########     YOU LOST!    #########");
	mvprintw(12, 50, "####################################");
	mvprintw(13, 50, "### Your soul has been claimed!! ###");
	mvprintw(17, 50, "###### Press Any Key to Leave ######");

	getch();
}

bool checkVictory(void)
{
	for (int i = 0; i < n_actors; i++)
	{
		if (!actors[i]->dead)
		{
			return false;
		}
	}

	return true;
}
