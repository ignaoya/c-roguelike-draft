#include "rogue.h"

void drawUI(void)
{
	Fighter* player = actors[n_actors]->fighter;
	char text[1024];
	int seen_counter = 0;
	int hp = player->hp;
	int max_hp = player->max_hp;
	Position clear_a = { 122, 3 };
	Position clear_b = { 137, 7 };
	mvprintw(1, 122, "Player Lvl");
	mvaddch(1, 134, player->level + '0'); 
	clrRect(clear_a, clear_b);
	snprintf(text, sizeof(char)*1024, "HP:%i/%i", hp, max_hp);
	mvprintw(3, 122, text);
	snprintf(text, sizeof(char)*1024, "MP:%i/%i", player->mana, player->max_mana);
	mvprintw(4, 122, text);
	snprintf(text, sizeof(char)*1024, "ATK: %i", player->attack);
	mvprintw(5, 122, text);
	snprintf(text, sizeof(char)*1024, "DEF: %i", player->defense);
	mvprintw(6, 122, text);
	snprintf(text, sizeof(char)*1024, "XP:%i/%i", player->xp, player->xp_to_next_level);
	mvprintw(7, 122, text);
	mvprintw(9, 122, "Player sees:");
	for (int i = 0; i < 10; i++)
	{
		move(10 + i, 122);
		clrtoeol();
	}
	for (int i = 0; i < n_actors; i++)
	{
		Position temp = actors[i]->entity->position;
		if (level[temp.y][temp.x].visible)
		{
			mvaddch(10 + seen_counter, 122, actors[i]->entity->ch | actors[i]->entity->color);
			mvprintw(10 + seen_counter, 124, actors[i]->name);
			
			seen_counter++;
		}
	}
	for (int i = 0; i < n_items; i++)
	{
		Position temp = items[i]->entity->position;
		if (level[temp.y][temp.x].visible)
		{
			mvaddch(10 + seen_counter, 122, items[i]->entity->ch | items[i]->entity->color);
			mvprintw(10 + seen_counter, 124, items[i]->name);

			seen_counter++;
		}
	}

	if (!seen_counter)
	{
		mvprintw(10, 122, "Nothing");
	}
}

