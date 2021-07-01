#include "rogue.h"

void playerDraw(Entity* player)
{
	mvaddch(player->position.y, player->position.x, player->ch | player->color);
}

void drawEntity(Entity* entity)
{
	mvaddch(entity->position.y, entity->position.x, entity->ch | entity->color);
}

void drawAllMonsters(void)
{
	int x, y;
	for (int i = 0; i < n_actors; i++)
	{
		y = actors[i]->entity->position.y;
		x = actors[i]->entity->position.x;
		if (level[y][x].visible)
		{
			drawEntity(actors[i]->entity);
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
				mvaddch(y, x, level[y][x].ch[0] | COLOR_PAIR(VISIBLE_COLOR));
			}
			else if (level[y][x].seen)
			{
				mvaddch(y, x, level[y][x].ch[0] | COLOR_PAIR(SEEN_COLOR));
			}
			else
			{
				mvprintw(y, x, " ");
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
			mvprintw(y, x, level[y][x].ch);
		}
	}
}
