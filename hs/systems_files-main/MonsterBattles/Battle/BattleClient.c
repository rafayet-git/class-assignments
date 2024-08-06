#include "BattleClient.h"

#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include <time.h>

#include "../TUI/Preset.h"
#include "CustomPreset.h"

BattleClient *make_battle_client(char *move_data_path, char *monster_data_path, char is_new_player, char *player_save_path)
{
    BattleClient *client = (BattleClient*) malloc(sizeof(BattleClient));

    srand(time(NULL));
    client->context = make_window_context();

    if (client->context->width < MINIMUM_TERMINAL_WIDTH || client->context->height < MINIMUM_TERMINAL_HEIGHT)
    {
        exit(1);
    }

    client->data = load_battle_data(move_data_path, monster_data_path);
    client->player = is_new_player ? make_player() : load_player(player_save_path);
    client->player_save_path = player_save_path;
    client->state = client_state_normal;

    size_t bx, by;
    wchar_t *game_name[] = {
        L" Monster Battles "
    };

    wchar_t *battle_bottom_left[] = {
        L"├────────────────────────╮",
        L"│                        │",
        L"│                        │",
        L"├────────────────────────┴"
    };

    wchar_t *battle_top_right[] = {
        L"┬────────────────────────╮",
        L"│                        │",
        L"│                        │",
        L"╰────────────────────────┤"
    };

    wchar_t *clear_name = L"               ";
    wchar_t *clear_percent = L"    ";
    wchar_t *clear_move[2] = { L"                               ", L"                               " };

    set_saved_canvas(client->context, BATTLE_CLEAR, generate_clear_screen());
    set_saved_canvas(client->context, BATTLE_CANVAS_BORDER, generate_border(client->context->width, client->context->height / 2, L'─', L'│', L'╭', L'╮', L'╰', L'╯', f_white, b_black, S_BOLD));
    set_saved_canvas(client->context, BATTLE_CANVAS_TITLE, generate_text(game_name, 1, 18));
    set_saved_canvas(client->context, BATTLE_SCREEN_BORDER_1, generate_horizontal_line(L'─', client->context->width, L'├', L'┤', f_white, b_black, S_BOLD));
    set_saved_canvas(client->context, BATTLE_SCREEN_BORDER_2, generate_vertical_line(L'│', 4, L'┬', L'┴', f_white, b_black, S_BOLD));
    set_saved_canvas(client->context, BATTLE_GOTO_CONSOLE, generate_goto(client->context->height / 2 + 1, 1));
    set_saved_canvas(client->context, BATTLE_SCREEN_PLAYER_DISPLAY, generate_canvas(battle_bottom_left, 4, 27, f_white, b_black, S_BOLD));
    set_saved_canvas(client->context, BATTLE_SCREEN_ENEMY_DISPLAY, generate_canvas(battle_top_right, 4, 27, f_white, b_black, S_BOLD));
    set_saved_canvas(client->context, NO_BATTLE_BORDER, generate_party_canvas(client->context->width, client->context->height / 2, f_white, b_black, S_BOLD));
    set_saved_canvas(client->context, CLEAR_BATTLE_NAME, generate_text(&clear_name, 1, 16));
    set_saved_canvas(client->context, CLEAR_CONSOLE_LINES, generate_clear_lines(client->context->height - client->context->height / 2));
    set_saved_canvas(client->context, CLEAR_HEALTH_PERCENT, generate_text(&clear_percent, 1, wcslen(clear_percent)));
    set_saved_canvas(client->context, CLEAR_MOVE_LINE, generate_text(clear_move, 2, wcslen(clear_move[0])));

    client->battle_screen_border_pos[0] = 1;
    client->battle_screen_border_pos[1] = 1;

    client->battle_screen_title_pos[0] = 5;
    client->battle_screen_title_pos[1] = 1;

    canvas_get_position(client->context->saved_canvases[BATTLE_CANVAS_BORDER], canvas_bottom_right, &bx, &by);

    client->battle_screen_battle_ui_1[0] = 1;
    client->battle_screen_battle_ui_1[1] = client->battle_screen_border_pos[1] + by - 4;

    client->battle_screen_battle_ui_2[0] = client->battle_screen_border_pos[0] + bx / 2;
    client->battle_screen_battle_ui_2[1] = client->battle_screen_border_pos[1] + by - 4;

    client->battle_screen_player_display_pos[0] = 1;
    client->battle_screen_player_display_pos[1] = client->battle_screen_border_pos[1] + by - 7;

    client->battle_screen_enemy_display_pos[0] = client->battle_screen_border_pos[0] + bx - 26;
    client->battle_screen_enemy_display_pos[1] = 1;

    client->battle_screen_player_health_pos[0] = 4;
    client->battle_screen_player_health_pos[1] = client->battle_screen_player_display_pos[1] + 2;

    client->battle_screen_enemy_health_pos[0] = client->battle_screen_enemy_display_pos[0] + 3;
    client->battle_screen_enemy_health_pos[1] = 3;

    client->battle_screen_player_percent_pos[0] = client->battle_screen_player_health_pos[0] + 16;
    client->battle_screen_player_percent_pos[1] = client->battle_screen_player_health_pos[1];
    client->battle_screen_enemy_percent_pos[0] = client->battle_screen_enemy_health_pos[0] + 16;
    client->battle_screen_enemy_percent_pos[1] = client->battle_screen_enemy_health_pos[1];

    client->battle_screen_player_name_pos[0] = client->battle_screen_player_health_pos[0];
    client->battle_screen_player_name_pos[1] = client->battle_screen_player_health_pos[1] - 1;
    client->battle_screen_enemy_name_pos[0] = client->battle_screen_enemy_health_pos[0];
    client->battle_screen_enemy_name_pos[1] = client->battle_screen_enemy_health_pos[1] - 1;

    canvas_get_position(client->context->saved_canvases[NO_BATTLE_BORDER], canvas_middle, &bx, &by);

    client->cell_pos[0][0] = 2;
    client->cell_pos[0][1] = 2;
    client->cell_pos[1][0] = bx + 2;
    client->cell_pos[1][1] = 2;
    client->cell_pos[2][0] = 2;
    client->cell_pos[2][1] = by + 2;
    client->cell_pos[3][0] = bx + 2;
    client->cell_pos[3][1] = by + 2;

    client->console_pos[0] = 1;
    client->console_pos[1] = client->context->height / 2 + 1;

    return client;
}  

