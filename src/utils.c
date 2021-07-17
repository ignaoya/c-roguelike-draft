#include "rogue.h"

int maxInt(int a, int b)
{
	return (a > b) ? a : b;
}

int minInt(int a, int b)
{
	return (a < b) ? a : b;
}

void clrRect(Position a, Position b)
{
	for (int y = a.y; y < b.y; y++)
	{
		for (int x = a.x; x < b.x; x++)
		{
			mvaddch(y, x, ' ');
		}
	}
}

void appendItem(List* head, Item* item)
{
	List* temp = head;
	
	while(temp->next)
	{
		temp = temp->next;
	}
	temp->next = malloc(sizeof(List));
	temp = temp->next;
	temp->item = item;
	temp->next = NULL;
}
	
void appendActor(List* head, Actor* actor)
{
	List* temp = head;
	
	while(temp->next)
	{
		temp = temp->next;
	}
	temp->next = malloc(sizeof(List));
	temp = temp->next;
	temp->actor = actor;
	temp->next = NULL;
}

void removeItem(List* head, Item* item, bool cleanUp)
{
	List* curr = head;
	List* prev = head;

	while(curr = curr->next)
	{
		if (curr->item == item)
		{
			prev->next = curr->next;
			if (cleanUp)
			{
				free(curr);
				curr = NULL;
			}
			break;
		}
		prev = prev->next;
	}
}

void removeActor(List* head, Actor* actor, bool cleanUp)
{
	List* curr = head;
	List* prev = head;

	while(curr = curr->next)
	{
		if (curr->actor == actor)
		{
			prev->next = curr->next;
			if (cleanUp)
			{
				free(curr);
				curr = NULL;
			}
			break;
		}
		prev = prev->next;
	}
}

void freeActor(Actor* actor)
{
	free(actor->entity);

	free(actor->fighter);

	free(actor->ai);

	for (int i = 0; i < actor->inventory->n_items; i++)
	{
		freeItem(actor->inventory->items[i]);
	}
	free(actor->inventory);

	free(actor->equipment->weapon);
	free(actor->equipment->shield);
	free(actor->equipment->helm);
	free(actor->equipment);

	free(actor);
}

void freeItem(Item* item)
{
	free(item->entity);
	
	free(item);
}

void freeRoom(Room* room)
{
	free(room->center);
	free(room);
}

void freeAllRooms(Room** rooms, int n_rooms)
{
	for (int i = 0; i < n_rooms; i++)
	{
		freeRoom(rooms[i]);
	}
}


void freeEverything(void)
{
	clearLevel();
	freeActor(player);
}

