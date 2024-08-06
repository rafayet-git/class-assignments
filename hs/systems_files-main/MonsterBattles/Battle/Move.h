#ifndef BATTLE_MOVE_H
#define BATTLE_MOVE_H

#define MOVE_NAME_LENGTH 32

#include <stddef.h>

typedef enum
{
    ATTACK_MOVE,
    HEAL_MOVE
} MoveType;

// to be serialized and deserialized
typedef struct 
{
    char move_name[MOVE_NAME_LENGTH];
    MoveType move_type;
    size_t value;
} Move;

Move *make_move(char move_name[MOVE_NAME_LENGTH], MoveType move_type, size_t value);

void debug_print_move(Move *move);

void save_move_to_file(Move *move, int fd);

#endif