#include "rogue.h"

void saveGame(void)
{
	FILE* outfile;
	List* temp;
	int eraser = 0;
	bool hasEquipment;
	int n_items;
	int n_actors;
	int message_count = 4;


	outfile = fopen("save/game.sav", "wb");
	if (outfile == NULL)
	{
		fprintf(stderr, "\nError opening file\n");
		exit(1);
	}

	// overwrite anything previously written in a pre-existing save file
	fwrite(&eraser, sizeof(int), 1, outfile);
	fclose(outfile);

	outfile = fopen("save/game.sav", "ab");
	if (outfile == NULL)
	{
		fprintf(stderr, "\nError opening file\n");
		exit(1);
	}

	fwrite(&dungeon_level, sizeof(int), 1, outfile);

	fwrite(&down_stairs, sizeof(Position), 1, outfile);

	for (int y = 0; y < MAP_HEIGHT; y++)
	{
		for (int x = 0; x < MAP_WIDTH; x++)
		{
			fwrite(&(map[y][x]), sizeof(Tile), 1, outfile);
		}
	}

	n_items = 0;
	temp = items;
	while (temp = temp->next)
	{
		n_items++;
	}
	fwrite(&n_items, sizeof(int), 1, outfile);
	
	temp = items;
	while (temp = temp->next)
	{
		fwrite(temp->item, sizeof(Item), 1, outfile);
		fwrite(temp->item->entity, sizeof(Entity), 1, outfile);
		fwrite(temp->item->name, sizeof(char) * 64, 1, outfile);
	}

	n_actors = 0;
	temp = actors;
	while (temp = temp->next)
	{
		n_actors++;
	}
	fwrite(&n_actors, sizeof(int), 1, outfile);

	temp = actors;
	while (temp = temp->next)
	{
		fwrite(temp->actor->entity, sizeof(Entity), 1, outfile);
		fwrite(temp->actor->fighter, sizeof(Fighter), 1, outfile);
		fwrite(temp->actor->ai, sizeof(AI), 1, outfile);
		//fwrite(temp->actor->inventory, sizeof(Inventory), 1, outfile);
		fwrite(temp->actor->name, sizeof(char) * 64, 1, outfile);
		fwrite(&(temp->actor->dead), sizeof(bool), 1, outfile);
	}

	fwrite(&(player->inventory->n_items), sizeof(int), 1, outfile);
	for (int i = 0; i < player->inventory->n_items; i++)
	{
		fwrite(player->inventory->items[i], sizeof(Item), 1, outfile);
		fwrite(player->inventory->items[i]->entity, sizeof(Entity), 1, outfile);
		fwrite(player->inventory->items[i]->name, sizeof(char) * 64, 1, outfile);
	}

	if (player->equipment->weapon)
	{
		hasEquipment = true;
		fwrite(&hasEquipment, sizeof(bool), 1, outfile);
		fwrite(player->equipment->weapon, sizeof(Item), 1, outfile);
		fwrite(player->equipment->weapon->entity, sizeof(Entity), 1, outfile);
		fwrite(player->equipment->weapon->name, sizeof(char) * 64, 1, outfile);
	}
	else
	{
		hasEquipment = false;
		fwrite(&hasEquipment, sizeof(bool), 1, outfile);
	}

	if (player->equipment->shield)
	{
		hasEquipment = true;
		fwrite(&hasEquipment, sizeof(bool), 1, outfile);
		fwrite(player->equipment->shield, sizeof(Item), 1, outfile);
		fwrite(player->equipment->shield->entity, sizeof(Entity), 1, outfile);
		fwrite(player->equipment->shield->name, sizeof(char) * 64, 1, outfile);
	}
	else
	{
		hasEquipment = false;
		fwrite(&hasEquipment, sizeof(bool), 1, outfile);
	}

	if (player->equipment->helm)
	{
		hasEquipment = true;
		fwrite(&hasEquipment, sizeof(bool), 1, outfile);
		fwrite(player->equipment->helm, sizeof(Item), 1, outfile);
		fwrite(player->equipment->helm->entity, sizeof(Entity), 1, outfile);
		fwrite(player->equipment->helm->name, sizeof(char) * 64, 1, outfile);
	}
	else
	{
		hasEquipment = false;
		fwrite(&hasEquipment, sizeof(bool), 1, outfile);
	}

	fwrite(&message_count, sizeof(int), 1, outfile);

	for (int i = message_count - 1 ; i >= 0; i--)
	{
		fwrite(message_log[i].text, sizeof(char) * 1024, 1, outfile);
	}

	fclose(outfile);

	clear();
	mvprintw(20, 60, "Saved successfully!");
	getch();
}

