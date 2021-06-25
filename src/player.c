#include "rogue.h"

Player* playerSetUp(Room* room)
{
	Player* newPlayer; 
	newPlayer = malloc(sizeof(Player));
	newPlayer->position.x = room->center->x;
	newPlayer->position.y = room->center->y;
	newPlayer->health = 20;

	mvprintw(newPlayer->position.y, newPlayer->position.x, "@");
	move(newPlayer->position.y, newPlayer->position.x);

	return newPlayer;
}

Position* handleInput(int input, Player* user)
{
	Position* newPosition;
	newPosition = malloc(sizeof(Position));
	switch (input)
	{
		// move up
		case 'w':
		case 'W':
		case 'k':
			newPosition->y = user->position.y - 1;
			newPosition->x = user->position.x;
			break;
		// move down
		case 's':
		case 'S':
		case 'j':
			newPosition->y = user->position.y + 1;
			newPosition->x = user->position.x;
			break;
		// move left
		case 'a':
		case 'A':
		case 'h':
			newPosition->y = user->position.y;
			newPosition->x = user->position.x - 1;
			break;
		// move right
		case 'd':
		case 'D':
		case 'l':
			newPosition->y = user->position.y;
			newPosition->x = user->position.x + 1;
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

int checkPosition(Position* newPosition, Player* player)
{
	switch (mvinch(newPosition->y, newPosition->x))
	{
		case '.':
			playerMove(newPosition, player);
			break;
		default:
			move(player->position.y, player->position.x);
			break;
	}
}

int playerMove(Position* newPosition, Player* user)
{
	//char buffer[8];
	//sprintf(buffer, "%c", level[user->position.y][user->position.x].ch);
	//mvprintw(user->position.y, user->position.x, level[user->position.y][user->position.x].ch);

	clearFOV(user);
	user->position.y = newPosition->y;
	user->position.x = newPosition->x;
	makeFOV(user);
	mapDraw();
	mvprintw(user->position.y, user->position.x, "@");
	move(user->position.y, user->position.x);
}
