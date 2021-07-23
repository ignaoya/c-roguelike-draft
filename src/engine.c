#include "rogue.h"

void initLists(void)
{
	actors = calloc(1, sizeof(List));
	actors->actor = NULL;
	actors->next = NULL;

	items = calloc(1, sizeof(List));
	items->item = NULL;
	items->next = NULL;
}

void initDungeon(bool load_successful)
{
	if (!load_successful)
	{
		Position* newPosition;

		level = createLevelTiles();
		newPosition = mapSetUp();
		player = playerSetUp(newPosition);
		free(newPosition);
		appendActor(actors, player);
		message_log = createLog();
	}

	makeFOV(player->entity);
	drawEverything();
}

void gameLoop(void)
{
	int ch;
	Position* newPosition;

	while (ch = getch())
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
		else if (ch == 'q')
		{
			saveGame();
			break;
		}
		newPosition = handleInput(ch);
		playerCheckPosition(newPosition);
		free(newPosition);
		allMonstersTakeTurns(player);
		drawEverything();
	}
	clear();
	move(20, 60);
	printw("Thank you for playing!");
	getch();
}

void closeGame(void)
{	
	endwin();
	freeEverything();
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

		init_pair(PLAYER_COLOR, COLOR_WHITE, COLOR_BLACK);
		init_pair(VISIBLE_COLOR, COLOR_WHITE, COLOR_BLACK);
		init_pair(SEEN_COLOR, COLOR_BLUE, COLOR_BLACK);
		init_pair(GREEN_COLOR, COLOR_GREEN, COLOR_BLACK);
		init_pair(RED_COLOR, COLOR_RED, COLOR_BLACK);
		init_pair(BLUE_COLOR, COLOR_BLUE, COLOR_BLACK);
		init_pair(CYAN_COLOR, COLOR_CYAN, COLOR_BLACK);
		init_pair(FIRE_COLOR, COLOR_BLACK, COLOR_RED);

		move(20, 60);
		printw("Your terminal supports %d colors.\n", COLORS);
		getch();
		return true;
	}
	printf("Your system does not support colors. Cannot start game!");
	return false;
}

bool intro(void)
{
	int ch;
	bool loadSuccessful;

	clear();
	mvprintw(10, 50, "####################################");
	mvprintw(11, 50, "######## THE MOURNING ABYSS ########");
	mvprintw(12, 50, "####################################");
	mvprintw(13, 50, "# a roguelike by Ignacio Oyarzabal #");
	mvprintw(14, 50, "####################################");
	mvprintw(15, 50, "####################################");
	mvprintw(16, 50, "######  (s) Start New Game    ######");
	mvprintw(17, 50, "######  (l) Load Saved Game   ######");

	while (ch = getch())
	{
		if (ch == 's')
		{
			return false;
		}
		else if (ch == 'l')
		{
			loadSuccessful = loadGame();
			return loadSuccessful;
		}
	}
}

void wonGame(void)
{
	mvprintw(10, 50, "####################################");
	mvprintw(11, 50, "######### CONGRATULATIONS! #########");
	mvprintw(12, 50, "####################################");
	mvprintw(13, 50, "###  You have slain the Balrog!  ###");
	mvprintw(17, 50, "###### Press 'q' Key to Leave ######");

	while (getch() != 'q'){;}
}

void lostGame(void)
{
	mvprintw(10, 50, "####################################");
	mvprintw(11, 50, "#########     YOU LOST!    #########");
	mvprintw(12, 50, "####################################");
	mvprintw(13, 50, "### Your soul has been claimed!! ###");
	mvprintw(17, 50, "###### Press 'q' Key to Leave ######");

	while (getch() != 'q'){;}
}

bool checkVictory(void)
{
	List* node = actors;

	if (dungeon_level == 10)
	{
		while (node = node->next)
		{
			if (node->actor == boss)
			{
				if (node->actor->dead)
				{
					return true;
				}
			}
		}
	}
	return false;	
}
