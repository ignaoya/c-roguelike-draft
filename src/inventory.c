#include "rogue.h"

void inventoryMenu(void)
{
	int ch;
	int cursorPos = 0;
	int itemOffset = 0;
	int itemIndex;
	bool itemWasConsumed = false;
	bool showInventory = true;
	Inventory* inventory = player->inventory;
	Position clr_a = {51, 13};
	Position clr_b = {85, 18};

	mvprintw(10, 50, "####################################");
	mvprintw(11, 50, "#             Inventory            #");
	mvprintw(12, 50, "####################################");
	mvprintw(13, 50, "#                                  #");
	mvprintw(14, 50, "#                                  #");
	mvprintw(15, 50, "#                                  #");
	mvprintw(16, 50, "#                                  #");
	mvprintw(17, 50, "#                                  #");
	mvprintw(18, 50, "####################################");
	mvprintw(19, 50, "# [space]: USE [d]: DROP [q]: EXIT #");
	mvprintw(20, 50, "####################################");

	while (showInventory)
	{
		clrRect(clr_a, clr_b);

		mvprintw(13 + cursorPos, 52, "X");
		for (int i = 0; i < inventory->n_items; i++)
		{
			if (0 <= (i + itemOffset) && (i + itemOffset) < inventory->n_items)
			{
				if (i < 5)
					mvprintw(13 + i, 54, inventory->items[i + itemOffset]->name);
			}
		}

		ch = getch();
		switch(ch)
		{
			case ' ': //use Item
				itemIndex = cursorPos + itemOffset;
				if (itemIndex < inventory->n_items)
				{
					itemWasConsumed = inventory->items[itemIndex]->useFunction(inventory->items[itemIndex], player);
					if (itemWasConsumed)
					{
						consumeItem(inventory, itemIndex);
					}
				}
				else
				{
					continue;
				}
				showInventory = false;
				break;
			case 'd': //drop Item
				itemIndex = cursorPos + itemOffset;
				if (itemIndex < inventory->n_items)
				{
					inventory->items[itemIndex]->entity->position.y = player->entity->position.y;
					inventory->items[itemIndex]->entity->position.x = player->entity->position.x;
					appendItem(items, inventory->items[itemIndex]);
					for (int i = itemIndex; i < inventory->n_items - 1; i++)
					{
						inventory->items[i] = inventory->items[i + 1];
					}
					inventory->n_items--;
				}
				else
				{
					continue;
				}
				addMessage("Dropped item!");
				showInventory = false;
				break;
			case 'j':
				if (cursorPos == 4)
				{
					if (itemOffset + 4 < inventory->n_items)
						itemOffset++;
				}
				else
				{
					cursorPos++;
				}
				break;
			case 'k':
				if (cursorPos == 0)
				{
					if (itemOffset > 0)
						itemOffset--;
				}
				else
				{
					cursorPos--;
				}
				break;
			case 'q':
				showInventory = false;
				break;
			default:
				break;
		}
	}
}





