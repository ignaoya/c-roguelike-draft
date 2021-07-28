#include "rogue.h"

void attack(Fighter* attacker, Fighter* defender)
{
	char text[1024] = {0};
	int damage = maxInt(0, attacker->attack - defender->defense);
	char* att_name = attacker->owner->name;
	char* def_name = defender->owner->name;
	snprintf(text, sizeof(text), "The %s attacks the lvl %i %s for %i damage!", att_name, defender->level, def_name, damage); 
	addMessage(text);
	takeDamage(defender, damage);
	if (attacker->owner == player)
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

	if (fighter->owner == player)
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
		case 0: temp.y--; temp.x--; break;
		case 1: temp.y--; break;
		case 2: temp.y--; temp.x++; break;
		case 3: temp.x--; break;
		case 4: break;
		case 5: temp.x++; break;
		case 6: temp.y++; temp.x--; break;
		case 7: temp.y++; break;
		case 8: temp.y++; temp.x++;
		default: break;
	}

	map[temp.y][temp.x].color = COLOR_PAIR(RED_COLOR);
}

void die(Fighter* fighter)
{
	char text[1024] = {0};

	if (fighter->owner == player)
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
	fighter->max_hp += fighter->max_hp / 5;
	fighter->hp = fighter->max_hp;
	fighter->max_mana += fighter->max_mana / 5;
	fighter->mana = fighter->max_mana;
	drawEverything();

	mvprintw(10, 50, "####################################");
	mvprintw(11, 50, "############# LEVEL UP #############");
	mvprintw(12, 50, "####################################");
	mvprintw(13, 50, "#####       Choose a bonus:    #####");
	mvprintw(14, 50, "#           (A): Attack +2         #");
	mvprintw(15, 50, "#           (D): Defense +1        #");
	mvprintw(16, 50, "####################################");
	addMessage("### LEVEL UP ###");
	printMessages();
	while (ch != 'A' && ch != 'D')
	{
		ch = getch();
		switch(ch)
		{
			case 'A':
				fighter->attack += 2;
				break;
			case 'D':
				fighter->defense++;
				break;
			default:
				break;
		}
	}
}


