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
	int x, y;
	for (int j = 0; j < ACTOR + 1; j++)
	{
		for (int i = 0; i <= n_actors; i++)
		{
			if (actors[i]->entity->draw_order == j)
			{
				y = actors[i]->entity->position.y;
				x = actors[i]->entity->position.x;
				if (level[y][x].visible)
				{
					drawEntity(actors[i]->entity);
				}
			}
		}
		if (j == ITEM)
		{
			for (int i = 0; i < n_items; i++)
			{
				y = items[i]->entity->position.y;
				x = items[i]->entity->position.x;
				if (level[y][x].visible)
				{
					drawEntity(items[i]->entity);
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
	makeFOV(actors[n_actors]->entity);
}
