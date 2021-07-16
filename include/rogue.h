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
#define CYAN_COLOR 7
#define FIRE_COLOR 8

// draw order
#define CORPSE 0
#define ITEM 1
#define ACTOR 2



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




// global constants
extern const int GAMEMAP_HEIGHT;
extern const int GAMEMAP_WIDTH;
extern const int MAX_MONSTERS;

// global variables
extern Actor* player;
extern Tile** level;
extern List* actors;
extern List* items;
extern Message** message_log;
extern int message_count;
extern int dungeon_level;
extern Position down_stairs;
extern Position up_stairs;
extern MonsterTemplate goblin;
extern MonsterTemplate orc;
extern MonsterTemplate troll;
extern ItemTemplate health_potion;
extern ItemTemplate mana_potion;
extern ItemTemplate lightning_scroll;
extern ItemTemplate fireball_scroll;
extern ItemTemplate short_sword;
extern ItemTemplate small_shield;
extern ItemTemplate light_helm;

// main.c functions
bool screenSetUp(void);
bool intro(void);
void wonGame(void);
void lostGame(void);
bool checkVictory(void);

// level.c functions 
Room** mapSetUp(void);
void addDownStairs(Position* center);
void addUpStairs(Position* center);
Tile** createLevelTiles(void);
void clearLevel(void);
void createNewLevel(void);

// player.c functions
Actor* playerSetUp(Room* room);
Position* handleInput(int input, Entity* player);
void checkPosition(Position* newPosition, Entity* player);
void playerMove(Position* newPosition, Entity* player);
Position* goDownStairs(Entity* player);
Position* goUpStairs(Entity* player);
void grabItem(Entity* player);
void gainXP(Fighter* player, int amount);
void levelUp(Fighter* player);

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
bool useHealthPotion(Item* self, Actor* drinker);
bool useManaPotion(Item* self, Actor* drinker);
bool castLightning(Item* self, Actor* caster);
bool castFireball(Item* self, Actor* caster);
void consumeItem(Inventory* inventory, int index);
bool equipItem(Item* self, Actor* equiper);
void unequipItem(Item* equipment, Actor* actor);

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
void appendItem(List* head, Item* item);
void appendActor(List* head, Actor* actor);
void removeItem(List* head, Item* item, bool cleanUp);
void removeActor(List* head, Actor* actor, bool cleanUp);
void freeActor(Actor* actor);
void freeItem(Item* item);

// save_load.c functions
void saveGame(void);
bool loadGame(void);


#endif
