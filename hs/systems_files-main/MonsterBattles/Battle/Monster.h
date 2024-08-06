#ifndef BATTLE_MONSTER_H
#define BATTLE_MONSTER_H

#include <stddef.h>

#include "Move.h"
#include "BattleData.h"
#include "MonsterData.h"

#define TOTAL_MOVES 2

typedef int MoveIndex;
typedef int MonsterIndex;

typedef struct
{
    long current_health;
    MoveIndex move_set[TOTAL_MOVES];
    MonsterIndex monster_data;
} Monster;

Move *get_move_data(BattleData *data, Monster *monster, int index);

MonsterData *get_monster_data(BattleData *data, Monster *monster);

void attack_monster(BattleData *data, Monster *attacker, Monster *defender, MoveIndex move_index);

#endif