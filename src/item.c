#include "rogue.h"

ItemTemplate health_potion = {'!', COLOR_PAIR(RED_COLOR), useHealthPotion, "Life Potion", false, false, false, false, false, 0};
ItemTemplate mana_potion = {'!', COLOR_PAIR(BLUE_COLOR), useManaPotion, "Mana Potion", false, false, false, false, false, 0};

ItemTemplate lightning_scroll = {'=', COLOR_PAIR(CYAN_COLOR), castLightning, "Bolt Scroll", false, false, false, false, false, 0};
ItemTemplate fireball_scroll = {'=', COLOR_PAIR(RED_COLOR), castFireball, "Fire Scroll", false, false, false, false, false, 0};

ItemTemplate short_sword = {'/', COLOR_PAIR(CYAN_COLOR), equipItem, "Short Sword", true, false, false, false, false, 3};
ItemTemplate small_shield = {'0', COLOR_PAIR(CYAN_COLOR), equipItem, "Small Shield", false, true, false, false, false, 2};
ItemTemplate light_armor = {'H', COLOR_PAIR(CYAN_COLOR), equipItem, "Light Armor", false, false, true, false, false, 2};
ItemTemplate light_helm = {'^', COLOR_PAIR(CYAN_COLOR), equipItem, "Light Helm", false, false, false, true, false, 1};
ItemTemplate ligth_boots = {';', COLOR_PAIR(CYAN_COLOR), equipItem, "Light Boots", false, false, false, false, true, 1};

Item* createItem(int y, int x, ItemTemplate template)
{
	Item* item;
	item = malloc(sizeof(Item));
	item->entity = malloc(sizeof(Entity));

	item->entity->position.y = y;
	item->entity->position.x = x;
	item->entity->ch = template.ch;
	item->entity->color = template.color;
	item->entity->draw_order = ITEM;
	item->entity->fov_radius = 0;
	item->entity->item = item;
	item->useFunction = template.useFunction;
	memcpy(item->name, template.name, sizeof(char) * 64);
	item->weapon = template.weapon;
	item->shield = template.shield;
	item->armor = template.armor;
	item->helm = template.helm;
	item->boots = template.boots;
	item->bonus = template.bonus;

	return item;
}

bool useHealthPotion(Item* self, Actor* drinker)
{
	if (drinker->fighter->hp < drinker->fighter->max_hp)
	{
		drinker->fighter->hp = minInt(drinker->fighter->max_hp, drinker->fighter->hp + 10);
		addMessage("You drank a potion and recovered 10 HP!");
		return true;
	}
	else
	{
		addMessage("You are already at full HP!");
		return false;
	}
}

bool useManaPotion(Item* self, Actor* drinker)
{
	if (drinker->fighter->mana < drinker->fighter->max_mana)
	{
		drinker->fighter->mana = minInt(drinker->fighter->max_mana, drinker->fighter->mana + 5);
		addMessage("You drank a potion and recovered 5 Mana!");
		return true;
	}
	else
	{
		addMessage("You are already at full Mana!");
		return false;
	}
}

bool castLightning(Item* self, Actor* caster)
{
	Actor* target = malloc(sizeof(Actor));
	target = NULL;
	int farthest = 200;
	int temp;
	char text[1024];

	if (caster->fighter->mana >= 2)
	{
		for (int i = 0; i < n_actors; i++)
		{
			if (level[actors[i]->entity->position.y][actors[i]->entity->position.x].visible)
			{
				temp = getDistance(caster->entity->position, actors[i]->entity->position);
				if (temp < farthest && !actors[i]->dead)
				{
					farthest = temp;
					target = actors[i];
				}
			}
		}

		if (target)
		{
			snprintf(text, sizeof(text), "You cast lightning at the %s for %i damage!", target->name, 30);
			addMessage(text);
			takeDamage(target->fighter, 30);
			caster->fighter->mana -= 2;
			gainXP(caster->fighter, 15);
			return true;
		}
		else
		{
			addMessage("There is no one to target!");
			return false;
		}
	}
	else
	{
		addMessage("You don't have enough mana!");
		return false;
	}
}

