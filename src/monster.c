#include "rogue.h"

MonsterTemplate goblin = {'g', 10, 2, 0, true, "goblin"};

Actor* createMonster(int y, int x, MonsterTemplate template, int xpLevel)
{
	Actor* monster;
	monster = malloc(sizeof(Actor));
	monster->entity = malloc(sizeof(Entity));
	monster->fighter = malloc(sizeof(Fighter));

	monster->entity->position.y = y;
	monster->entity->position.x = x;
	monster->entity->ch = template.ch;
	monster->fighter->hp = template.hp;
	monster->fighter->max_hp = template.hp;
	monster->fighter->attack = template.attack;
	monster->fighter->defense = template.defense;
	monster->fighter->ai = template.ai;
	monster->name = template.name;

	return monster;
}

void drawEntity(Entity* entity)
{
	mvaddch(entity->position.y, entity->position.x, entity->ch);
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

