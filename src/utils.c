#include "rogue.h"

int maxInt(int a, int b)
{
	return (a > b) ? a : b;
}

int minInt(int a, int b)
{
	return (a < b) ? a : b;
}

void clrRect(Position a, Position b)
{
	for (int y = a.y; y < b.y; y++)
	{
		for (int x = a.x; x < b.x; x++)
		{
			mvaddch(y, x, ' ');
		}
	}
}
