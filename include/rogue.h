#ifndef ROGUE_H
#define ROGUE_H
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

// color pairs
#define BLACK_COLOR 0
#define PLAYER_COLOR 1
#define VISIBLE_COLOR 2
#define SEEN_COLOR 3
#define GREEN_COLOR 4
#define RED_COLOR 5
#define BLUE_COLOR 6

// draw order
#define CORPSE 0
#define ITEM 1
#define ACTOR 2


extern const int GAMEMAP_HEIGHT;
extern const int GAMEMAP_WIDTH;
extern const int MAX_MONSTERS;
extern const int MAX_ITEMS;

struct Actor;
typedef struct Actor Actor;
struct Item;
typedef struct Item Item;
struct Inventory;
typedef struct Inventory Inventory;

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
	int hp;
	int max_hp;
	int attack;
	int defense;
	Actor* owner;
} Fighter;

typedef struct
{
	bool seen_player;
	Position last_player_position;
	Actor* owner;
} AI;

struct Actor
{
	Entity* entity;
	Fighter* fighter;
	AI* ai;
	Inventory* inventory;
	char* name;
	bool dead;
};

struct Item
{
	Entity* entity;
	void (*useFunction)(Item* self, Actor* drinker);
	char* name;
};

struct Inventory
{
	Item* items[10];
	int n_items;
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
	void (*useFunction)(Item* self, Actor* drinker);
	char* name;
} ItemTemplate;

typedef struct
{
	char text[1024];
} Message;

// global variables
extern Tile** level;
extern Actor* actors[];
extern Item* items[];
extern Entity* entities[];
extern int n_actors;
extern int n_items;
extern int n_entities;
extern Message** message_log;
extern int message_count;
extern MonsterTemplate goblin;
extern MonsterTemplate orc;
extern MonsterTemplate troll;
extern ItemTemplate health_potion;
extern ItemTemplate mana_potion;

// main.c functions
bool screenSetUp(void);
void intro(void);
void wonGame(void);
void lostGame(void);
bool checkVictory(void);

// level.c functions 
Room** mapSetUp(void);
Tile** createLevelTiles(void);

// player.c functions
Actor* playerSetUp(Room* room);
Position* handleInput(int input, Entity* player);
void checkPosition(Position* newPosition, Entity* player);
void playerMove(Position* newPosition, Entity* player);
void grabItem(Entity* player);

// monster.c functions
Actor* createMonster(int y, int x, MonsterTemplate template, int xpLevel);

// fighter.c functions
void attack(Fighter* attacker, Fighter* defender);
void takeDamage(Fighter* fighter, int damage);
void drawBlood(Entity* entity);
void die(Fighter* fighter);

// ai.c functions
void takeTurn(Actor* actor, Actor* player);
void allMonstersTakeTurns(Actor* player);
void moveTowards(Actor* actor, Actor* target);
void monsterMove(Position direction, Entity* entity);

// item.c functions
Item* createItem(int y, int x, ItemTemplate template);
void useHealthPotion(Item* self, Actor* drinker);
void useManaPotion(Item* self, Actor* drinker);
void consumeItem(Inventory* inventory, int index);

// inventory.c functions
void useInventory(Inventory* inventory);

// room.c functions
Room* createRoom(int y, int x, int height, int width);
void drawRoom(Room* room);
void connectRoomCenters(Position* centerOne, Position* centerTwo);

// fov.c functions
int getDistance(Position origin, Position target);
void makeFOV(Entity* player);
void clearFOV(Entity* player);
bool isInMap(int y, int x);
bool lineOfSight(Entity* origin, int target_y, int target_x);
int getSign(int a);

// log.c exports
Message** createLog();
void addMessage(char text[1024]);
void printMessages(void);

// ui.c functions
void drawUI(void);

// draw.c functions
void drawEverything(void);
void drawEntity(Entity* entity);
void drawAllEntities(void);
void mapDraw(void);
void showWholeMap(void);

// utils.c functions
int maxInt(int a, int b);
int minInt(int a, int b);
void clrRect(Position a, Position b);


#endif
