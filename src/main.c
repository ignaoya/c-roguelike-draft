#include "rogue.h"

const int MAP_HEIGHT = 30;
const int MAP_WIDTH = 110;
Actor* player;
Actor* boss;
Tile** map;
List* actors;
List* items;
Message* message_log;
int dungeon_level = 1;
Position down_stairs;
Position up_stairs;

int main(void)
{
	srand(time(NULL));

	bool compatibleTerminal;
	bool load_successful;

	initLists();
	compatibleTerminal = screenSetUp();
	load_successful = intro();
	showControls();

	if (!load_successful)
	{
		initDungeon();
	}

	if (compatibleTerminal)
	{
		gameLoop();
	}

	closeGame();

	return 0;
}

