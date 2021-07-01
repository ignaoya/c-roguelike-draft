#ifndef ROGUE_H
#define ROGUE_H
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

#define BLACK_COLOR 0
#define PLAYER_COLOR 1
#define VISIBLE_COLOR 2
#define SEEN_COLOR 3
#define GREEN_COLOR 4
#define RED_COLOR 5

extern const int GAMEMAP_HEIGHT;
extern const int GAMEMAP_WIDTH;

struct Actor;
typedef struct Actor Actor;


typedef struct 
{
	int x;
	int y;
} Position;

typedef struct
{
	char* ch;
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
	int fov_radius;
	Actor* owner;
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
	char* name;
	bool dead;
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
	char text[1024];
} Message;

// global variables
extern Tile** level;
extern Actor* actors[];
extern int n_actors;
extern Message** message_log;
extern int message_count;
extern MonsterTemplate goblin;
extern MonsterTemplate orc;
extern MonsterTemplate troll;

// main.c functions
bool screenSetUp(void);
void intro(void);
void wonGame(void);
void lostGame(void);
bool checkVictory(void);

// level.c functions 
Room** mapSetUp(void);
void mapDraw(void);
void showWholeMap(void);
Tile** createLevelTiles(void);

// player.c functions
Actor* playerSetUp(Room* room);
Position* handleInput(int input, Entity* player);
void checkPosition(Position* newPosition, Entity* player);
void playerMove(Position* newPosition, Entity* player);
void playerDraw(Entity* player);

// monster.c functions
Actor* createMonster(int y, int x, MonsterTemplate template, int xpLevel);
void drawEntity(Entity* entity);
void drawAllMonsters(void);

// fighter.c functions
void attack(Fighter* attacker, Fighter* defender);
void takeDamage(Fighter* fighter, int damage);
void die(Fighter* fighter);

// ai.c functions
void takeTurn(Actor* actor, Actor* player);
void allMonstersTakeTurns(Actor* player);
void moveTowards(Actor* actor, Actor* target);
void monsterMove(Position direction, Entity* entity);

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

// utils.c functions
int maxInt(int a, int b);
int minInt(int a, int b);


#endif
