#include "rogue.h"

int RADIUS = 5;

void makeFOV(Tile** level, Player* player) 
{
	int y, x;
	double dist, dy, dx;

	for (y = player->position.y - RADIUS; y < player->position.y + RADIUS; y++)
	{
		for (x = player->position.x - RADIUS; x < player->position.x + RADIUS; x++)
		{
			dx = x - player->position.x;
			dy = y - player->position.y;
			dist = sqrt((dx * dx) + (dy * dy));
			if (floor(dist) < RADIUS)
			{
				if (isInMap(y, x))
					level[y][x].visible = true;
			}
		}
	}
}

void clearFOV(Tile** level, Player* player) 
{
	int y, x;

	for (y = player->position.y - RADIUS; y < player->position.y + RADIUS; y++)
	{
		for (x = player->position.x - RADIUS; x < player->position.x + RADIUS; x++)
		{
			if (isInMap(y, x))
				level[y][x].visible = false;
		}
	}
}

bool isInMap(int y, int x)
{
	if ((0 < y && y < GAMEMAP_HEIGHT) && (0 < x && x < GAMEMAP_WIDTH))
	{
		return true;
	}
	return false;
}

