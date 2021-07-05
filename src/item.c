#include "rogue.h"

ItemTemplate health_potion = {'!', COLOR_PAIR(RED_COLOR), useHealthPotion, "Life Potion"};
ItemTemplate mana_potion = {'!', COLOR_PAIR(BLUE_COLOR), useManaPotion, "Mana Potion"};

ItemTemplate lightning_scroll = {'=', COLOR_PAIR(CYAN_COLOR), castLightning, "Bolt Scroll"};

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
	item->name = template.name;

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

void consumeItem(Inventory* inventory, int index)
{
	for (int i = index; i < inventory->n_items - 1; i++)
	{
		//free(inventory->items[i]);
		inventory->items[i]= inventory->items[i + 1];
	}
	inventory->n_items--;
}

