#include "rogue.h"

void drawEverything(void)
{
	mapDraw();
	drawAllEntities();
	printMessages();
	drawUI();
}

void drawEntity(Entity* entity)
{
	mvaddch(entity->position.y, entity->position.x, entity->ch | entity->color);
}

void drawAllEntities(void)
{
	List* node;
	int x, y;
	for (int j = 0; j <= ACTOR; j++)
	{
		node = actors;
		while (node = node->next)
		{
			if (node->actor->entity->draw_order == j)
			{
				y = node->actor->entity->position.y;
				x = node->actor->entity->position.x;
				if (level[y][x].visible)
				{
					drawEntity(node->actor->entity);
				}
			}
		}
		if (j == ITEM)
		{
			node = items;

			while (node = node->next)
			{
				y = node->item->entity->position.y;
				x = node->item->entity->position.x;
				if (level[y][x].visible)
				{
					drawEntity(node->item->entity);
				}
			}
		}
	}
}

void mapDraw(void)
{
	int x, y;
	for (y = 0; y < MAP_HEIGHT; y++)
	{
		for (x = 0; x < MAP_WIDTH; x++)
		{
			if (level[y][x].visible)
			{
				mvaddch(y, x, level[y][x].ch | level[y][x].color);
			}
			else if (level[y][x].seen)
			{
				mvaddch(y, x, level[y][x].ch | COLOR_PAIR(SEEN_COLOR));
			}
			else
			{
				mvaddch(y, x, ' ');
			}
		}
	}
}

void showWholeMap(void)
{
	int x, y;
	for (y = 0; y < MAP_HEIGHT; y++)
	{
		for (x = 0; x < MAP_WIDTH; x++)
		{
			mvaddch(y, x, level[y][x].ch);
			level[y][x].visible = true;
		}
	}
	drawAllEntities();

	for (y = 0; y < MAP_HEIGHT; y++)
	{
		for (x = 0; x < MAP_WIDTH; x++)
		{
			level[y][x].visible = false;
		}
	}
	makeFOV(player->entity);
}

void drawUI(void)
{
	Fighter* player_f = player->fighter;
	List* node;
	char text[1024];
	int seen_counter = 0;
	int hp = player_f->hp;
	int max_hp = player_f->max_hp;
	Position clear_a = { 112, 0 };
	Position clear_b = { 137, 7 };

	clrRect(clear_a, clear_b);
	snprintf(text, sizeof(char)*1024, "Dungeon Lvl %i", dungeon_level);
	mvprintw(0, 112, text);
	snprintf(text, sizeof(char)*1024, "Player Lvl %i", player_f->level);
	mvprintw(1, 112, text);
	snprintf(text, sizeof(char)*1024, "HP:%i/%i", hp, max_hp);
	mvprintw(3, 112, text);
	snprintf(text, sizeof(char)*1024, "MP:%i/%i", player_f->mana, player_f->max_mana);
	mvprintw(4, 112, text);
	snprintf(text, sizeof(char)*1024, "ATK: %i", player_f->attack);
	mvprintw(5, 112, text);
	snprintf(text, sizeof(char)*1024, "DEF: %i", player_f->defense);
	mvprintw(6, 112, text);
	snprintf(text, sizeof(char)*1024, "XP:%i/%i", player_f->xp, player_f->xp_to_next_level);
	mvprintw(7, 112, text);
	mvprintw(9, 112, "Player sees:");
	for (int i = 0; i < 10; i++)
	{
		move(10 + i, 112);
		clrtoeol();
	}

	node = actors;
	while ((node = node->next) && (strcmp(node->actor->name, "player")))
	{
		Position pos = node->actor->entity->position;
		if (level[pos.y][pos.x].visible)
		{
			mvaddch(10 + seen_counter, 112, node->actor->entity->ch | node->actor->entity->color);
			mvprintw(10 + seen_counter, 114, node->actor->name);
			
			seen_counter++;
		}
	}
	node = items;
	while (node = node->next)
	{
		Position pos = node->item->entity->position;
		if (level[pos.y][pos.x].visible)
		{
			mvaddch(10 + seen_counter, 112, node->item->entity->ch | node->item->entity->color);
			mvprintw(10 + seen_counter, 114, node->item->name);

			seen_counter++;
		}
	}

	if (level[down_stairs.y][down_stairs.x].visible)
	{
		mvaddch(10 + seen_counter, 112, level[down_stairs.y][down_stairs.x].ch | level[down_stairs.y][down_stairs.x].color);
		mvprintw(10 + seen_counter, 114, "Down Stairs");

		seen_counter++;
	}
	if (level[up_stairs.y][up_stairs.x].visible)
	{
		mvaddch(10 + seen_counter, 112, level[up_stairs.y][up_stairs.x].ch | level[up_stairs.y][up_stairs.x].color);
		mvprintw(10 + seen_counter, 114, "Up Stairs");

		seen_counter++;
	}

	if (!seen_counter)
	{
		mvprintw(10, 112, "Nothing");
	}
}
