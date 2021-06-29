#ifndef ROGUE_H
#define ROGUE_H
#include <ncurses.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

#define BLACK_COLOR 0
#define PLAYER_COLOR 1
#define VISIBLE_COLOR 2
#define SEEN_COLOR 3

extern const int GAMEMAP_HEIGHT;
extern const int GAMEMAP_WIDTH;

typedef struct Position 
{
	int x;
	int y;
} Position;

typedef struct Tile
{
	char* ch;
	bool walkable;
	bool transparent;
	bool visible;
	bool seen;
} Tile;

typedef struct Room
{
	Position position;
	int height;
	int width;
	Position* center;
} Room;

typedef struct Entity
{
	Position position;
	char ch;
	int fov_radius;
} Entity;

typedef struct Fighter
{
	int hp;
	int max_hp;
	int attack;
	int defense;
	bool ai;
} Fighter;

typedef struct Actor
{
	Entity* entity;
	Fighter* fighter;
	char* name;
} Actor;
	
typedef struct MonsterTemplate
{
	char ch;
	int fov_radius;
	int hp;
	int attack;
	int defense;
	bool ai;
	char* name;
} MonsterTemplate;

// global variables
extern Tile** level;
extern Actor* actors[];
extern int n_actors;
extern MonsterTemplate goblin;

// main.c functions
bool screenSetUp(void);

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

// ai.c functions
void takeTurn(Actor* actor, Actor* player);
void allMonstersTakeTurns(Actor* player);

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
void addMessage(char* text);
void printMessages(void);


#endif
