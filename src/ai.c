#include "rogue.h"

void takeTurn(Actor* actor, Actor* player)
{
	int distance = getDistance(actor->entity->position, player->entity->position);
	if (distance < actor->entity->fov_radius &&
		  lineOfSight(actor->entity, player->entity->position.y, player->entity->position.x))
	{
		if (!actor->ai->seen_player)
		{
			addMessage("The enemy has seen you!");
			actor->ai->seen_player = true;
		}
		//actor->ai->last_player_position.y = player->entity->position.y;
		//actor->ai->last_player_position.x = player->entity->position.x;

		moveTowards(actor, player);
	}
	else if (actor->ai->seen_player)
	{
		moveTowards(actor, player);
	}
}

void allMonstersTakeTurns(Actor* player)
{
	for (int i = 0; i < n_actors; i++)
	{
		takeTurn(actors[i], player);
	}
	drawAllMonsters();
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
		monsterAttack(actor->fighter, target->fighter);
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

		switch(mvinch(direction.y, direction.x) & A_CHARTEXT)
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
	bool occupied = false;
	for (int i = 0; i < n_actors; i++)
	{
		if (actors[i]->entity->position.y == direction.y && actors[i]->entity->position.x == direction.x)
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

void monsterAttack(Fighter* monster, Fighter* target)
{
	char* text;

	switch(rand() % 3)
	{
		case 0:
			text = "The goblin is beating your ankle with a chicken bone!";
			break;
		case 1:
			text = "The goblin is throwing boogers at you!";
			break;
		case 2:
			text = "A goblin is trying to sell you a counterfeit Rolex!";
			break;
		default:
			text = "The goblin is asking if you've seen his grandmother!";
			break;
	}

	addMessage(text);
}