bool castFireball(Item* self, Actor* caster)
{
	char text[1024];
	int ch = '0';
	int damage;
	char temp;
	Position cursor;

	if (caster->fighter->mana >= 3)
	{
		cursor.y = caster->entity->position.y;
		cursor.x = caster->entity->position.x;

		while (true)
		{
			drawEverything();
			if (cursor.y > GAMEMAP_HEIGHT - 2) cursor.y = GAMEMAP_HEIGHT - 2;
			if (cursor.y < 0) cursor.y = 0;
			if (cursor.x > GAMEMAP_WIDTH - 2) cursor.x = GAMEMAP_WIDTH - 2;
			if (cursor.x < 0) cursor.x = 0;

			for (int y = -1; y < 2; y++)
			{
				for (int x = -1; x < 2; x++)
				{
					temp = mvinch(cursor.y + y, cursor.x + x) & A_CHARTEXT;
					mvaddch(cursor.y + y, cursor.x + x, temp | COLOR_PAIR(FIRE_COLOR));
				}
			}

			
			ch = getch();
			switch(ch)
			{
				case 'j':
					cursor.y++;
					break;
				case 'k':
					cursor.y--;
					break;
				case 'h':
					cursor.x--;
					break;
				case 'l':
					cursor.x++;
					break;
				case 'q':
					addMessage("You stopped casting!");
					return false;
					break;
				case ' ':
					if (level[cursor.y][cursor.x].visible)
					{
						snprintf(text, sizeof(text), "You cast a fireball!");
						addMessage(text);
						for (int y = -1; y < 2; y++)
						{
							for (int x = -1; x < 2; x++)
							{
								for (int i = 0; i <= n_actors; i++)
								{
									if (actors[i]->entity->position.y == cursor.y + y &&
											actors[i]->entity->position.x == cursor.x + x)
									{
										if (y == 0 && x == 0)
										{
											damage = 20;
										}
										else
										{
											damage = 10;
										}
										snprintf(text, sizeof(text), "The %s takes %i damage!", actors[i]->name, damage);
										addMessage(text);
										takeDamage(actors[i]->fighter, damage);
									}
								}
							}
						}
						caster->fighter->mana -= 3;
						gainXP(caster->fighter, 15);
						return true;
					}
					else
					{
						addMessage("You cannot cast a fireball where you can't see!");
					}
					break;
				default:
					break;
			}
		}
	}
	else
	{
		addMessage("You don't have enough mana!");
		return false;
	}
}


void consumeItem(Inventory* inventory, int index)
{
	for (int i = index; i < inventory->n_items - 1; i++)
	{
		inventory->items[i] = inventory->items[i + 1];
	}
	inventory->n_items--;
}

bool equipItem(Item* self, Actor* equiper)
{
	if (self->weapon)
	{
		if (equiper->equipment->weapon)
		{
			equiper->fighter->attack -= equiper->equipment->weapon->bonus;
			unequipItem(equiper->equipment->weapon, equiper);
		}
		equiper->equipment->weapon = self;
		equiper->fighter->attack += self->bonus;
	}
	else if (self->shield)
	{
		if (equiper->equipment->shield)
		{
			equiper->fighter->defense -= equiper->equipment->shield->bonus;
			unequipItem(equiper->equipment->shield, equiper);
		}
		equiper->equipment->shield = self;
		equiper->fighter->defense += self->bonus;
	}
	else if (self->armor)
	{
		if (equiper->equipment->armor)
		{
			equiper->fighter->defense -= equiper->equipment->armor->bonus;
			unequipItem(equiper->equipment->armor, equiper);
		}
		equiper->equipment->armor = self;
		equiper->fighter->defense += self->bonus;
	}
	else if (self->helm)
	{
		if (equiper->equipment->helm)
		{
			equiper->fighter->defense -= equiper->equipment->helm->bonus;
			unequipItem(equiper->equipment->helm, equiper);
		}
		equiper->equipment->helm = self;
		equiper->fighter->defense += self->bonus;
	}
	else if (self->boots)
	{
		if (equiper->equipment->boots)
		{
			equiper->fighter->defense -= equiper->equipment->boots->bonus;
			unequipItem(equiper->equipment->boots, equiper);
		}
		equiper->equipment->boots = self;
		equiper->fighter->defense += self->bonus;
	}

	addMessage("Successfully equipped!");
	return true;
}

void unequipItem(Item* equipment, Actor* actor)
{
	appendItem(items, equipment);

	equipment->entity->position.y = actor->entity->position.y;
	equipment->entity->position.x = actor->entity->position.x;
}




