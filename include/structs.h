#ifndef STRUCTS_H
#define STRUCTS_H

struct Actor;
typedef struct Actor Actor;
struct Item;
typedef struct Item Item;
struct Inventory;
typedef struct Inventory Inventory;
struct Equipment;
typedef struct Equipment Equipment;

typedef struct 
{
	int x;
	int y;
} Position;

typedef struct
{
	char ch;
	int color;
	bool walkable;
	bool transparent;
	bool visible;
	bool seen;
} Tile;

typedef struct
{
	Position position;
	int height;
	int width;
	Position* center;
} Room;

typedef struct
{
	Position position;
	char ch;
	int color;
	int draw_order;
	int fov_radius;
	union {
		Actor* owner;
		Item* item;
	};
} Entity;

typedef struct
{
	int level;
	int xp;
	int xp_to_next_level;
	int hp;
	int max_hp;
	int mana;
	int max_mana;
	int attack;
	int defense;
	Actor* owner;
} Fighter;

typedef struct
{
	bool seen_player;
	Position last_player_position;
} AI;

struct Actor
{
	Entity* entity;
	Fighter* fighter;
	AI* ai;
	Inventory* inventory;
	Equipment* equipment;
	char name[64];
	bool dead;
};

struct Item
{
	Entity* entity;
	bool (*useFunction)(Item* self, Actor* user);
	char name[64];
	bool weapon;
	bool shield;
	bool helm;
	int bonus;
};

struct Inventory
{
	Item* items[10];
	int n_items;
};

struct Equipment
{
	Item* weapon;
	Item* shield;
	Item* helm;
};
	
typedef struct
{
	char ch;
	int color;
	int fov_radius;
	int hp;
	int attack;
	int defense;
	char* name;
} MonsterTemplate;

typedef struct
{
	char ch;
	int color;
	bool (*useFunction)(Item* self, Actor* user);
	char name[64];
	bool weapon;
	bool shield;
	bool helm;
	int bonus;
} ItemTemplate;

typedef struct
{
	char text[1024];
} Message;

typedef struct List
{
	union {
		Actor* actor;
		Item* item;
	};
	struct List* next;
} List;

#endif
