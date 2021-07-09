#include "rogue.h"

int MIN_SIZE = 4;
int MAX_SIZE = 9;
int MAX_MONSTERS_PER_ROOM = 2;

Room** mapSetUp(void)
{
	int y, x, height, width, max_rooms, n_monsters;
	max_rooms = rand() % 15 + 5;
	Room** rooms;
	rooms = malloc(sizeof(Room) * max_rooms);

	for (int i = 0; i < max_rooms; i++)
	{
		y = rand() % (GAMEMAP_HEIGHT - 15) + 1;
		x = rand() % (GAMEMAP_WIDTH - 15) + 1;
		height = rand() % MAX_SIZE + MIN_SIZE;
		width = rand() % MAX_SIZE + MIN_SIZE;
		n_monsters = rand() % MAX_MONSTERS_PER_ROOM;

		rooms[i] = createRoom(y, x, height, width);
		for (int j = 0; j < n_monsters; j++)
		{
			MonsterTemplate template;
			if (n_actors >= MAX_MONSTERS || i == 0)
			{
				break;
			}
			int monster_y = rand() % (height - 2) + y + 1;
			int monster_x = rand() % (width - 2) + x + 1;
			int monster_level = rand() % 3;
			int monster_type = rand() % 10;
			if (monster_type < 4)
			{
				template = goblin;
			}
			else if (monster_type < 9)
			{
				template = orc;
			}
			else
			{
				template = troll;
			}
			actors[n_actors] = createMonster(monster_y, monster_x, template, monster_level);
			entities[n_entities] = actors[n_actors]->entity;
			n_actors++;
			n_entities++;
		}

		if (n_items < MAX_ITEMS)
		{
			for (int k = 0; k < 1; k++)
			{
				ItemTemplate itemTemp;
				int item_y = rand() % (height - 2) + y + 1;
				int item_x = rand() % (width - 2) + x + 1;
				int item_type = rand() % 10;
				if (item_type > 6)
				{
					itemTemp = health_potion;
				}
				else if (item_type > 4)
				{
					itemTemp = lightning_scroll;
				}
				else if (item_type > 1)
				{
					itemTemp = fireball_scroll;
				}
				else
				{
					itemTemp = mana_potion;
				}
				items[n_items] = createItem(item_y, item_x, itemTemp);
				entities[n_entities] = items[n_items]->entity;
				n_items++;
				n_entities++;
			}
		}

		drawRoom(rooms[i]);
		

		if (i > 0) 
		{
			connectRoomCenters(rooms[i]->center, rooms[i-1]->center);
		}
		if (i == max_rooms - 1)
		{
			addDownStairs(rooms[i]->center);
		}
	}
	return rooms;
}

void addDownStairs(Position* center)
{
	level[center->y][center->x].ch = '>';
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
