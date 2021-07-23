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
			newPosition = goDownStairs(player->entity);
			break;
		// Go up stairs
		case '<':
			free(newPosition);
			newPosition = goUpStairs(player->entity);
			break;
		// Grab an Item
		case 'g':
			grabItem(player->entity);
			break;
		// Use Inventory
		case 'I':
			useInventory(player->inventory);
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
	List* node = actors;
	bool occupied = false;

	while ((node = node->next) && (node->actor != player->owner))
	{
		if (!node->actor->dead && 
				node->actor->entity->position.y == newPosition->y && 
				node->actor->entity->position.x == newPosition->x)
		{
			attack(player->owner->fighter, node->actor->fighter);
			occupied = true;
			break;
		}
	}
	if ((!occupied) && (level[newPosition->y][newPosition->x].walkable))
	{
		playerMove(newPosition, player);
	}
}

void playerMove(Position* newPosition, Entity* player)
{
	clearFOV(player);
	player->position.y = newPosition->y;
	player->position.x = newPosition->x;
	makeFOV(player);
}

Position* goDownStairs(Entity* player)
{
	Position* temp = calloc(1, sizeof(Position));

	if (level[player->position.y][player->position.x].ch == '>')
	{
		dungeon_level++;
		clearLevel();
		createNewLevel();
		appendActor(actors, player->owner);
		addMessage("You go deeper into the dungeon!");
		temp->y = up_stairs.y;	
		temp->x = up_stairs.x;
		return temp;
	}
	else
	{
		addMessage("There are no DOWN stairs here!");
		temp->y = player->position.y;
		temp->x = player->position.x;
		return temp;
	}
}

Position* goUpStairs(Entity* player)
{
	Position* temp = calloc(1, sizeof(Position));

	if (level[player->position.y][player->position.x].ch == '<')
	{
		dungeon_level--;
		clearLevel();
		createNewLevel();
		appendActor(actors, player->owner);
		addMessage("You go up the levels of the dungeon!");
		temp->y = down_stairs.y;
		temp->x = down_stairs.x;
		return temp;
	}
	else
	{
		addMessage("There are no UP stairs here!");
		temp->y = player->position.y;
		temp->x = player->position.x;
		return temp;
	}
}


void grabItem(Entity* player)
{
	List* temp = items;

	while (temp = temp->next)
	{
		if (temp->item->entity->position.y == player->position.y &&
				temp->item->entity->position.x == player->position.x)
		{
			if (player->owner->inventory->n_items < 10)
			{
				player->owner->inventory->items[player->owner->inventory->n_items] = temp->item;
				player->owner->inventory->n_items++;
				temp->item->entity->position.y = 0;
				temp->item->entity->position.x = 0;
				removeItem(items, temp->item, true);
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


