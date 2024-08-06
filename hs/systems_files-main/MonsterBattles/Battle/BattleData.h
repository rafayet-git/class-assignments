#ifndef BATTLE_DATA_H
#define BATTLE_DATA_H

#include "Move.h"
#include "MonsterData.h"

typedef struct 
{
    size_t total_moves;
    size_t total_monsters;
    Move *moves;
    MonsterData *monsters;
} BattleData;

BattleData *load_battle_data(char *move_data_path, char *monster_data_path);

void debug_print_battle_data_moves(BattleData *data);

void debug_print_battle_data_monsters(BattleData *data);

void free_battle_data(BattleData *data);

#endif 