#ifndef FUNCTIONS_H
#define FUNCTIONS_H

// engine.c functions
void initLists(void);
void initDungeon(bool load_successful);
void gameLoop(void);
void closeGame(void);
bool screenSetUp(void);
bool intro(void);
void wonGame(void);
void lostGame(void);
bool checkVictory(void);

// level.c functions 
Position* mapSetUp(void);
void addDownStairs(Position* center);
void addUpStairs(Position* center);
Tile** createLevelTiles(void);
void clearLevel(void);
void createNewLevel(void);

// player.c functions
Actor* playerSetUp(Position* start_pos);
Position* handleInput(int input);
void playerCheckPosition(Position* newPosition);
void playerMove(Position* newPosition);
Position* goDownStairs(Entity* player);
Position* goUpStairs(Entity* player);
void grabItem(Entity* player);
void gainXP(Fighter* player, int amount);
void levelUp(Fighter* player);

// monster.c functions
Actor* createMonster(int y, int x, MonsterTemplate template, int xpLevel);

// fighter.c functions
void attack(Fighter* attacker, Fighter* defender);
void takeDamage(Fighter* fighter, int damage);
void drawBlood(Entity* entity);
void die(Fighter* fighter);

// ai.c functions
void takeTurn(Actor* actor, Actor* player);
void allMonstersTakeTurns(Actor* player);
void monsterCheckDirection(Actor* actor, Actor* target);
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
void useInventory(Inventory* inventory);

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
Message* createLog();
void addMessage(char text[1024]);
void printMessages(void);
void freeLog(void);

// ui.c functions
void drawUI(void);

// draw.c functions
void drawEverything(void);
void drawEntity(Entity* entity);
void drawAllEntities(void);
void mapDraw(void);
void showWholeMap(void);

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