void draw_no_battle_scene(BattleClient *client)
{
    if (client->state == client_state_pvp) return;
    push_saved_canvas_instruction(client->context, BATTLE_CLEAR, 0, 0);
    push_saved_canvas_instruction(client->context, NO_BATTLE_BORDER, client->battle_screen_border_pos[0], client->battle_screen_border_pos[1]);
    push_saved_canvas_instruction(client->context, BATTLE_CANVAS_TITLE, client->battle_screen_title_pos[0], client->battle_screen_title_pos[1]);
    push_saved_canvas_instruction(client->context, BATTLE_GOTO_CONSOLE, 0, 0);
    execute_all_instructions(client->context->queue);   
}

void draw_battle_scene(BattleClient *client)
{
    if (client->state == client_state_normal) return;

    push_saved_canvas_instruction(client->context, BATTLE_CLEAR, 0, 0);
    push_saved_canvas_instruction(client->context, BATTLE_CANVAS_BORDER, client->battle_screen_border_pos[0], client->battle_screen_border_pos[1]);
    push_saved_canvas_instruction(client->context, BATTLE_CANVAS_TITLE, client->battle_screen_title_pos[0], client->battle_screen_title_pos[1]);   

    push_saved_canvas_instruction(client->context, BATTLE_SCREEN_BORDER_1, client->battle_screen_battle_ui_1[0], client->battle_screen_battle_ui_1[1]);
    push_saved_canvas_instruction(client->context, BATTLE_SCREEN_BORDER_2, client->battle_screen_battle_ui_2[0], client->battle_screen_battle_ui_2[1]);
    push_saved_canvas_instruction(client->context, BATTLE_SCREEN_PLAYER_DISPLAY, client->battle_screen_player_display_pos[0], client->battle_screen_player_display_pos[1]);
    push_saved_canvas_instruction(client->context, BATTLE_SCREEN_ENEMY_DISPLAY, client->battle_screen_enemy_display_pos[0], client->battle_screen_enemy_display_pos[1]);
    push_saved_canvas_instruction(client->context, BATTLE_GOTO_CONSOLE, 0, 0);
    execute_all_instructions(client->context->queue);
}

void update_battle_monster_display(BattleClient *client, Monster *monster, battle_user user)
{
    if (client->state == client_state_normal) return;

    int *pos = user == battle_player ? client->battle_screen_player_name_pos : client->battle_screen_enemy_name_pos;

    push_saved_canvas_instruction(client->context, CLEAR_BATTLE_NAME, pos[0], pos[1]);

    wchar_t *buffer = malloc(sizeof(wchar_t) * MONSTER_NAME_LENGTH);
    mbstowcs(buffer, client->data->monsters[monster->monster_data].monster_name, MONSTER_NAME_LENGTH);

    Canvas *canvas = generate_canvas(&buffer, 1, MONSTER_NAME_LENGTH, f_white, b_black, S_BOLD);
    push_instruction(client->context->queue, canvas, pos[0], pos[1], 1);
    execute_all_instructions(client->context->queue);
    
    free(buffer);
}

