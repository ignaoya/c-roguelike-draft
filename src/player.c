#include "rogue.h"

Actor* playerSetUp(Position* start_pos)
{
	Actor* newPlayer = calloc(1, sizeof(Actor));
	newPlayer->entity = calloc(1, sizeof(Entity));
	newPlayer->fighter = calloc(1, sizeof(Fighter));
	newPlayer->ai = calloc(1, sizeof(AI));
	newPlayer->inventory = calloc(1, sizeof(Inventory));
	newPlayer->equipment = calloc(1, sizeof(Equipment));


	newPlayer->entity->position.x = start_pos->x;
	newPlayer->entity->position.y = start_pos->y;
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
	newPlayer->equipment->weapon = NULL;
	newPlayer->equipment->shield = NULL;
	newPlayer->equipment->helm = NULL;

	memcpy(newPlayer->name, "player", sizeof(char) * 64);
	newPlayer->dead = false;

	return newPlayer;
}

Position* handleInput(int input)
{
	Position* newPosition = calloc(1, sizeof(Position));
	newPosition->y = player->entity->position.y;
	newPosition->x = player->entity->position.x;
	switch (input)
	{
		// move up
		case 'w':
		case 'k':
			newPosition->y--;
			break;
		// move down
		case 's':
		case 'j':
			newPosition->y++;
			break;
		// move left
		case 'a':
		case 'h':
			newPosition->x--;
			break;
		// move right
		case 'd':
		case 'l':
			newPosition->x++;
			break;
		case 'u':
			newPosition->y--;
			newPosition->x--;
			break;
		case 'i':
			newPosition->y--;
			newPosition->x++;
			break;
		case 'n':
			newPosition->y++;
			newPosition->x--;
			break;
		case 'm':
			newPosition->y++;
			newPosition->x++;
			break;

		// Go down stairs
		case '>':
			free(newPosition);
			newPosition = goDownStairs();
			break;
		// Go up stairs
		case '<':
			free(newPosition);
			newPosition = goUpStairs();
			break;
		// Grab an Item
		case 'g':
			grabItem();
			break;
		// Use Inventory
		case 'I':
			inventoryMenu();
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

void playerCheckPosition(Position* newPosition)
{
	List* node = actors;
	bool occupied = false;

	while ((node = node->next) && (node->actor != player))
	{
		if (!node->actor->dead && 
				node->actor->entity->position.y == newPosition->y && 
				node->actor->entity->position.x == newPosition->x)
		{
			attack(player->fighter, node->actor->fighter);
			occupied = true;
			break;
		}
	}
	if ((!occupied) && (map[newPosition->y][newPosition->x].walkable))
	{
		playerMove(newPosition);
	}
}

void playerMove(Position* newPosition)
{
	clearFOV(player->entity);
	player->entity->position.y = newPosition->y;
	player->entity->position.x = newPosition->x;
	makeFOV(player->entity);
}

Position* goDownStairs(void)
{
	Position* temp = calloc(1, sizeof(Position));

	if (map[player->entity->position.y][player->entity->position.x].ch == '>')
	{
		dungeon_level++;
		clearLevel();
		createNewLevel();
		appendActor(actors, player);
		addMessage("You go deeper into the dungeon!");
		temp->y = up_stairs.y;	
		temp->x = up_stairs.x;
		return temp;
	}
	else
	{
		addMessage("There are no DOWN stairs here!");
		temp->y = player->entity->position.y;
		temp->x = player->entity->position.x;
		return temp;
	}
}

Position* goUpStairs(void)
{
	Position* temp = calloc(1, sizeof(Position));

	if (map[player->entity->position.y][player->entity->position.x].ch == '<')
	{
		dungeon_level--;
		clearLevel();
		createNewLevel();
		appendActor(actors, player);
		addMessage("You go up the levels of the dungeon!");
		temp->y = down_stairs.y;
		temp->x = down_stairs.x;
		return temp;
	}
	else
	{
		addMessage("There are no UP stairs here!");
		temp->y = player->entity->position.y;
		temp->x = player->entity->position.x;
		return temp;
	}
}


void grabItem(void)
{
	List* node = items;

	while (node = node->next)
	{
		if (node->item->entity->position.y == player->entity->position.y &&
				node->item->entity->position.x == player->entity->position.x)
		{
			if (player->inventory->n_items < 10)
			{
				player->inventory->items[player->inventory->n_items] = node->item;
				player->inventory->n_items++;
				removeItem(items, node->item);
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



