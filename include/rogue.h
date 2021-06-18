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
Room** mapSetUp(void);
Player* playerSetUp(void);
int handleInput(int input, Player* user);
int playerMove(int y, int x, Player* user);
int checkPosition(int newY, int newX, Player* user);

// room functions
Room* createRoom(int y, int x, int height, int width);
void drawRoom(Room* room);
void connectDoors(Position* doorOne, Position* doorTwo);

#endif