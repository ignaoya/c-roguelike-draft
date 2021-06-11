#include <ncurses.h>
#include <stdlib.h>

typedef struct Room
{
	int xPosition;
	int yPosition;
	int height;
	int width;
	//Monster** monsters;
	//Item** items;
} Room;

typedef struct Player
{
	int xPosition;
	int yPosition;
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

int main(void)
{
	Player* user;
	int ch;
	screenSetUp();

	mapSetUp();

	user = playerSetUp();

	/* main game loop */
	while ((ch = getch()) != 'q')
	{
		handleInput(ch, user);
	}

	endwin();

	return 0;
}

void screenSetUp(void)
{
	initscr();
	printw("Hello world!");
	noecho();
	refresh();
}

Room** mapSetUp(void)
{
	Room** rooms;
	rooms = malloc(sizeof(Room) * 6);

	rooms[0] = createRoom(13, 13, 6, 8);
	rooms[1] = createRoom(2, 40, 6, 8);
	rooms[2] = createRoom(10, 40, 6, 12);

	drawRoom(rooms[0]);
	drawRoom(rooms[1]);
	drawRoom(rooms[2]);

	return rooms;
}

Room* createRoom(int y, int x, int height, int width)
{
	Room* newRoom;
	newRoom = malloc(sizeof(Room));

	newRoom->yPosition = y;
	newRoom->xPosition = x;
	newRoom->height = height;
	newRoom->width = width;

	return newRoom;
}

void drawRoom(Room* room)
{
	int y;
	int x;

	// draw top and bottom
	for (x = room->xPosition; x < room->xPosition + room->width; x++)
	{
		mvprintw(room->yPosition, x, "-"); // top
		mvprintw(room->yPosition + room->height - 1, x, "-"); // bottom
	}
	
	// draw floors and side walls
	for (y = room->yPosition + 1; y < room->yPosition + room->height - 1; y++)
	{
		// draw side walls
		mvprintw(y, room->xPosition, "|");
		mvprintw(y, room->xPosition + room->width - 1, "|");

		// draw floors
		for (x = room->xPosition + 1; x < room->xPosition + room->width - 1; x++)
		{
			mvprintw(y, x, ".");
		}
	}
}

Player* playerSetUp(void)
{
	Player* newPlayer; 
	newPlayer = malloc(sizeof(Player));
	newPlayer->xPosition = 14;
	newPlayer->yPosition = 14;
	newPlayer->health = 20;

	playerMove(14, 14, newPlayer);

	return newPlayer;
}

int handleInput(int input, Player* user)
{
	int newY;
	int newX;
	switch (input)
	{
		// move up
		case 'w':
		case 'W':
			newY = user->yPosition - 1;
			newX = user->xPosition;
			break;
		// move down
		case 's':
		case 'S':
			newY = user->yPosition + 1;
			newX = user->xPosition;
			break;
		// move left
		case 'a':
		case 'A':
			newY = user->yPosition;
			newX = user->xPosition - 1;
			break;
		// move right
		case 'd':
		case 'D':
			newY = user->yPosition;
			newX = user->xPosition + 1;
			break;

		default:
			break;
	}

	checkPosition(newY, newX, user);
}

int checkPosition(int newY, int newX, Player* user)
{
	int space;
	switch (mvinch(newY, newX))
	{
		case '.':
			playerMove(newY, newX, user);
			break;
		default:
			move(user->yPosition, user->xPosition);
			break;
	}
}

int playerMove(int y, int x, Player* user)
{
	mvprintw(user->yPosition, user->xPosition, ".");

	user->yPosition = y;
	user->xPosition = x;

	mvprintw(user->yPosition, user->xPosition, "@");
	move(user->yPosition, user->xPosition);
}
