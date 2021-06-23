#ifndef ROGUE_H
#define ROGUE_H
#include <ncurses.h>
#include <stdlib.h>
#include <time.h>

typedef struct Position 
{
	int x;
	int y;
} Position;

typedef struct Tile
{
	char ch;
	bool walkable;
	bool transparent;
} Tile;

typedef struct Room
{
	Position position;
	int height;
	int width;
	Position** doors;
	//Monster** monsters;
	//Item** items;
} Room;

typedef struct Player
{
	Position position;
	int health;
} Player;

void screenSetUp(void);

// level/map functions 
Room** mapSetUp(void);
Tile** saveLevelTiles(void);

// player functions
Player* playerSetUp(void);
Position* handleInput(int input, Player* user);
int playerMove(Position* newPosition, Player* user, Tile** level);
int checkPosition(Position* newPosition, Player* user, Tile** level);

// room functions
Room* createRoom(int y, int x, int height, int width);
void drawRoom(Room* room);
void connectDoors(Position* doorOne, Position* doorTwo);

#endif
