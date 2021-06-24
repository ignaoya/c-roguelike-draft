#include "rogue.h"

Player* playerSetUp(Room** rooms)
{
	Player* newPlayer; 
	newPlayer = malloc(sizeof(Player));
	newPlayer->position.x = 14;
	newPlayer->position.y = 14;
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
			newPosition->y = user->position.y - 1;
			newPosition->x = user->position.x;
			break;
		// move down
		case 's':
		case 'S':
			newPosition->y = user->position.y + 1;
			newPosition->x = user->position.x;
			break;
		// move left
		case 'a':
		case 'A':
			newPosition->y = user->position.y;
			newPosition->x = user->position.x - 1;
			break;
		// move right
		case 'd':
		case 'D':
			newPosition->y = user->position.y;
			newPosition->x = user->position.x + 1;
			break;

		default:
			break;
	}

	return newPosition;
}

int checkPosition(Position* newPosition, Player* player, Tile** level)
{
	switch (mvinch(newPosition->y, newPosition->x))
	{
		case '.':
			playerMove(newPosition, player, level);
			break;
		default:
			move(player->position.y, player->position.x);
			break;
	}
}

int playerMove(Position* newPosition, Player* user, Tile** level)
{
	//char buffer[8];
	//sprintf(buffer, "%c", level[user->position.y][user->position.x].ch);
	//mvprintw(user->position.y, user->position.x, level[user->position.y][user->position.x].ch);

	clearFOV(level, user);
	user->position.y = newPosition->y;
	user->position.x = newPosition->x;
	makeFOV(level, user);
	mapDraw(level);
	mvprintw(user->position.y, user->position.x, "@");
	move(user->position.y, user->position.x);
}
