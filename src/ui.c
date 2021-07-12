#include "rogue.h"

void drawUI(void)
{
	Fighter* player = actors[n_actors]->fighter;
	List* temp;
	char text[1024];
	int seen_counter = 0;
	int hp = player->hp;
	int max_hp = player->max_hp;
	Position clear_a = { 122, 0 };
	Position clear_b = { 137, 7 };

	clrRect(clear_a, clear_b);
	snprintf(text, sizeof(char)*1024, "Dungeon Lvl %i", dungeon_level);
	mvprintw(0, 122, text);
	snprintf(text, sizeof(char)*1024, "Player Lvl %i", player->level);
	mvprintw(1, 122, text);
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
	temp = items;
	while (temp = temp->next)
	{
		Position pos = temp->item->entity->position;
		if (level[pos.y][pos.x].visible)
		{
			mvaddch(10 + seen_counter, 122, temp->item->entity->ch | temp->item->entity->color);
			mvprintw(10 + seen_counter, 124, temp->item->name);

			seen_counter++;
		}
	}

	if (level[down_stairs.y][down_stairs.x].visible)
	{
		mvaddch(10 + seen_counter, 122, level[down_stairs.y][down_stairs.x].ch | level[down_stairs.y][down_stairs.x].color);
		mvprintw(10 + seen_counter, 124, "Down Stairs");

		seen_counter++;
	}
	if (level[up_stairs.y][up_stairs.x].visible)
	{
		mvaddch(10 + seen_counter, 122, level[up_stairs.y][up_stairs.x].ch | level[up_stairs.y][up_stairs.x].color);
		mvprintw(10 + seen_counter, 124, "Up Stairs");

		seen_counter++;
	}

	if (!seen_counter)
	{
		mvprintw(10, 122, "Nothing");
	}
}

