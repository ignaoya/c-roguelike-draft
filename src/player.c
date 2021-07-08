#include "rogue.h"

Actor* playerSetUp(Room* room)
{
	Actor* newPlayer; 
	newPlayer = malloc(sizeof(Actor));
	newPlayer->entity = malloc(sizeof(Entity));
	newPlayer->fighter = malloc(sizeof(Fighter));
	newPlayer->ai = malloc(sizeof(AI));
	newPlayer->inventory = malloc(sizeof(Inventory));


	newPlayer->entity->position.x = room->center->x;
	newPlayer->entity->position.y = room->center->y;
	newPlayer->entity->ch = '@';
	newPlayer->entity->color = COLOR_PAIR(PLAYER_COLOR);
	newPlayer->entity->draw_order = ACTOR;
	newPlayer->entity->fov_radius = 12;
	newPlayer->entity->owner = newPlayer;
	newPlayer->fighter->level = 1;
	newPlayer->fighter->xp = 0;
	newPlayer->fighter->xp_to_next_level = 25;
	newPlayer->fighter->hp = 50;
	newPlayer->fighter->max_hp = 50;
	newPlayer->fighter->mana = 10;
	newPlayer->fighter->max_mana = 10;
	newPlayer->fighter->attack = 5;
	newPlayer->fighter->defense = 1;
	newPlayer->fighter->owner = newPlayer;
	newPlayer->inventory->items[0] = createItem(0, 0, health_potion);
	newPlayer->inventory->n_items = 1;
	memcpy(newPlayer->name, "player", sizeof(char) * 64);
	newPlayer->dead = false;

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

		// Grab an Item
		case 'g':
			grabItem(player);
			break;
		// Use Inventory
		case 'I':
			useInventory(player->owner->inventory);
			break;
		// View All Map Cheat(for development)
		case 'v':
			showWholeMap();
			getch();
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
		switch (level[newPosition->y][newPosition->x].ch)
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
}

void grabItem(Entity* player)
{
	for (int i = 0; i < n_items; i++)
	{
		if (items[i]->entity->position.y == player->position.y &&
				items[i]->entity->position.x == player->position.x)
		{
			if (player->owner->inventory->n_items < 10)
			{
				player->owner->inventory->items[player->owner->inventory->n_items] = items[i];
				player->owner->inventory->n_items++;
				items[i]->entity->position.y = 0;
				items[i]->entity->position.x = 0;
				addMessage("You pick up an item.");
			}
			else
			{
				addMessage("Your inventory is full.");
			}
			return;
		}
	}
	addMessage("There's nothing to pick up.");
}

void gainXP(Fighter* player, int amount)
{
	player->xp += amount;
	if (player->xp >= player->xp_to_next_level)
	{
		levelUp(player);
	}
}

void levelUp(Fighter* player)
{
	int ch = '0';

	player->level++;
	player->xp_to_next_level = player->xp_to_next_level * 2;
	player->hp += player->max_hp / 5;
	player->max_hp += player->max_hp / 5;
	player->mana += player->max_mana / 5;
	player->max_mana += player->max_mana / 5;
	drawEverything();

	mvprintw(10, 50, "####################################");
	mvprintw(11, 50, "############# LEVEL UP #############");
	mvprintw(12, 50, "####################################");
	mvprintw(13, 50, "#####       Choose a bonus:    #####");
	mvprintw(14, 50, "#           (a): Attack +2         #");
	mvprintw(15, 50, "#           (d): Defense +1        #");
	mvprintw(16, 50, "####################################");
	addMessage("### LEVEL UP ###");
	printMessages();
	while (ch != 'a' && ch != 'd')
	{
		ch = getch();
		switch(ch)
		{
			case 'a':
				player->attack += 2;
				break;
			case 'd':
				player->defense++;
				break;
			default:
				break;
		}
	}
}


