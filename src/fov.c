#include "rogue.h"


int RADIUS = 5;

void makeFOV(Entity* player) 
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
				if (isInMap(y, x) && lineOfSight(player, y, x))
				{
					level[y][x].visible = true;
					level[y][x].seen = true;
				}
			}
		}
	}
}

void clearFOV(Entity* player) 
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

bool lineOfSight(Entity* origin, int target_y, int target_x)
{
	int t, x, y, abs_delta_x, abs_delta_y, sign_x, sign_y, delta_x, delta_y;

	delta_x = origin->position.x - target_x;
	delta_y = origin->position.y - target_y;

	abs_delta_x = abs(delta_x);
	abs_delta_y = abs(delta_y);

	sign_x = getSign(delta_x);
	sign_y = getSign(delta_y);

	x = target_x;
	y = target_y;

	if (abs_delta_x > abs_delta_y)
	{
		t = abs_delta_y * 2 - abs_delta_x;

		do
		{
			if(t >= 0)
			{
				y += sign_y;
				t -= abs_delta_x * 2;
			}

			x += sign_x;
			t += abs_delta_y * 2;

			if (x == origin->position.x && y == origin->position.y)
			{
				return true;
			}
		}
		while(level[y][x].transparent);

		return false;
	}
	else
	{
		t = abs_delta_x * 2 - abs_delta_y;

		do
		{
			if (t >= 0)
			{
				x += sign_x;
				t -= abs_delta_y * 2;
			}

			y += sign_y;
			t += abs_delta_x * 2;

			if (x == origin->position.x && y == origin->position.y)
			{
				return true;
			}
		}
		while(level[y][x].transparent);

		return false;
	}
}

int getSign(int a)
{
	return (a<0) ? -1 : 1;
}
