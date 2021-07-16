#include "rogue.h"

void drawUI(void)
{
	Fighter* player_f = player->fighter;
	List* node;
	char text[1024];
	int seen_counter = 0;
	int hp = player_f->hp;
	int max_hp = player_f->max_hp;
	Position clear_a = { 112, 0 };
	Position clear_b = { 137, 7 };

	clrRect(clear_a, clear_b);
	snprintf(text, sizeof(char)*1024, "Dungeon Lvl %i", dungeon_level);
	mvprintw(0, 112, text);
	snprintf(text, sizeof(char)*1024, "Player Lvl %i", player_f->level);
	mvprintw(1, 112, text);
	snprintf(text, sizeof(char)*1024, "HP:%i/%i", hp, max_hp);
	mvprintw(3, 112, text);
	snprintf(text, sizeof(char)*1024, "MP:%i/%i", player_f->mana, player_f->max_mana);
	mvprintw(4, 112, text);
	snprintf(text, sizeof(char)*1024, "ATK: %i", player_f->attack);
	mvprintw(5, 112, text);
	snprintf(text, sizeof(char)*1024, "DEF: %i", player_f->defense);
	mvprintw(6, 112, text);
	snprintf(text, sizeof(char)*1024, "XP:%i/%i", player_f->xp, player_f->xp_to_next_level);
	mvprintw(7, 112, text);
	mvprintw(9, 112, "Player sees:");
	for (int i = 0; i < 10; i++)
	{
		move(10 + i, 112);
		clrtoeol();
	}

	node = actors;
	while ((node = node->next) && (strcmp(node->actor->name, "player")))
	{
		Position pos = node->actor->entity->position;
		if (level[pos.y][pos.x].visible)
		{
			mvaddch(10 + seen_counter, 112, node->actor->entity->ch | node->actor->entity->color);
			mvprintw(10 + seen_counter, 114, node->actor->name);
			
			seen_counter++;
		}
	}
	node = items;
	while (node = node->next)
	{
		Position pos = node->item->entity->position;
		if (level[pos.y][pos.x].visible)
		{
			mvaddch(10 + seen_counter, 112, node->item->entity->ch | node->item->entity->color);
			mvprintw(10 + seen_counter, 114, node->item->name);

			seen_counter++;
		}
	}

	if (level[down_stairs.y][down_stairs.x].visible)
	{
		mvaddch(10 + seen_counter, 112, level[down_stairs.y][down_stairs.x].ch | level[down_stairs.y][down_stairs.x].color);
		mvprintw(10 + seen_counter, 114, "Down Stairs");

		seen_counter++;
	}
	if (level[up_stairs.y][up_stairs.x].visible)
	{
		mvaddch(10 + seen_counter, 112, level[up_stairs.y][up_stairs.x].ch | level[up_stairs.y][up_stairs.x].color);
		mvprintw(10 + seen_counter, 114, "Up Stairs");

		seen_counter++;
	}

	if (!seen_counter)
	{
		mvprintw(10, 112, "Nothing");
	}
}

