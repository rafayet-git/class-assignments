#include "Monster.h"

#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <wchar.h>

#include "MonsterData.h"
#include "../TUI/Macros.h"

Move *get_move_data(BattleData *data, Monster *monster, int index)
{
    if (index >= data->total_moves) return NULL;
    return data->moves + monster->move_set[index];
}

MonsterData *get_monster_data(BattleData *data, Monster *monster)
{
    return data->monsters + monster->monster_data;
}

void attack_monster(BattleData *data, Monster *attacker, Monster *defender, MoveIndex move_index)
{
    if (defender->current_health <= 0) return;

    Move *move = get_move_data(data, attacker, move_index);
    if (move->move_type == ATTACK_MOVE)
    {
        defender->current_health -= move->value;
    }
    else if (move->move_type == HEAL_MOVE)
    {
        MonsterData *monster = get_monster_data(data, attacker);
        attacker->current_health = attacker->current_health + move->value > monster->max_health ? monster->max_health : attacker->current_health + move->value;
    }
}