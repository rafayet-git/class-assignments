#ifndef BATTLE_PLAYER_H
#define BATTLE_PLAYER_H

#include "Monster.h"
#include "BattleData.h"

#define MONSTER_PARTY_SIZE 4

typedef struct 
{
    Monster party[MONSTER_PARTY_SIZE];
} Player;

Player *make_player();

Player *load_player(char *file_name);

Monster *get_player_monster(Player *player, size_t index);

Monster *get_available_player_monster(Player *player);

char is_party_full(Player *player);

void save_player_to_file(Player *player, char *file_name);

void get_random_monster(BattleData *data, Player *player);

#endif