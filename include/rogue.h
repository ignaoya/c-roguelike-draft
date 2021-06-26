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

typedef struct Player
{
	Position position;
	char ch;
	int health;
} Player;


extern Tile** level;

// main.c functions
bool screenSetUp(void);

// level.c functions 
Room** mapSetUp(void);
void mapDraw(void);
void showWholeMap(void);
Tile** createLevelTiles(void);

// player.c functions
Player* playerSetUp(Room* room);
Position* handleInput(int input, Player* player);
void checkPosition(Position* newPosition, Player* player);
void playerMove(Position* newPosition, Player* player);
void playerDraw(Player* player);

// room.c functions
Room* createRoom(int y, int x, int height, int width);
void drawRoom(Room* room);
void connectRoomCenters(Position* centerOne, Position* centerTwo);
bool roomIntersectsOther(Room* room, Room* other);

// fov.c functions
void makeFOV(Player* player);
void clearFOV(Player* player);
bool isInMap(int y, int x);

#endif
