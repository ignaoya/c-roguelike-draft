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
	for (y = 0; y < GAMEMAP_HEIGHT; y++)
	{
		for (x = 0; x < GAMEMAP_WIDTH; x++)
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
	for (y = 0; y < GAMEMAP_HEIGHT; y++)
	{
		for (x = 0; x < GAMEMAP_WIDTH; x++)
		{
			mvaddch(y, x, level[y][x].ch);
			level[y][x].visible = true;
		}
	}
	drawAllEntities();

	for (y = 0; y < GAMEMAP_HEIGHT; y++)
	{
		for (x = 0; x < GAMEMAP_WIDTH; x++)
		{
			level[y][x].visible = false;
		}
	}
	makeFOV(player->entity);
}
