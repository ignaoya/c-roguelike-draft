#ifndef ROGUE_H
#define ROGUE_H
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

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


extern Tile** level;

// main.c functions
void screenSetUp(void);

// level.c functions 
Room** mapSetUp(void);
void mapDraw(void);
void showWholeMap(void);
Tile** createLevelTiles(void);

// player.c functions
Player* playerSetUp(Room* room);
Position* handleInput(int input, Player* user);
int playerMove(Position* newPosition, Player* user);
int checkPosition(Position* newPosition, Player* user);

// room.c functions
Room* createRoom(int y, int x, int height, int width);
void drawRoom(Room* room);
void connectDoors(Position* doorOne, Position* doorTwo);
bool roomIntersectsOther(Room* room, Room* other);

// fov.c functions
void makeFOV(Player* player);
void clearFOV(Player* player);
bool isInMap(int y, int x);

#endif
