#ifndef BATTLE_MONSTER_DATA_H
#define BATTLE_MONSTER_DATA_H

#include <stddef.h>

#define MONSTER_NAME_LENGTH 16

typedef struct 
{
    char monster_name[MONSTER_NAME_LENGTH];
    size_t max_health;
} MonsterData;

MonsterData *make_monster_data(char monster_name[MONSTER_NAME_LENGTH], size_t max_health);

void debug_print_monster_data(MonsterData *monster);

void save_monster_data_to_file(MonsterData *monster, int fd);

#endif 