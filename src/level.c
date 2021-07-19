#include "rogue.h"

int MIN_SIZE = 4;
int MAX_SIZE = 9;
int MAX_MONSTERS_PER_ROOM = 2;
int MAX_ITEMS_PER_ROOM = 2;
int CHANCE_OF_ITEM = 70;

Position* mapSetUp(void)
{
	int y, x, height, width, n_rooms, n_monsters, n_items;
	n_rooms = rand() % 15 + 5;
	Position* start_pos = malloc(sizeof(Position));
	Room** rooms;
	rooms = malloc(sizeof(Room*) * n_rooms);

	for (int i = 0; i < n_rooms; i++)
	{
		y = rand() % (GAMEMAP_HEIGHT - 15) + 1;
		x = rand() % (GAMEMAP_WIDTH - 15) + 1;
		height = rand() % MAX_SIZE + MIN_SIZE;
		width = rand() % MAX_SIZE + MIN_SIZE;
		n_monsters = rand() % MAX_MONSTERS_PER_ROOM;
		n_items = rand() % MAX_ITEMS_PER_ROOM;

		rooms[i] = createRoom(y, x, height, width);
		for (int j = 0; j < n_monsters; j++)
		{
			MonsterTemplate template;
			if (i == 0)
			{
				break;
			}
			int monster_y = rand() % (height - 2) + y + 1;
			int monster_x = rand() % (width - 2) + x + 1;
			int monster_level = rand() % dungeon_level + 1;
			int monster_type = rand() % 100;
			if (monster_type < 80 - dungeon_level * dungeon_level)
			{
				template = goblin;
			}
			else if (monster_type < 99 - dungeon_level * 2)
			{
				template = orc;
				monster_level = maxInt(1, monster_level / 2);
			}
			else
			{
				template = troll;
				monster_level = maxInt(1, monster_level / 3);
			}
			appendActor(actors, createMonster(monster_y, monster_x, template, monster_level));
		}

		for (int k = 0; k < n_items; k++)
		{
			if ((rand() % 100) < CHANCE_OF_ITEM)
			{
				continue;
			}
			ItemTemplate itemTemp;
			int item_y = rand() % (height - 2) + y + 1;
			int item_x = rand() % (width - 2) + x + 1;
			int item_level = (rand() % 100) + (10 * dungeon_level);
			int item_type = rand() % 10;
			if (item_level < 60)
			{
				if (item_type < 6)
				{
					itemTemp = health_potion;
				}
				else if (item_type < 8)
				{
					itemTemp = mana_potion;
				}
				else
				{
					itemTemp = light_helm;
				}
			}
			else if (item_level < 80)
			{
				if (item_type < 3)
				{
					itemTemp = health_potion;
				}
				else if (item_type < 6)
				{
					itemTemp = mana_potion;
				}
				else if (item_type < 8)
				{
					itemTemp = lightning_scroll;
				}
				else
				{
					itemTemp = light_helm;
				}
			}
			else
			{
				if (item_type < 2)
				{
					itemTemp = health_potion;
				}
				else if (item_type < 4)
				{
					itemTemp = mana_potion;
				}
				else if (item_type < 6)
				{
					itemTemp = fireball_scroll;
				}
				else if (item_type < 8)
				{
					itemTemp = short_sword;
				}
				else
				{
					itemTemp = small_shield;
				}
			}
			appendItem(items, createItem(item_y, item_x, itemTemp));
		}

		drawRoom(rooms[i]);
		
		if (i > 0) 
		{
			connectRoomCenters(rooms[i]->center, rooms[i-1]->center);
		}
		if (i == n_rooms - 1)
		{
			if (dungeon_level < 10)
			{
				addDownStairs(rooms[i]->center);
			}
			else
			{
				boss = createMonster(rooms[i]->center->y, rooms[i]->center->x, balrog, 1);
				appendActor(actors, boss);
			}
		}
	}
	
	if (dungeon_level > 1)
	{
		addUpStairs(rooms[0]->center);
	}

	start_pos->y = rooms[0]->center->y;
	start_pos->x = rooms[0]->center->x;

	freeAllRooms(rooms, n_rooms);
	return start_pos;
}

void addDownStairs(Position* center)
{
	level[center->y][center->x].ch = '>';
	down_stairs.y = center->y;
	down_stairs.x = center->x;
}

void addUpStairs(Position* center)
{
	level[center->y][center->x].ch = '<';
	up_stairs.y = center->y;
	up_stairs.x = center->x;
}

Tile** createLevelTiles(void)
{
	int x, y;
	Tile** tiles;
	tiles = malloc(sizeof(Tile*) * GAMEMAP_HEIGHT);

	for (y = 0; y < GAMEMAP_HEIGHT; y++)
	{
		tiles[y] = malloc(sizeof(Tile) * GAMEMAP_WIDTH);
		for (x = 0; x < GAMEMAP_WIDTH; x++)
		{
			tiles[y][x].ch = '#';
			tiles[y][x].color = COLOR_PAIR(VISIBLE_COLOR);
			tiles[y][x].walkable = false;
			tiles[y][x].transparent = false;
			tiles[y][x].visible = false;
			tiles[y][x].seen = false;
		}
	}

	return tiles;
}

void clearLevel(void)
{
	List* node;

	node = actors;
	while ((node = node->next) && (node->actor != player))
	{
		freeActor(node->actor);
	}

	freeList(actors);

	node = items;
	while (node = node->next)
	{
		freeItem(node->item);
	}

	freeList(items);

	for (int y = 0; y < GAMEMAP_HEIGHT; y++)
	{
		free(level[y]);
	}
	free(level);
}

void createNewLevel(void)
{
	actors = malloc(sizeof(List));
	actors->actor = NULL;
	actors->next = NULL;

	items = malloc(sizeof(List));
	items->item = NULL;
	items->next = NULL;

	Position* temp;
	level = createLevelTiles();
	temp = mapSetUp();
	free(temp);
}

