#include "Player.h"

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>

Player *make_player()
{
    return (Player*) calloc(1, sizeof(Player));
}

Player *load_player(char *file_name)
{
    Player *player = (Player*) malloc(sizeof(Player));
    int file_fd = open(file_name, O_RDONLY);
    read(file_fd, player, sizeof(Player));
    close(file_fd);

    return player;
}

Monster *get_player_monster(Player *player, size_t index)
{
    if (index >= MONSTER_PARTY_SIZE) return NULL;
    return player->party + index;
}

Monster *get_available_player_monster(Player *player)
{
    for (int i = 0; i < MONSTER_PARTY_SIZE; ++i)
    {
        if (player->party[i].current_health > 0)
        {
            return player->party + i;
        }
    }
    return NULL;
}

char is_party_full(Player *player)
{
    for (int i = 0; i < MONSTER_PARTY_SIZE; ++i)
    {
        if (player->party[i].current_health <= 0)
        {
            return 0;
        }
    }
    return 1;
}

void save_player_to_file(Player *player, char *file_name)
{
    int file_fd = open(file_name, O_CREAT | O_TRUNC | O_WRONLY, 0644);
    write(file_fd, player, sizeof(Player));
    close(file_fd);
}

void get_random_monster(BattleData *data, Player *player)
{
    Monster* monster;
    for (int i = 0; i < MONSTER_PARTY_SIZE; ++i)
    {
        if (player->party[i].current_health <= 0)
        {
            monster = player->party + i;
            break;
        }
    }

    monster->monster_data = rand() % data->total_monsters;
    for (int i = 0; i < TOTAL_MOVES; ++i)
    {
        monster->move_set[i] = rand() % data->total_moves;
    }
    monster->current_health = data->monsters[monster->monster_data].max_health;
}