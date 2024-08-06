#include "BattleData.h"

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>

BattleData *load_battle_data(char *move_data_path, char *monster_data_path)
{
    int moves_fd = open(move_data_path, O_RDONLY);
    int monster_fd = open(monster_data_path, O_RDONLY);

    BattleData *battle_data = (BattleData*) malloc(sizeof(BattleData));

    struct stat s;
    stat(move_data_path, &s);
    battle_data->total_moves = s.st_size / sizeof(Move);
    stat(monster_data_path, &s);
    battle_data->total_monsters = s.st_size / sizeof(MonsterData);

    battle_data->moves = (Move*) malloc(sizeof(Move) * battle_data->total_moves);
    battle_data->monsters = (MonsterData*) malloc(sizeof(MonsterData) * battle_data->total_monsters);

    read(moves_fd, battle_data->moves, sizeof(Move) * battle_data->total_moves);
    read(monster_fd, battle_data->monsters, sizeof(MonsterData) * battle_data->total_monsters);

    return battle_data;
}

void debug_print_battle_data_moves(BattleData *data)
{
    for (int i = 0; i < data->total_moves; ++i)
    {
        debug_print_move(data->moves + i);
    }
}

void debug_print_battle_data_monsters(BattleData *data)
{
    for (int i = 0; i < data->total_monsters; ++i)
    {
        debug_print_monster_data(data->monsters + i);
    }
}

void free_battle_data(BattleData *data)
{
    free(data->moves);
    free(data->monsters);
    free(data);
}