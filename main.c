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

int main(void)
{
	srand(time(NULL));
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

	connectDoors(rooms[0]->doors[3], rooms[2]->doors[1]);
	connectDoors(rooms[0]->doors[0], rooms[1]->doors[1]);
	connectDoors(rooms[2]->doors[0], rooms[1]->doors[2]);

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

	newRoom->doors = malloc(sizeof(Position) * 4);


	/* top door */
	newRoom->doors[0] = malloc(sizeof(Position));
	newRoom->doors[0]->x = rand() % (width - 2) + newRoom->position.x + 1;
	newRoom->doors[0]->y = newRoom->position.y;

	/* bottom door */
	newRoom->doors[2] = malloc(sizeof(Position));
	newRoom->doors[2]->x = rand() % (width - 2) + newRoom->position.x + 1;
	newRoom->doors[2]->y = newRoom->position.y + height - 1;

	/* left door */
	newRoom->doors[1] = malloc(sizeof(Position));
	newRoom->doors[1]->x = newRoom->position.x;
	newRoom->doors[1]->y = rand() % (height - 2) + newRoom->position.y + 1;

	/* right door */
	newRoom->doors[3] = malloc(sizeof(Position));
	newRoom->doors[3]->x = newRoom->position.x + width - 1;
	newRoom->doors[3]->y = rand() % (height - 2)  + newRoom->position.y + 1;

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

	/* draw doors */
	for (int i = 0; i < 4; i++)
	{
		mvprintw(room->doors[i]->y, room->doors[i]->x, "+");
	}
}

void connectDoors(Position* doorOne, Position* doorTwo)
{
	Position temp;
	Position previous;
	temp.x = doorOne->x;
	temp.y = doorOne->y;

	previous = temp;

	while (true)
	{
		if ((abs((temp.x - 1) - doorTwo->x) < abs(temp.x - doorTwo->x)) && 
				(mvinch(temp.y, temp.x - 1) == ' ') &&
				abs(temp.x - doorTwo->x) > 1)
		{
			previous.x = temp.x;
			temp.x = temp.x - 1;

		} else if ((abs((temp.x + 1) - doorTwo->x) < abs(temp.x - doorTwo->x)) && 
				       (mvinch(temp.y, temp.x + 1) == ' ') &&
							 abs(temp.x - doorTwo->x) > 1) 
		{
			previous.x = temp.x;
			temp.x = temp.x + 1;

		} else if ((abs((temp.y + 1) - doorTwo->y) < abs(temp.y - doorTwo->y)) && 
				       (mvinch(temp.y + 1, temp.x) == ' ') &&
							 abs(temp.y - doorTwo->y) > 1) 
		{
			previous.y = temp.y;
			temp.y = temp.y + 1;

		} else if ((abs((temp.y - 1) - doorTwo->y) < abs(temp.y - doorTwo->y)) && 
				       (mvinch(temp.y - 1, temp.x) == ' ') &&
							 abs(temp.y - doorTwo->y) > 1) 
		{
			previous.y = temp.y;
			temp.y = temp.y - 1;
		} else
		{
			if (previous.x < temp.x && mvinch(temp.y, temp.x + 1) == ' ')
				mvprintw(temp.y, temp.x + 1, "#");
			else if (previous.x > temp.x && mvinch(temp.y, temp.x - 1) == ' ')
				mvprintw(temp.y, temp.x - 1, "#");
			else if (previous.y < temp.y && mvinch(temp.y + 1, temp.x) == ' ')
				mvprintw(temp.y + 1, temp.x, "#");
			else if (previous.y > temp.y && mvinch(temp.y - 1, temp.x) == ' ')
				mvprintw(temp.y - 1, temp.x, "#");
			break;
		}
		mvprintw(temp.y, temp.x, "#");
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
		case '+':
		case '#':
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
