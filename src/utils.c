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


