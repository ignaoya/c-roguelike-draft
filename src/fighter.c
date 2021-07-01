#include "rogue.h"

void attack(Fighter* attacker, Fighter* defender)
{
	char text[1024];
	int damage = maxInt(0, attacker->attack - defender->defense);
	char* att_name = attacker->owner->name;
	char* def_name = defender->owner->name;
	takeDamage(defender, damage);
	snprintf(text, sizeof(text), "The %s attacks the %s for %i damage!", att_name, def_name, damage); 
	addMessage(text);
}


void takeDamage(Fighter* fighter, int damage)
{
	fighter->hp = maxInt(0, fighter->hp - damage);
	if (fighter->hp <= 0)
	{
		die(fighter);
	}
}

void die(Fighter* fighter)
{
	char text[1024];
	fighter->owner->dead = true;
	fighter->owner->entity->ch = '%';
	fighter->owner->entity->color = COLOR_PAIR(RED_COLOR);
	fighter->owner->entity->draw_order = CORPSE;


	if (!strcmp(fighter->owner->name, "player"))
	{
		snprintf(text, sizeof(text), "You have been killed!");
	}
	else
	{
		snprintf(text, sizeof(text), "You killed the %s!", fighter->owner->name);
	}
	addMessage(text);
}




