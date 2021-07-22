#ifndef EXTERNS_H
#define EXTERNS_H

// global constants
extern const int GAMEMAP_HEIGHT;
extern const int GAMEMAP_WIDTH;

// global variables
extern Actor* player;
extern Actor* boss;
extern Tile** level;
extern List* actors;
extern List* items;
extern Message* message_log;
extern int dungeon_level;
extern Position down_stairs;
extern Position up_stairs;
extern MonsterTemplate goblin;
extern MonsterTemplate orc;
extern MonsterTemplate troll;
extern MonsterTemplate balrog;
extern ItemTemplate health_potion;
extern ItemTemplate mana_potion;
extern ItemTemplate lightning_scroll;
extern ItemTemplate fireball_scroll;
extern ItemTemplate short_sword;
extern ItemTemplate small_shield;
extern ItemTemplate light_helm;


#endif
