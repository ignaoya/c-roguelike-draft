#include "rogue.h"

void saveGame(void)
{
	FILE* outfile;
	List* temp;
	int eraser = 0;
	bool hasEquipment;


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

	for (int y = 0; y < GAMEMAP_HEIGHT; y++)
	{
		for (int x = 0; x < GAMEMAP_WIDTH; x++)
		{
			fwrite(&(level[y][x]), sizeof(Tile), 1, outfile);
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

	fwrite(&n_actors, sizeof(int), 1, outfile);

	for (int i = 0; i <= n_actors; i++)
	{
		fwrite(actors[i]->entity, sizeof(Entity), 1, outfile);
		fwrite(actors[i]->fighter, sizeof(Fighter), 1, outfile);
		fwrite(actors[i]->ai, sizeof(AI), 1, outfile);
		//fwrite(actors[i]->inventory, sizeof(Inventory), 1, outfile);
		fwrite(actors[i]->name, sizeof(char) * 64, 1, outfile);
		fwrite(&(actors[i]->dead), sizeof(bool), 1, outfile);
	}

	fwrite(&(actors[n_actors]->inventory->n_items), sizeof(int), 1, outfile);
	for (int i = 0; i < actors[n_actors]->inventory->n_items; i++)
	{
		fwrite(actors[n_actors]->inventory->items[i], sizeof(Item), 1, outfile);
		fwrite(actors[n_actors]->inventory->items[i]->entity, sizeof(Entity), 1, outfile);
		fwrite(actors[n_actors]->inventory->items[i]->name, sizeof(char) * 64, 1, outfile);
	}

	if (actors[n_actors]->equipment->weapon)
	{
		hasEquipment = true;
		fwrite(&hasEquipment, sizeof(bool), 1, outfile);
		fwrite(actors[n_actors]->equipment->weapon, sizeof(Item), 1, outfile);
		fwrite(actors[n_actors]->equipment->weapon->entity, sizeof(Entity), 1, outfile);
		fwrite(actors[n_actors]->equipment->weapon->name, sizeof(char) * 64, 1, outfile);
	}
	else
	{
		hasEquipment = false;
		fwrite(&hasEquipment, sizeof(bool), 1, outfile);
	}

	if (actors[n_actors]->equipment->shield)
	{
		hasEquipment = true;
		fwrite(&hasEquipment, sizeof(bool), 1, outfile);
		fwrite(actors[n_actors]->equipment->shield, sizeof(Item), 1, outfile);
		fwrite(actors[n_actors]->equipment->shield->entity, sizeof(Entity), 1, outfile);
		fwrite(actors[n_actors]->equipment->shield->name, sizeof(char) * 64, 1, outfile);
	}
	else
	{
		hasEquipment = false;
		fwrite(&hasEquipment, sizeof(bool), 1, outfile);
	}

	if (actors[n_actors]->equipment->armor)
	{
		hasEquipment = true;
		fwrite(&hasEquipment, sizeof(bool), 1, outfile);
		fwrite(actors[n_actors]->equipment->armor, sizeof(Item), 1, outfile);
		fwrite(actors[n_actors]->equipment->armor->entity, sizeof(Entity), 1, outfile);
		fwrite(actors[n_actors]->equipment->armor->name, sizeof(char) * 64, 1, outfile);
	}
	else
	{
		hasEquipment = false;
		fwrite(&hasEquipment, sizeof(bool), 1, outfile);
	}
	
	if (actors[n_actors]->equipment->helm)
	{
		hasEquipment = true;
		fwrite(&hasEquipment, sizeof(bool), 1, outfile);
		fwrite(actors[n_actors]->equipment->helm, sizeof(Item), 1, outfile);
		fwrite(actors[n_actors]->equipment->helm->entity, sizeof(Entity), 1, outfile);
		fwrite(actors[n_actors]->equipment->helm->name, sizeof(char) * 64, 1, outfile);
	}
	else
	{
		hasEquipment = false;
		fwrite(&hasEquipment, sizeof(bool), 1, outfile);
	}

	if (actors[n_actors]->equipment->boots)
	{
		hasEquipment = true;
		fwrite(&hasEquipment, sizeof(bool), 1, outfile);
		fwrite(actors[n_actors]->equipment->boots, sizeof(Item), 1, outfile);
		fwrite(actors[n_actors]->equipment->boots->entity, sizeof(Entity), 1, outfile);
		fwrite(actors[n_actors]->equipment->boots->name, sizeof(char) * 64, 1, outfile);
	}
	else
	{
		hasEquipment = false;
		fwrite(&hasEquipment, sizeof(bool), 1, outfile);
	}


	fwrite(&message_count, sizeof(int), 1, outfile);

	for (int i = message_count - 1 ; i >= 0; i--)
	{
		fwrite(message_log[i]->text, sizeof(char) * 1024, 1, outfile);
	}

	fclose(outfile);

	if(fwrite != 0)
	{
		clear();
		mvprintw(20, 60, "Saved succesfully!");
		getch();
	}
	else
	{
		clear();
		mvprintw(20, 60, "Error saving!");
		getch();
	}
}

bool loadGame(void)
{
	FILE * infile;
	List* temp;
	int eraserCatcher;
	bool hasEquipment;

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

	level = malloc(sizeof(Tile*) * GAMEMAP_HEIGHT);
	for (int y = 0; y < GAMEMAP_HEIGHT; y++)
	{
		level[y] = malloc(sizeof(Tile) * GAMEMAP_WIDTH);
		for (int x = 0; x < GAMEMAP_WIDTH; x++)
		{
			fread(&(level[y][x]), sizeof(Tile), 1, infile);
		}
	}

	fread(&n_items, sizeof(int), 1, infile);
	for (int i = 0; i < n_items; i++)
	{
		Item* item = malloc(sizeof(Item));
		fread(item, sizeof(Item), 1, infile);
		item->entity = malloc(sizeof(Entity));
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
	for (int i = 0; i <= n_actors; i++)
	{
		actors[i] = malloc(sizeof(Actor));
		actors[i]->entity = malloc(sizeof(Entity));
		actors[i]->fighter = malloc(sizeof(Fighter));
		actors[i]->ai = malloc(sizeof(AI));
		actors[i]->inventory = malloc(sizeof(Inventory));
		actors[i]->equipment = malloc(sizeof(Equipment));

		fread(actors[i]->entity, sizeof(Entity), 1, infile);
		fread(actors[i]->fighter, sizeof(Fighter), 1, infile);
		fread(actors[i]->ai, sizeof(AI), 1, infile);
		//fread(actors[i]->inventory, sizeof(Inventory), 1, infile);
		fread(actors[i]->name, sizeof(char) * 64, 1, infile);
		fread(&(actors[i]->dead), sizeof(bool), 1, infile);

		actors[i]->entity->owner = actors[i];
		actors[i]->fighter->owner = actors[i];

		actors[i]->equipment->weapon = NULL;
		actors[i]->equipment->shield = NULL;
		actors[i]->equipment->armor = NULL;
		actors[i]->equipment->helm = NULL;
		actors[i]->equipment->boots = NULL;
	}
	
	fread(&(actors[n_actors]->inventory->n_items), sizeof(int), 1, infile);
	for (int i = 0; i < actors[n_actors]->inventory->n_items; i++)
	{
		actors[n_actors]->inventory->items[i] = malloc(sizeof(Item));
		fread(actors[n_actors]->inventory->items[i], sizeof(Item), 1, infile);
		actors[n_actors]->inventory->items[i]->entity = malloc(sizeof(Entity));
		fread(actors[n_actors]->inventory->items[i]->entity, sizeof(Entity), 1, infile);
		fread(actors[n_actors]->inventory->items[i]->name, sizeof(char) * 64, 1, infile);
		actors[n_actors]->inventory->items[i]->entity->item = actors[n_actors]->inventory->items[i];

		if (!strcmp(actors[n_actors]->inventory->items[i]->name, "Life Potion"))
		{
			actors[n_actors]->inventory->items[i]->useFunction = useHealthPotion;
		}
		else if (!strcmp(actors[n_actors]->inventory->items[i]->name, "Mana Potion"))
		{
			actors[n_actors]->inventory->items[i]->useFunction = useManaPotion;
		}
		else if (!strcmp(actors[n_actors]->inventory->items[i]->name, "Bolt Scroll"))
		{
			actors[n_actors]->inventory->items[i]->useFunction = castLightning;
		}
		else if (!strcmp(actors[n_actors]->inventory->items[i]->name, "Fire Scroll"))
		{
			actors[n_actors]->inventory->items[i]->useFunction = castFireball;
		}
		else
		{
			actors[n_actors]->inventory->items[i]->useFunction = equipItem;
		}
	}

	fread(&hasEquipment, sizeof(bool), 1, infile);
	if (hasEquipment)
	{
		actors[n_actors]->equipment->weapon = malloc(sizeof(Item));
		fread(actors[n_actors]->equipment->weapon, sizeof(Item), 1, infile);
		actors[n_actors]->equipment->weapon->entity = malloc(sizeof(Entity));
		fread(actors[n_actors]->equipment->weapon->entity, sizeof(Entity), 1, infile);
		fread(actors[n_actors]->equipment->weapon->name, sizeof(char) * 64, 1, infile);
		actors[n_actors]->equipment->weapon->entity->item = actors[n_actors]->equipment->weapon;
		actors[n_actors]->equipment->weapon->useFunction = equipItem;
	}
	else
	{
		actors[n_actors]->equipment->weapon = NULL;
	}

	fread(&hasEquipment, sizeof(bool), 1, infile);
	if (hasEquipment)
	{
		actors[n_actors]->equipment->shield = malloc(sizeof(Item));
		fread(actors[n_actors]->equipment->shield, sizeof(Item), 1, infile);
		actors[n_actors]->equipment->shield->entity = malloc(sizeof(Entity));
		fread(actors[n_actors]->equipment->shield->entity, sizeof(Entity), 1, infile);
		fread(actors[n_actors]->equipment->shield->name, sizeof(char) * 64, 1, infile);
		actors[n_actors]->equipment->shield->entity->item = actors[n_actors]->equipment->shield;
		actors[n_actors]->equipment->shield->useFunction = equipItem;
	}
	else
	{
		actors[n_actors]->equipment->shield = NULL;
	}

	fread(&hasEquipment, sizeof(bool), 1, infile);
	if (hasEquipment)
	{
		actors[n_actors]->equipment->armor = malloc(sizeof(Item));
		fread(actors[n_actors]->equipment->armor, sizeof(Item), 1, infile);
		actors[n_actors]->equipment->armor->entity = malloc(sizeof(Entity));
		fread(actors[n_actors]->equipment->armor->entity, sizeof(Entity), 1, infile);
		fread(actors[n_actors]->equipment->armor->name, sizeof(char) * 64, 1, infile);
		actors[n_actors]->equipment->armor->entity->item = actors[n_actors]->equipment->armor;
		actors[n_actors]->equipment->armor->useFunction = equipItem;
	}
	else
	{
		actors[n_actors]->equipment->armor = NULL;
	}
	
	fread(&hasEquipment, sizeof(bool), 1, infile);
	if (hasEquipment)
	{
		actors[n_actors]->equipment->helm = malloc(sizeof(Item));
		fread(actors[n_actors]->equipment->helm, sizeof(Item), 1, infile);
		actors[n_actors]->equipment->helm->entity = malloc(sizeof(Entity));
		fread(actors[n_actors]->equipment->helm->entity, sizeof(Entity), 1, infile);
		fread(actors[n_actors]->equipment->helm->name, sizeof(char) * 64, 1, infile);
		actors[n_actors]->equipment->helm->entity->item = actors[n_actors]->equipment->helm;
		actors[n_actors]->equipment->helm->useFunction = equipItem;
	}
	else
	{
		actors[n_actors]->equipment->helm = NULL;
	}

	fread(&hasEquipment, sizeof(bool), 1, infile);
	if (hasEquipment)
	{
		actors[n_actors]->equipment->boots = malloc(sizeof(Item));
		fread(actors[n_actors]->equipment->boots, sizeof(Item), 1, infile);
		actors[n_actors]->equipment->boots->entity = malloc(sizeof(Entity));
		fread(actors[n_actors]->equipment->boots->entity, sizeof(Entity), 1, infile);
		fread(actors[n_actors]->equipment->boots->name, sizeof(char) * 64, 1, infile);
		actors[n_actors]->equipment->boots->entity->item = actors[n_actors]->equipment->boots;
		actors[n_actors]->equipment->boots->useFunction = equipItem;
	}
	else
	{
		actors[n_actors]->equipment->boots = NULL;
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
