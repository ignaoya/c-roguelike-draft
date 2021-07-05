#include "rogue.h"

ItemTemplate health_potion = {'!', COLOR_PAIR(RED_COLOR), useHealthPotion, "Life Potion"};
ItemTemplate mana_potion = {'!', COLOR_PAIR(BLUE_COLOR), useManaPotion, "Mana Potion"};

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

void useHealthPotion(Item* self, Actor* drinker)
{
	drinker->fighter->hp = minInt(drinker->fighter->max_hp, drinker->fighter->hp + 10);
	addMessage("You drank a potion and recovered 10 HP!");
	
}

void useManaPotion(Item* self, Actor* drinker)
{
	//drinker->fighter->mana = minInt(drinker->fighter->max_mana, drinker->fighter->mana + 5);
	addMessage("You drank a potion and recovered 10 Mana!");
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

