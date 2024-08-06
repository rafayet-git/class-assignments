#include "MonsterData.h"

#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <unistd.h>
#include <string.h>
#include <wchar.h>
#include "../TUI/Macros.h"

MonsterData *make_monster_data(char monster_name[MONSTER_NAME_LENGTH], size_t max_health)
{
    MonsterData *monster_data = (MonsterData*) malloc(sizeof(MonsterData));
    strcpy(monster_data->monster_name, monster_name);
    monster_data->max_health = max_health;

    return monster_data;
}

void debug_print_monster_data(MonsterData *monster)
{
    PRINTF("MD[.name=%s, .health=%ld]\n", monster->monster_name, monster->max_health);
}

void save_monster_data_to_file(MonsterData *monster, int fd)
{
    write(fd, monster, sizeof(MonsterData));
}