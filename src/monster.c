#include "rogue.h"

MonsterTemplate goblin = {'g', COLOR_PAIR(GREEN_COLOR), 15, 6, 2, 0, "goblin"};
MonsterTemplate orc = {'o', COLOR_PAIR(GREEN_COLOR), 10, 10, 3, 1, "orc"};
MonsterTemplate troll = {'T', COLOR_PAIR(GREEN_COLOR), 7, 20, 5, 2, "troll"}; 

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
	monster->entity->color = template.color;
	monster->entity->fov_radius = template.fov_radius;
	monster->entity->owner = monster;
	monster->fighter->hp = template.hp * xpLevel;
	monster->fighter->max_hp = template.hp * xpLevel;
	monster->fighter->attack = template.attack * xpLevel;
	monster->fighter->defense = template.defense * xpLevel;
	monster->fighter->owner = monster;
	monster->ai->seen_player = false;
	monster->ai->last_player_position.y = -1;
	monster->ai->last_player_position.x = -1;
	monster->ai->owner = monster;
	monster->name = template.name;
	monster->dead = false;

	return monster;
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

