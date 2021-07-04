#include "rogue.h"

ItemTemplate health_potion = {'!', COLOR_PAIR(RED_COLOR), "Life Potion"};
ItemTemplate mana_potion = {'!', COLOR_PAIR(BLUE_COLOR), "Mana Potion"};

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
	item->name = template.name;

	return item;
}
