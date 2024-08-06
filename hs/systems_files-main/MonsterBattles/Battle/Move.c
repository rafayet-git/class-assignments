#include "Move.h"

#include <string.h>
#include <stdlib.h>
#include <unistd.h>

#include <stdio.h>

Move *make_move(char move_name[MOVE_NAME_LENGTH], MoveType move_type, size_t value)
{
    Move *move = (Move*) malloc(sizeof(Move));
    strcpy(move->move_name, move_name);
    move->move_type = move_type;
    move->value = value;

    return move;
}

void debug_print_move(Move *move)
{
    printf("MV[.name=%s, .move_type=%s, .value=%ld]\n", move->move_name, move->move_type == ATTACK_MOVE ? "attack_move" : "heal_move", move->value);
}

void save_move_to_file(Move *move, int fd)
{
    write(fd, move, sizeof(Move));
}