#ifndef FUNCTIONS_H
#define FUNCTIONS_H

// engine.c functions
void initLists(void);
void initDungeon(void);
void gameLoop(void);
void closeGame(void);
bool screenSetUp(void);
bool intro(void);
void wonGame(void);
void lostGame(void);
bool checkVictory(void);

// level.c functions 
Tile** createMapTiles(void);
Position* mapSetUp(void);
void addMonsterToRoom(Room* room);
void addItemToRoom(Room* room);
void addDownStairs(Position* center);
void addUpStairs(Position* center);
void clearLevel(void);
void createNewLevel(void);

// player.c functions
Actor* playerSetUp(Position* start_pos);
Position* handleInput(int input);
void playerCheckPosition(Position* newPosition);
void playerMove(Position* newPosition);
Position* goDownStairs(void);
Position* goUpStairs(void);
void grabItem(void);

// monster.c functions
Actor* createMonster(int y, int x, MonsterTemplate template, int xpLevel);

// fighter.c functions
void attack(Fighter* attacker, Fighter* defender);
void takeDamage(Fighter* fighter, int damage);
void spillBlood(Entity* entity);
void die(Fighter* fighter);
void gainXP(Fighter* fighter, int amount);
void levelUp(Fighter* fighter);

// ai.c functions
void takeTurn(Actor* actor);
void allMonstersTakeTurns(void);
void monsterCheckDirection(Actor* monster, Position target);
void monsterMove(Position direction, Entity* entity);

// item.c functions
Item* createItem(int y, int x, ItemTemplate template);
bool useHealthPotion(Item* self, Actor* drinker);
bool useManaPotion(Item* self, Actor* drinker);
bool castLightning(Item* self, Actor* caster);
bool castFireball(Item* self, Actor* caster);
void consumeItem(Inventory* inventory, int index);
bool equipItem(Item* self, Actor* equiper);
void unequipItem(Item* equipment, Actor* actor);

// inventory.c functions
void inventoryMenu(void);

// room.c functions
Room* createRoom(int y, int x, int height, int width);
void drawRoom(Room* room);
void connectRoomCenters(Position* centerOne, Position* centerTwo);

// fov.c functions
int getDistance(Position origin, Position target);
void makeFOV(Entity* player);
void clearFOV(Entity* player);
bool isInMap(int y, int x);
bool lineOfSight(Position origin, Position target);
int getSign(int a);

// log.c exports
Message* createLog();
void addMessage(char text[1024]);
void printMessages(void);
void freeLog(void);

// draw.c functions
void drawEverything(void);
void drawEntity(Entity* entity);
void drawAllEntities(void);
void mapDraw(void);
void showWholeMap(void);
void drawUI(void);

// utils.c functions
int maxInt(int a, int b);
int minInt(int a, int b);
void clrRect(Position a, Position b);
void appendItem(List* head, Item* item);
void appendActor(List* head, Actor* actor);
void removeItem(List* head, Item* item, bool cleanUp);
void removeActor(List* head, Actor* actor, bool cleanUp);
void freeActor(Actor* actor);
void freeItem(Item* item);
void freeRoom(Room* room);
void freeAllRooms(Room** rooms, int n_rooms);
void freeList(List* head);
void freeEverything(void);

// save_load.c functions
void saveGame(void);
bool loadGame(void);


#endif
