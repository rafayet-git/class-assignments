#include <stdio.h>
#include <string.h>
#include <locale.h>
#include <stdlib.h>
#include <wchar.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdbool.h>
#include <arpa/inet.h>
#include <sys/stat.h>

#include "Battle/BattleData.h"
#include "Battle/BattleClient.h"
#include "TUI/SocketConnect.h"

#define PORT_NUMBER "43290"

#define USER_CLIENT_BUFFER_LENGTH 128
#define IP_ADDRESS_LENGTH 32
#define REMOVE_NEWLINE_FROM_BUFFER(buffer) buffer[strlen(buffer) - 1] = '\0'            

typedef struct move_data_t
{
    int move_index;
} move_data;

void flush_stdin_buffer()
{
    char c;
    while ((c = getchar()) != '\n' && c != EOF);
}

char is_valid_ip_address(char *ip_address)
{
    if (strcmp(ip_address, "localhost")==0){ 
      strcpy(ip_address, "127.0.0.1\0\0");
    }struct sockaddr_in s;
    int res = inet_pton(AF_INET, ip_address, &(s.sin_addr));
    return res != 0;
}

char does_file_exist(char *file_path)
{
    struct stat s;
    return stat(file_path, &s) == 0;
}

int main()
{
    setlocale(LC_ALL, "");
    
    char user_client_buffer[USER_CLIENT_BUFFER_LENGTH];

    char c = 0;
    if (does_file_exist("res/save.data"))
    {
        PRINT("Do you want to load the save? [Y/N]\n");
        c = getchar();
        flush_stdin_buffer();
    }
    

    BattleClient *client = make_battle_client("res/move_data.data", "res/monster_data.data", c == 'Y' || c == 'y' ? 0 : 1, "res/save.data");
    client->state = client_state_normal;

    Player *opponent = malloc(sizeof(Player)); // opponent buffer 
    AddressInf *internet = malloc(sizeof(AddressInf)); // socket info buffer

    draw_no_battle_scene(client);
    if (c == 'Y' || c == 'y') update_team_display(client);

    char ip_address[IP_ADDRESS_LENGTH];
    char server_switch[4];

    while (1)
    {
        clear_and_goto_console(client);

        if (client->state == client_state_normal)
        {
            PRINT("Enter command: \"catch\", \"save\", \"battle [ -server [ip_address] | -client [ip_address] ]\", \"exit\"\n> ");  

            fgets(user_client_buffer, USER_CLIENT_BUFFER_LENGTH, stdin);
            REMOVE_NEWLINE_FROM_BUFFER(user_client_buffer);

            char ip_address[IP_ADDRESS_LENGTH];
            char server_switch[16];
            int res;

            if (strcasecmp("catch", user_client_buffer) == 0)
            {
                if (is_party_full(client->player))
                {
                    PRINT("Party is full. You cannot catch more monsters.\n");
                    sleep(2);
                    continue;
                }
                else
                {
                    get_random_monster(client->data, client->player);
                    update_team_display(client);
                }
            }
            else if (strcasecmp("save", user_client_buffer) == 0)
            {
                save_player_to_file(client->player, client->player_save_path);
                PRINTF("Saved to %s.\n", client->player_save_path);
                sleep(2);
                continue;
            }
            else if ((res = sscanf(user_client_buffer, "battle %s %s", server_switch, ip_address)) >= 1)
            {
                if (!get_available_player_monster(client->player))
                {
                    PRINT("You do not have a party. Use \"catch\" to capture some monsters.\n");
                    sleep(2);
                    continue;
                }
                else if (!is_valid_ip_address(ip_address) && res == 2)
                {
                    PRINT("Invalid IP address. Try again.\n");
                    sleep(2);
                    continue;
                }

                if (strcasecmp("-server", server_switch) == 0 || strcasecmp("-s", server_switch) == 0)
                {
                    create_socket(internet, res == 1 ? NULL : ip_address, PORT_NUMBER, 1);
                    PRINT("Awaiting for connection...\n");
                    server_recieve_connection(internet);
                    PRINT("Recieved a connection...\n");
                }
                else if ((strcasecmp("-client", server_switch) == 0 || strcasecmp("-c", server_switch) == 0) && res == 2)
                {
                    create_socket(internet, ip_address, PORT_NUMBER, 0);
                    client_make_connection(internet);
                    PRINTF("Successfully connected to %s\n", ip_address);
                }
                else
                {
                    PRINT("Invalid argument. Has to be \"-server\" (\"-s\") or \"-client [ip_address] \" (\"-c [ip_address]\")\n");
                    sleep(2);
                    continue;
                }

                if (socket_writedata(internet, client->player, sizeof(Player)) == 0)
                {
                    PRINT("Opponent disconnected...\n");
                    freeall(internet);
                    sleep(2);
                    continue;
                }
                if (socket_readdata(internet, opponent, sizeof(Player)) == 0)
                {
                    PRINT("Opponent disconnected...\n");
                    freeall(internet);
                    sleep(2);
                    continue;
                }
                PRINT("Successfully exchanged data. Commencing battle.\n");
                client->state = client_state_pvp;
                sleep(2);

                draw_battle_scene(client);
                continue;
            }
            else if (strcasecmp("exit", user_client_buffer) == 0)
            {
                save_player_to_file(client->player, client->player_save_path);
                free(opponent);
                free(internet);
                free_battle_client(client);
                exit(0);
            }
            else
            {
                PRINT("Invalid Input. Try again.\n");
                sleep(2);
                continue;
            }
        }
        else if (client->state == client_state_pvp)
        {

            Monster *oppo_mon = get_available_player_monster(opponent);
            Monster *user_mon = get_available_player_monster(client->player);

            if (oppo_mon != NULL && user_mon != NULL)
            {
                update_battle_monster_display(client, user_mon, battle_player);
                update_battle_monster_display(client, oppo_mon, battle_enemy);
                update_battle_health_display(client, user_mon, battle_player);
                update_battle_health_display(client, oppo_mon, battle_enemy);
                update_move_display(client, user_mon);

                int move_index;
                clear_and_goto_console(client);
                PRINT("Fight! Enter \"move [ 1 | 2 ]\" to use a move.\n> ");
                fgets(user_client_buffer, USER_CLIENT_BUFFER_LENGTH, stdin);

                while (sscanf(user_client_buffer, "move %d", &move_index) != 1 && (move_index < 1 || move_index > 2))
                {
                    clear_and_goto_console(client);
                    PRINT("Invalid Input. Enter \"move [ 1 | 2 ]\" to use a move.\n> ");
                    fgets(user_client_buffer, USER_CLIENT_BUFFER_LENGTH, stdin);
                }

                move_data outgoing = { move_index - 1 };
                if (socket_writedata(internet, &outgoing, sizeof(move_data)) == 0)
                {
                    PRINT("Opponent disconnected...\n");
                    freeall(internet);
                    sleep(2);
                    client->state = client_state_normal;
                    draw_no_battle_scene(client);
                    update_team_display(client);
                    continue;
                }

                PRINT("Waiting for opponent's turn...\n");
                move_data incoming;
                if (socket_readdata(internet, &incoming, sizeof(move_data)) == 0)
                {
                    PRINT("Opponent disconnected...\n");
                    freeall(internet);
                    sleep(2);
                    client->state = client_state_normal;
                    draw_no_battle_scene(client);
                    update_team_display(client);
                    continue;
                }

                attack_monster(client->data, user_mon, oppo_mon, outgoing.move_index);
                attack_monster(client->data, oppo_mon, user_mon, incoming.move_index);
            }
            else
            {
                clear_and_goto_console(client);
                if (user_mon == oppo_mon)
                {
                    PRINT("It was a tie! Exiting battle...\n");
                }
                else if (user_mon)
                {
                    PRINT("You won the battle! Exiting battle...\n");
                }
                else
                {
                    PRINT("You lost the battle. Exiting battle...\n");
                }
                freeall(internet);
                sleep(2);
                client->state = client_state_normal;
                draw_no_battle_scene(client);
                update_team_display(client);
            }
        }
    }

    free(opponent);
    free(internet);
    free_battle_client(client);
}