void update_battle_health_display(BattleClient *client, Monster *monster, battle_user user)
{
    if (client->state == client_state_normal) return;

    int *pos = user == battle_player ? client->battle_screen_player_health_pos : client->battle_screen_enemy_health_pos;

    MonsterData *data = client->data->monsters + monster->monster_data;
    push_instruction(client->context->queue, generate_health_bar(monster->current_health, data->max_health), pos[0], pos[1], 1);

    push_saved_canvas_instruction(client->context, CLEAR_HEALTH_PERCENT, pos[0] + 16, pos[1]);
    int percent = (double) monster->current_health / data->max_health * 100;
    wchar_t *wbuffer = malloc(8 * sizeof(wchar_t));
    swprintf(wbuffer, 8, L"%d%%", percent);
    push_instruction(client->context->queue, generate_canvas(&wbuffer, 1, wcslen(wbuffer), f_white, b_black, S_BOLD), pos[0] + 16, pos[1], 1);
    execute_all_instructions(client->context->queue);

    free(wbuffer);
}

void update_team_display(BattleClient *client)
{
    MonsterData *mon_data;
    wchar_t *health_buffer = malloc(sizeof(wchar_t) * client->context->width / 2 - 3);
    wchar_t *name_buffer = malloc(sizeof(wchar_t) * MONSTER_NAME_LENGTH);
    for (int i = 0; i < MONSTER_PARTY_SIZE; ++i)
    {
        if (client->player->party[i].current_health > 0)
        {
            Monster *mon_ptr = client->player->party + i;
            mon_data = get_monster_data(client->data, mon_ptr);
            mbstowcs(name_buffer, client->data->monsters[mon_ptr->monster_data].monster_name, MONSTER_NAME_LENGTH);
            swprintf(health_buffer, client->context->width / 2 - 3, L"Health: %d / %d", mon_ptr->current_health, mon_data->max_health);

            push_instruction(client->context->queue, generate_canvas(&name_buffer, 1, MONSTER_NAME_LENGTH, f_white, b_black, S_BOLD), client->cell_pos[i][0], client->cell_pos[i][1], 1);
            push_instruction(client->context->queue, generate_canvas(&health_buffer, 1, wcslen(health_buffer), f_white, b_black, S_BOLD), client->cell_pos[i][0], client->cell_pos[i][1] + 1, 1);
            execute_all_instructions(client->context->queue);
        } 
    }

    free(name_buffer);
    free(health_buffer);
}

void update_move_display(BattleClient *client, Monster *monster)
{
    const size_t buffer_size = MINIMUM_TERMINAL_WIDTH / 2 - 2;
    wchar_t *buffer = malloc(buffer_size * sizeof(wchar_t));
    Move *move_0 = get_move_data(client->data, monster, 0);
    Move *move_1 = get_move_data(client->data, monster, 1);

    swprintf(buffer, buffer_size, L"1) %s", move_0->move_name);
    push_saved_canvas_instruction(client->context, CLEAR_MOVE_LINE, client->battle_screen_battle_ui_1[0] + 1, client->battle_screen_battle_ui_1[1] + 1);
    push_instruction(client->context->queue, generate_canvas(&buffer, 1, wcslen(buffer), f_white, b_black, S_BOLD), client->battle_screen_battle_ui_1[0] + 1, client->battle_screen_battle_ui_1[1] + 1, 1);
    swprintf(buffer, buffer_size, move_0->move_type == ATTACK_MOVE ? L"Attack %ld damage" : L"Heal %ld damage", move_0->value);
    push_instruction(client->context->queue, generate_canvas(&buffer, 1, wcslen(buffer), f_white, b_black, S_BOLD), client->battle_screen_battle_ui_1[0] + 1, client->battle_screen_battle_ui_1[1] + 2, 1);
    
    swprintf(buffer, buffer_size, L"2) %s", move_1->move_name);
    push_saved_canvas_instruction(client->context, CLEAR_MOVE_LINE, client->battle_screen_battle_ui_2[0] + 1, client->battle_screen_battle_ui_2[1] + 1);
    push_instruction(client->context->queue, generate_canvas(&buffer, 1, wcslen(buffer), f_white, b_black, S_BOLD), client->battle_screen_battle_ui_2[0] + 1, client->battle_screen_battle_ui_2[1] + 1, 1);
    swprintf(buffer, buffer_size, move_1->move_type == ATTACK_MOVE ? L"Attack %ld damage" : L"Heal %ld damage", move_1->value);
    push_instruction(client->context->queue, generate_canvas(&buffer, 1, wcslen(buffer), f_white, b_black, S_BOLD), client->battle_screen_battle_ui_2[0] + 1, client->battle_screen_battle_ui_2[1] + 2, 1);

    execute_all_instructions(client->context->queue);
    free(buffer);
}

void clear_and_goto_console(BattleClient *client)
{
    push_saved_canvas_instruction(client->context, CLEAR_CONSOLE_LINES, client->console_pos[0], client->console_pos[1]);
    push_saved_canvas_instruction(client->context, BATTLE_GOTO_CONSOLE, 0, 0);
    execute_all_instructions(client->context->queue);
}

void free_battle_client(BattleClient *client)
{
    free_battle_data(client->data);
    free_window_context(client->context);
    free(client->player);
    free(client);
}