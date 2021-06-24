#ifndef ROGUE_H
#define ROGUE_H
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

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
} Tile;

typedef struct Room
{
	Position position;
	int height;
	int width;
	Position* center;
	//Monster** monsters;
	//Item** items;
} Room;

typedef struct Player
{
	Position position;
	int health;
} Player;

// main.c functions
void screenSetUp(void);

// level.c functions 
Room** mapSetUp(Tile** level);
void mapDraw(Tile** level);
Tile** createLevelTiles(void);

// player.c functions
Player* playerSetUp(Room* room);
Position* handleInput(int input, Player* user);
int playerMove(Position* newPosition, Player* user, Tile** level);
int checkPosition(Position* newPosition, Player* user, Tile** level);

// room.c functions
Room* createRoom(int y, int x, int height, int width);
void drawRoom(Room* room, Tile** level);
void connectDoors(Position* doorOne, Position* doorTwo, Tile** level);

// fov.c functions
void makeFOV(Tile** level, Player* player);
void clearFOV(Tile** level, Player* player);
bool isInMap(int y, int x);

#endif
