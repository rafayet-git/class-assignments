#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

#include "Battle/Move.h"
#include "Battle/MonsterData.h"

#define BUFFER_LENGTH 256

int main()
{
    int move_fd = open("res/move_data.data", O_CREAT | O_WRONLY | O_APPEND , 0644);
    int monster_fd = open("res/monster_data.data", O_CREAT | O_WRONLY | O_APPEND, 0644);

    char buffer[BUFFER_LENGTH];

    while(1)
    {
        printf("Do you want to create a [move] or [monster]?\n");
        fgets(buffer, BUFFER_LENGTH, stdin);
        buffer[strlen(buffer) - 1] = '\0';

        if (strcasecmp("move", buffer) == 0)
        {
            char move_name[MOVE_NAME_LENGTH];
            printf("Enter a name: \n");
            fgets(move_name, MOVE_NAME_LENGTH, stdin);

            move_name[strlen(move_name) - 1] = '\0';

            printf("Enter the move type [attack] or [heal]:\n");
            fgets(buffer, BUFFER_LENGTH, stdin);

            MoveType type;
            if (strcasecmp(buffer, "attack\n") == 0)
            {
                type = ATTACK_MOVE;
            }
            else if (strcasecmp(buffer, "heal\n") == 0)
            {
                type = HEAL_MOVE;
            }
            else
            {
                printf("Invalid option. Has to be [attack] or [heal].\n");
                continue;
            }

            size_t value;
            printf("Enter the value: \n");
            fgets(buffer, BUFFER_LENGTH, stdin);
            buffer[strlen(buffer) - 1] = '\0';

            int res = sscanf(buffer, "%ld", &value);
            if (res == 0)
            {
                printf("Invalid input. Has to be an integral value.\n");
                continue;
            }

            Move *move = make_move(move_name, type, value);
            save_move_to_file(move, move_fd);
        }
        else if (strcasecmp("monster", buffer) == 0)
        {
            char monster_name[MONSTER_NAME_LENGTH];
            printf("Enter a name: \n");
            fgets(monster_name, MONSTER_NAME_LENGTH, stdin);
            
            monster_name[strlen(monster_name) - 1] = '\0';

            size_t value;
            printf("Enter the maximum health: \n");
            fgets(buffer, BUFFER_LENGTH, stdin);
            buffer[strlen(buffer) - 1] = '\0';

            int res = sscanf(buffer, "%ld", &value);
            if (res == 0)
            {
                printf("Invalid input. Has to be an integral value.\n");
                continue;
            }

            MonsterData *monster = make_monster_data(monster_name, value);
            save_monster_data_to_file(monster, monster_fd);
        }
    }

    close(move_fd);
    close(monster_fd);

    return 0;
}