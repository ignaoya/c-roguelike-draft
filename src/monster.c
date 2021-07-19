#include "rogue.h"

MonsterTemplate goblin = {'g', COLOR_PAIR(GREEN_COLOR), 15, 6, 2, 0, "goblin"};
MonsterTemplate orc = {'o', COLOR_PAIR(GREEN_COLOR), 10, 10, 3, 1, "orc"};
MonsterTemplate troll = {'T', COLOR_PAIR(GREEN_COLOR), 7, 20, 5, 2, "troll"}; 
MonsterTemplate balrog = {'B', COLOR_PAIR(RED_COLOR), 15, 100, 25, 10, "Balrog"};

Actor* createMonster(int y, int x, MonsterTemplate template, int xpLevel)
{
	Actor* monster;
	monster = malloc(sizeof(Actor));
	monster->entity = malloc(sizeof(Entity));
	monster->fighter = malloc(sizeof(Fighter));
	monster->ai = malloc(sizeof(AI));
	monster->inventory = malloc(sizeof(Inventory));
	monster->equipment = malloc(sizeof(Equipment));

	monster->entity->position.y = y;
	monster->entity->position.x = x;
	monster->entity->ch = template.ch;
	monster->entity->color = template.color;
	monster->entity->draw_order = ACTOR;
	monster->entity->fov_radius = template.fov_radius;
	monster->entity->owner = monster;
	monster->fighter->level = xpLevel;
	monster->fighter->xp = 0;
	monster->fighter->xp_to_next_level = 25;
	monster->fighter->hp = template.hp * xpLevel;
	monster->fighter->max_hp = template.hp * xpLevel;
	monster->fighter->mana = 0;
	monster->fighter->max_mana = 0;
	monster->fighter->attack = template.attack * xpLevel;
	monster->fighter->defense = template.defense * xpLevel;
	monster->fighter->owner = monster;
	monster->ai->seen_player = false;
	monster->ai->last_player_position.y = -1;
	monster->ai->last_player_position.x = -1;
	monster->inventory->n_items = 0;
	memcpy(monster->name, template.name, sizeof(char) * 64);
	monster->equipment->weapon = NULL;
	monster->equipment->shield = NULL;
	monster->equipment->helm = NULL;
	monster->dead = false;

	return monster;
}

