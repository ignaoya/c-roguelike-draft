#include "rogue.h"

void takeTurn(Actor* actor)
{
	int distance = getDistance(actor->entity->position, player->entity->position);
	if (distance < actor->entity->fov_radius &&
		  lineOfSight(actor->entity->position, player->entity->position))
	{
		if (!actor->ai->seen_player)
		{
			actor->ai->seen_player = true;
		}
		actor->ai->last_player_position.y = player->entity->position.y;
		actor->ai->last_player_position.x = player->entity->position.x;

		monsterCheckDirection(actor, player->entity->position);
	}
	else if (actor->ai->seen_player)
	{
		monsterCheckDirection(actor, actor->ai->last_player_position);
	}
}

void allMonstersTakeTurns(void)
{
	List* node = actors;
	while (node = node->next)
	{
		if (!(node->actor->dead) && strcmp(node->actor->name, "player"))
		{
			takeTurn(node->actor);
		}
	}
}

void monsterCheckDirection(Actor* monster, Position target)
{
	Position direction;
	int dy, dx;
	int monster_y = monster->entity->position.y;
	int monster_x = monster->entity->position.x;

	dy = target.y - monster_y;
	dx = target.x - monster_x;

	if (target.y == player->entity->position.y && 
		  target.x == player->entity->position.x && 
			abs(dy) < 2 && abs(dx) < 2)
	{
		attack(monster->fighter, player->fighter);
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

		direction.y = monster_y + dy;
		direction.x = monster_x + dx;

		if (map[direction.y][direction.x].walkable)
		{
			monsterMove(direction, monster->entity);
		}
		else if (map[direction.y - dy][direction.x].walkable)
		{
			direction.y -= dy;
			monsterMove(direction, monster->entity);
		}
		else if (map[direction.y][direction.x - dx].walkable)
		{
			direction.x -= dx;
			monsterMove(direction, monster->entity);
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

