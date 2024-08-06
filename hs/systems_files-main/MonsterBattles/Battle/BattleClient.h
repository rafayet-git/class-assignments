#ifndef BATTLE_CLIENT_H
#define BATTLE_CLIENT_H

#include "../TUI/Window.h"
#include "BattleData.h"
#include "Player.h"
#include "Monster.h"

#define MINIMUM_TERMINAL_WIDTH 79
#define MINIMUM_TERMINAL_HEIGHT 24

typedef enum
{
    BATTLE_CLEAR,
    BATTLE_CANVAS_BORDER,
    BATTLE_CANVAS_TITLE,
    BATTLE_SCREEN_BORDER_1,
    BATTLE_SCREEN_BORDER_2,
    BATTLE_GOTO_CONSOLE,
    BATTLE_SCREEN_PLAYER_DISPLAY,
    BATTLE_SCREEN_ENEMY_DISPLAY,
    NO_BATTLE_BORDER,
    CLEAR_BATTLE_NAME,
    CLEAR_CONSOLE_LINES,
    CLEAR_HEALTH_PERCENT,
    CLEAR_MOVE_LINE,
    INDEX_TOTAL
} BattleCanvasIndex;

typedef enum 
{
    client_state_normal,
    client_state_pvp
} BattleClientState;

typedef struct 
{
    WindowContext *context;
    BattleData *data;
    Player *player;
    char *player_save_path;
    BattleClientState state;

    int battle_screen_border_pos[2];
    int battle_screen_title_pos[2];
    int battle_screen_battle_ui_1[2];
    int battle_screen_battle_ui_2[2];
    int battle_screen_player_display_pos[2];
    int battle_screen_enemy_display_pos[2];
    int battle_screen_player_health_pos[2];
    int battle_screen_enemy_health_pos[2];
    int battle_screen_player_percent_pos[2];
    int battle_screen_enemy_percent_pos[2];
    int battle_screen_player_name_pos[2];
    int battle_screen_enemy_name_pos[2];
    
    int cell_pos[4][2];

    int console_pos[2];

} BattleClient;

typedef enum
{
    battle_player,
    battle_enemy
} battle_user;

BattleClient *make_battle_client(char *move_data_path, char *monster_data_path, char is_new_player, char *player_save_path);

void draw_no_battle_scene(BattleClient *client);

void draw_battle_scene(BattleClient *client);

void update_battle_monster_display(BattleClient *client, Monster *monster, battle_user user);

void update_battle_health_display(BattleClient *client, Monster *monster, battle_user user);

void update_team_display(BattleClient *client);

void update_move_display(BattleClient *client, Monster *monster);

void clear_and_goto_console(BattleClient *client);

void free_battle_client(BattleClient *client);

#endif