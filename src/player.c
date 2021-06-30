#include "rogue.h"

Actor* playerSetUp(Room* room)
{
	Actor* newPlayer; 
	newPlayer = malloc(sizeof(Actor));
	newPlayer->entity = malloc(sizeof(Entity));
	newPlayer->fighter = malloc(sizeof(Fighter));
	newPlayer->ai = NULL;

	newPlayer->entity->position.x = room->center->x;
	newPlayer->entity->position.y = room->center->y;
	newPlayer->entity->ch = '@';
	newPlayer->entity->color = COLOR_PAIR(PLAYER_COLOR);
	newPlayer->entity->fov_radius = 12;
	newPlayer->entity->owner = newPlayer;
	newPlayer->fighter->hp = 20;
	newPlayer->fighter->max_hp = 20;
	newPlayer->fighter->attack = 5;
	newPlayer->fighter->defense = 1;
	newPlayer->fighter->owner = newPlayer;
	newPlayer->name = "player";
	newPlayer->dead = false;

	playerDraw(newPlayer->entity);

	return newPlayer;
}

Position* handleInput(int input, Entity* player)
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
		case 'u':
			newPosition->y = player->position.y - 1;
			newPosition->x = player->position.x - 1;
			break;
		case 'i':
			newPosition->y = player->position.y - 1;
			newPosition->x = player->position.x + 1;
			break;
		case 'n':
			newPosition->y = player->position.y + 1;
			newPosition->x = player->position.x - 1;
			break;
		case 'm':
			newPosition->y = player->position.y + 1;
			newPosition->x = player->position.x + 1;
			break;

		// View All Map Cheat(for development)
		case 'v':
			showWholeMap();
			break;

		default:
			break;
	}

	return newPosition;
}

void checkPosition(Position* newPosition, Entity* player)
{
	bool occupied = false;
	for (int i = 0; i < n_actors; i++)
	{
		if (!actors[i]->dead && 
				actors[i]->entity->position.y == newPosition->y && 
				actors[i]->entity->position.x == newPosition->x)
		{
			attack(player->owner->fighter, actors[i]->fighter);
			occupied = true;
			break;
		}
	}
	if (!occupied)
	{
		switch (*(level[newPosition->y][newPosition->x].ch))
		{
			case '.':
				playerMove(newPosition, player);
				break;
			default:
				break;
		}
	}
}

void playerMove(Position* newPosition, Entity* player)
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

void playerDraw(Entity* player)
{
	mvaddch(player->position.y, player->position.x, player->ch | player->color);
	move(player->position.y, player->position.x);
}
