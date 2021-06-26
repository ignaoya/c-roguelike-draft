#include "rogue.h"

Player* playerSetUp(Room* room)
{
	Player* newPlayer; 
	newPlayer = malloc(sizeof(Player));
	newPlayer->position.x = room->center->x;
	newPlayer->position.y = room->center->y;
	newPlayer->ch = '@';
	newPlayer->health = 20;

	playerDraw(newPlayer);

	return newPlayer;
}

Position* handleInput(int input, Player* player)
{
	Position* newPosition;
	newPosition = malloc(sizeof(Position));
	switch (input)
	{
		// move up
		case 'w':
		case 'W':
		case 'k':
			newPosition->y = player->position.y - 1;
			newPosition->x = player->position.x;
			break;
		// move down
		case 's':
		case 'S':
		case 'j':
			newPosition->y = player->position.y + 1;
			newPosition->x = player->position.x;
			break;
		// move left
		case 'a':
		case 'A':
		case 'h':
			newPosition->y = player->position.y;
			newPosition->x = player->position.x - 1;
			break;
		// move right
		case 'd':
		case 'D':
		case 'l':
			newPosition->y = player->position.y;
			newPosition->x = player->position.x + 1;
			break;

		//TODO: View All Map Cheat(for development)
		case 'v':
			showWholeMap();
			break;
		//TODO: Open seen map
		case 'm':
			break;

		default:
			break;
	}

	return newPosition;
}

void checkPosition(Position* newPosition, Player* player)
{
	switch (mvinch(newPosition->y, newPosition->x) & A_CHARTEXT) // Using A_CHARTEXT mask to separate the char from color info.
	{
		case '.':
			playerMove(newPosition, player);
			break;
		default:
			move(player->position.y, player->position.x);
			break;
	}
}

void playerMove(Position* newPosition, Player* player)
{
	//char buffer[8];
	//sprintf(buffer, "%c", level[user->position.y][user->position.x].ch);
	//mvprintw(user->position.y, user->position.x, level[user->position.y][user->position.x].ch);

	clearFOV(player);
	player->position.y = newPosition->y;
	player->position.x = newPosition->x;
	makeFOV(player);
	mapDraw();
	playerDraw(player);
}

void playerDraw(Player* player)
{
	mvaddch(player->position.y, player->position.x, player->ch | COLOR_PAIR(PLAYER_COLOR));
	move(player->position.y, player->position.x);
}
