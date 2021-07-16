#include "rogue.h"

void takeTurn(Actor* actor, Actor* player)
{
	int distance = getDistance(actor->entity->position, player->entity->position);
	if (distance < actor->entity->fov_radius &&
		  lineOfSight(actor->entity, player->entity->position.y, player->entity->position.x))
	{
		if (!actor->ai->seen_player)
		{
			//addMessage("The enemy has seen you!");
			actor->ai->seen_player = true;
		}

		moveTowards(actor, player);
	}
	else if (actor->ai->seen_player)
	{
		moveTowards(actor, player);
	}
}

void allMonstersTakeTurns(Actor* player)
{
	List* temp = actors;
	while (temp = temp->next)
	{
		if (!(temp->actor->dead) && strcmp(temp->actor->name, "player"))
		{
			takeTurn(temp->actor, player);
		}
	}
}

void moveTowards(Actor* actor, Actor* target)
{
	Position direction;
	int dy, dx;
	int actor_y = actor->entity->position.y;
	int actor_x = actor->entity->position.x;
	int target_y = target->entity->position.y;
	int target_x = target->entity->position.x;

	dy = target_y - actor_y;
	dx = target_x - actor_x;

	if (abs(dy) < 2 && abs(dx) < 2)
	{
		attack(actor->fighter, target->fighter);
	}
	else
	{
		if (dy != 0)
		{
			dy = (dy < 0) ? -1 : 1;
		}
		if (dx != 0)
		{
			dx = (dx < 0) ? -1 : 1;
		}

		direction.y = actor_y + dy;
		direction.x = actor_x + dx;

		switch(level[direction.y][direction.x].ch)
		{
			case '.':
				monsterMove(direction, actor->entity);
				break;
			default:
				break;
		}
	}
}

void monsterMove(Position direction, Entity* entity)
{
	List* node;
	bool occupied = false;

	node = actors;
	while ((node = node->next) && (strcmp(node->actor->name, "player")))
	{
		if (!node->actor->dead && 
				node->actor->entity->position.y == direction.y && 
				node->actor->entity->position.x == direction.x)
		{
			occupied = true;
		}
	}
	if (!occupied)
	{
		entity->position.y = direction.y;
		entity->position.x = direction.x;
	}
}

