#include "rogue.h"

MonsterTemplate goblin = {'g', 10, 10, 2, 0, true, "goblin"};

Actor* createMonster(int y, int x, MonsterTemplate template, int xpLevel)
{
	Actor* monster;
	monster = malloc(sizeof(Actor));
	monster->entity = malloc(sizeof(Entity));
	monster->fighter = malloc(sizeof(Fighter));
	monster->ai = malloc(sizeof(AI));

	monster->entity->position.y = y;
	monster->entity->position.x = x;
	monster->entity->ch = template.ch;
	monster->entity->fov_radius = template.fov_radius;
	monster->fighter->hp = template.hp * xpLevel;
	monster->fighter->max_hp = template.hp * xpLevel;
	monster->fighter->attack = template.attack * xpLevel;
	monster->fighter->defense = template.defense * xpLevel;
	monster->ai->seen_player = false;
	monster->ai->last_player_position.y = -1;
	monster->ai->last_player_position.x = -1;
	monster->name = template.name;

	return monster;
}

void drawEntity(Entity* entity)
{
	mvaddch(entity->position.y, entity->position.x, entity->ch | COLOR_PAIR(GREEN_COLOR));
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

