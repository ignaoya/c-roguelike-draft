#include "rogue.h"

void takeTurn(Actor* actor, Actor* player)
{
	int distance = getDistance(actor->entity->position, player->entity->position);
	if (distance < actor->entity->fov_radius)
	{
		if (lineOfSight(actor->entity, player->entity->position.y, player->entity->position.x))
		{
			addMessage("The enemy has seen you!");
		}
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


