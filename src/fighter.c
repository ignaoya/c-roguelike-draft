#include "rogue.h"

void attack(Fighter* attacker, Fighter* defender)
{
	char text[1024];
	int damage = maxInt(0, attacker->attack - defender->defense);
	char* att_name = attacker->owner->name;
	char* def_name = defender->owner->name;
	snprintf(text, sizeof(text), "The %s attacks the lvl %i %s for %i damage!", att_name, defender->level, def_name, damage); 
	addMessage(text);
	takeDamage(defender, damage);
	if (!strcmp(attacker->owner->name, "player"))
	{
		gainXP(attacker, damage);
	}
}


void takeDamage(Fighter* fighter, int damage)
{
	fighter->hp = maxInt(0, fighter->hp - damage);
	if (fighter->hp <= 0)
	{
		die(fighter);
	}

	if (!strcmp(fighter->owner->name, "player"))
	{
		gainXP(fighter, damage);
	}

	while (damage > 0)
	{
		spillBlood(fighter->owner->entity);
		damage -= 5;
	}
}

void spillBlood(Entity* entity)
{
	int blood_spot = rand() % 9;
	Position temp;
	temp.y = entity->position.y;
	temp.x = entity->position.x;

	switch(blood_spot)
	{
		case 0:
			level[temp.y - 1][temp.x - 1].color = COLOR_PAIR(RED_COLOR);
			break;
		case 1:
			level[temp.y - 1][temp.x].color = COLOR_PAIR(RED_COLOR);
			break;
		case 2:
			level[temp.y - 1][temp.x + 1].color = COLOR_PAIR(RED_COLOR);
			break;
		case 3:
			level[temp.y][temp.x - 1].color = COLOR_PAIR(RED_COLOR);
			break;
		case 4:
			level[temp.y][temp.x].color = COLOR_PAIR(RED_COLOR);
			break;
		case 5:
			level[temp.y][temp.x + 1].color = COLOR_PAIR(RED_COLOR);
			break;
		case 6:
			level[temp.y + 1][temp.x - 1].color = COLOR_PAIR(RED_COLOR);
			break;
		case 7:
			level[temp.y + 1][temp.x].color = COLOR_PAIR(RED_COLOR);
			break;
		case 8:
			level[temp.y + 1][temp.x + 1].color = COLOR_PAIR(RED_COLOR);
			break;
		default:
			break;
	}
}

void die(Fighter* fighter)
{
	char text[1024];

	if (!strcmp(fighter->owner->name, "player"))
	{
		snprintf(text, sizeof(text), "You have been killed!");
	}
	else
	{
		snprintf(text, sizeof(text), "You killed the lvl %i %s!", fighter->level, fighter->owner->name);
	}
	addMessage(text);

	fighter->owner->dead = true;
	memcpy(fighter->owner->name, "corpse", sizeof(char) * 64);
	fighter->owner->entity->ch = '%';
	fighter->owner->entity->color = COLOR_PAIR(RED_COLOR);
	fighter->owner->entity->draw_order = CORPSE;
}


void gainXP(Fighter* fighter, int amount)
{
	fighter->xp += amount;
	if (fighter->xp >= fighter->xp_to_next_level)
	{
		levelUp(fighter);
	}
}

void levelUp(Fighter* fighter)
{
	int ch = '0';

	fighter->level++;
	fighter->xp_to_next_level = fighter->xp_to_next_level * 2;
	fighter->hp += fighter->max_hp / 5;
	fighter->max_hp += fighter->max_hp / 5;
	fighter->mana += fighter->max_mana / 5;
	fighter->max_mana += fighter->max_mana / 5;
	drawEverything();

	mvprintw(10, 50, "####################################");
	mvprintw(11, 50, "############# LEVEL UP #############");
	mvprintw(12, 50, "####################################");
	mvprintw(13, 50, "#####       Choose a bonus:    #####");
	mvprintw(14, 50, "#           (a): Attack +2         #");
	mvprintw(15, 50, "#           (d): Defense +1        #");
	mvprintw(16, 50, "####################################");
	addMessage("### LEVEL UP ###");
	printMessages();
	while (ch != 'a' && ch != 'd')
	{
		ch = getch();
		switch(ch)
		{
			case 'a':
				fighter->attack += 2;
				break;
			case 'd':
				fighter->defense++;
				break;
			default:
				break;
		}
	}
}


