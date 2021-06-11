#include <ncurses.h>
#include <stdlib.h>

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

	newRoom->position.y = y;
	newRoom->position.x = x;
	newRoom->height = height;
	newRoom->width = width;

	return newRoom;
}

void drawRoom(Room* room)
{
	int y;
	int x;

	// draw top and bottom
	for (x = room->position.x; x < room->position.x + room->width; x++)
	{
		mvprintw(room->position.y, x, "-"); // top
		mvprintw(room->position.y + room->height - 1, x, "-"); // bottom
	}
	
	// draw floors and side walls
	for (y = room->position.y + 1; y < room->position.y + room->height - 1; y++)
	{
		// draw side walls
		mvprintw(y, room->position.x, "|");
		mvprintw(y, room->position.x + room->width - 1, "|");

		// draw floors
		for (x = room->position.x + 1; x < room->position.x + room->width - 1; x++)
		{
			mvprintw(y, x, ".");
		}
	}
}

Player* playerSetUp(void)
{
	Player* newPlayer; 
	newPlayer = malloc(sizeof(Player));
	newPlayer->position.x = 14;
	newPlayer->position.y = 14;
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
			newY = user->position.y - 1;
			newX = user->position.x;
			break;
		// move down
		case 's':
		case 'S':
			newY = user->position.y + 1;
			newX = user->position.x;
			break;
		// move left
		case 'a':
		case 'A':
			newY = user->position.y;
			newX = user->position.x - 1;
			break;
		// move right
		case 'd':
		case 'D':
			newY = user->position.y;
			newX = user->position.x + 1;
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
			move(user->position.y, user->position.x);
			break;
	}
}

int playerMove(int y, int x, Player* user)
{
	mvprintw(user->position.y, user->position.x, ".");

	user->position.y = y;
	user->position.x = x;

	mvprintw(user->position.y, user->position.x, "@");
	move(user->position.y, user->position.x);
}