bool loadGame(void)
{
	FILE * infile;
	List* temp;
	int eraserCatcher;
	bool hasEquipment;
	int n_items;
	int n_actors;
	int message_count;

	infile = fopen("save/game.sav", "rb");
	if (infile == NULL)
	{
		clear();
		mvprintw(20, 60, "Couldn't load!");
		getch();
		return false;
	}

	fread(&eraserCatcher, sizeof(int), 1, infile);

	fread(&dungeon_level, sizeof(int), 1, infile);

	fread(&down_stairs, sizeof(Position), 1, infile);

	map = calloc(MAP_HEIGHT, sizeof(Tile*));
	for (int y = 0; y < MAP_HEIGHT; y++)
	{
		map[y] = calloc(MAP_WIDTH, sizeof(Tile));
		for (int x = 0; x < MAP_WIDTH; x++)
		{
			fread(&(map[y][x]), sizeof(Tile), 1, infile);
		}
	}

	fread(&n_items, sizeof(int), 1, infile);
	for (int i = 0; i < n_items; i++)
	{
		Item* item = calloc(1, sizeof(Item));
		fread(item, sizeof(Item), 1, infile);
		item->entity = calloc(1, sizeof(Entity));
		fread(item->entity, sizeof(Entity), 1, infile);
		fread(item->name, sizeof(char) * 64, 1, infile);
		item->entity->item = item;

		if (!strcmp(item->name, "Life Potion"))
		{
			item->useFunction = useHealthPotion;
		}
		else if (!strcmp(item->name, "Mana Potion"))
		{
			item->useFunction = useManaPotion;
		}
		else if (!strcmp(item->name, "Bolt Scroll"))
		{
			item->useFunction = castLightning;
		}
		else if (!strcmp(item->name, "Fire Scroll"))
		{
			item->useFunction = castFireball;
		}
		else
		{
			item->useFunction = equipItem;
		}

		appendItem(items, item);
	}

	fread(&n_actors, sizeof(int), 1, infile);
	for (int i = 0; i < n_actors; i++)
	{
		Actor* actor = calloc(1, sizeof(Actor));
		actor->entity = calloc(1, sizeof(Entity));
		actor->fighter = calloc(1, sizeof(Fighter));
		actor->ai = calloc(1, sizeof(AI));
		actor->inventory = calloc(1, sizeof(Inventory));
		actor->equipment = calloc(1, sizeof(Equipment));

		fread(actor->entity, sizeof(Entity), 1, infile);
		fread(actor->fighter, sizeof(Fighter), 1, infile);
		fread(actor->ai, sizeof(AI), 1, infile);
		//fread(actor->inventory, sizeof(Inventory), 1, infile);
		fread(actor->name, sizeof(char) * 64, 1, infile);
		fread(&(actor->dead), sizeof(bool), 1, infile);

		actor->entity->owner = actor;
		actor->fighter->owner = actor;

		actor->equipment->weapon = NULL;
		actor->equipment->shield = NULL;
		actor->equipment->helm = NULL;

		if (i == n_actors - 1)
		{
			player = actor;
		}

		if (actor->entity->ch == 'B')
		{
			boss = actor;
		}

		appendActor(actors, actor);
	}
	
	fread(&(player->inventory->n_items), sizeof(int), 1, infile);
	for (int i = 0; i < player->inventory->n_items; i++)
	{
		player->inventory->items[i] = calloc(1, sizeof(Item));
		fread(player->inventory->items[i], sizeof(Item), 1, infile);
		player->inventory->items[i]->entity = calloc(1, sizeof(Entity));
		fread(player->inventory->items[i]->entity, sizeof(Entity), 1, infile);
		fread(player->inventory->items[i]->name, sizeof(char) * 64, 1, infile);
		player->inventory->items[i]->entity->item = player->inventory->items[i];

		if (!strcmp(player->inventory->items[i]->name, "Life Potion"))
		{
			player->inventory->items[i]->useFunction = useHealthPotion;
		}
		else if (!strcmp(player->inventory->items[i]->name, "Mana Potion"))
		{
			player->inventory->items[i]->useFunction = useManaPotion;
		}
		else if (!strcmp(player->inventory->items[i]->name, "Bolt Scroll"))
		{
			player->inventory->items[i]->useFunction = castLightning;
		}
		else if (!strcmp(player->inventory->items[i]->name, "Fire Scroll"))
		{
			player->inventory->items[i]->useFunction = castFireball;
		}
		else
		{
			player->inventory->items[i]->useFunction = equipItem;
		}
	}

	fread(&hasEquipment, sizeof(bool), 1, infile);
	if (hasEquipment)
	{
		player->equipment->weapon = calloc(1, sizeof(Item));
		fread(player->equipment->weapon, sizeof(Item), 1, infile);
		player->equipment->weapon->entity = calloc(1, sizeof(Entity));
		fread(player->equipment->weapon->entity, sizeof(Entity), 1, infile);
		fread(player->equipment->weapon->name, sizeof(char) * 64, 1, infile);
		player->equipment->weapon->entity->item = player->equipment->weapon;
		player->equipment->weapon->useFunction = equipItem;
	}
	else
	{
		player->equipment->weapon = NULL;
	}

	fread(&hasEquipment, sizeof(bool), 1, infile);
	if (hasEquipment)
	{
		player->equipment->shield = calloc(1, sizeof(Item));
		fread(player->equipment->shield, sizeof(Item), 1, infile);
		player->equipment->shield->entity = calloc(1, sizeof(Entity));
		fread(player->equipment->shield->entity, sizeof(Entity), 1, infile);
		fread(player->equipment->shield->name, sizeof(char) * 64, 1, infile);
		player->equipment->shield->entity->item = player->equipment->shield;
		player->equipment->shield->useFunction = equipItem;
	}
	else
	{
		player->equipment->shield = NULL;
	}
	
	fread(&hasEquipment, sizeof(bool), 1, infile);
	if (hasEquipment)
	{
		player->equipment->helm = calloc(1, sizeof(Item));
		fread(player->equipment->helm, sizeof(Item), 1, infile);
		player->equipment->helm->entity = calloc(1, sizeof(Entity));
		fread(player->equipment->helm->entity, sizeof(Entity), 1, infile);
		fread(player->equipment->helm->name, sizeof(char) * 64, 1, infile);
		player->equipment->helm->entity->item = player->equipment->helm;
		player->equipment->helm->useFunction = equipItem;
	}
	else
	{
		player->equipment->helm = NULL;
	}

	fread(&message_count, sizeof(int), 1, infile);
	message_log = createLog();
	for (int i = 0; i < message_count; i++)
	{
		char text[1024];
		fread(text, sizeof(char) * 1024, 1, infile);
		addMessage(text);
	}

	fclose(infile);
	return true;
}
