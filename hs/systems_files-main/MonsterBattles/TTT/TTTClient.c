#include "TTTClient.h"

#include <stdlib.h>
#include <string.h>
#include <wchar.h>

#include "../TUI/Preset.h"

const TTTPattern patterns[8] = {
    // 000000111
    (1 << 3) - 1, // 000 000 111
    ((1 << 3) - 1) << 3, // 000 111 000
    ((1 << 3) - 1) << 6, // 111 000 000
    73, // 001 001 001
    73 << 1, // 010 010 010
    73 << 2,
    273, // 100 010 001
    84// 001 010 100
};

TTTClient *make_ttt_client(TTTUser user_char)
{   
    TTTClient *client = (TTTClient*) malloc(sizeof(TTTClient));
    WindowContext *context = make_window_context();

    client->context = context;

    wchar_t *empty_tic_tac_toe[] = {
        L"\033│\033│\033",
        L"─┼─┼─",
        L"\033│\033│\033",
        L"─┼─┼─",
        L"\033│\033│\033"
    };

    wchar_t *clear_tic_tac_toe[] = {
        L" \033 \033 \033",
        L"\033\033\033\033\033",
        L" \033 \033 \033",
        L"\033\033\033\033\033",
        L" \033 \033 \033"
    };
    wchar_t *tic_tac_toe_name[] = {
        L" Tic-Tac-Toe "
    };

    set_saved_canvas(context, EMPTY_TIC_TAC_TOE, generate_canvas(empty_tic_tac_toe, 5, 6, f_white, b_black, S_BOLD));
    set_saved_canvas(context, BORDER, generate_border(context->width, context->height / 2, L'─', L'│', L'╭', L'╮', L'╰', L'╯', f_white, b_black, S_BOLD));
    set_saved_canvas(context, NO_BLINK_O, generate_character_canvas(1, 1, L'O', f_white, b_black, S_BOLD));
    set_saved_canvas(context, NO_BLINK_X, generate_character_canvas(1, 1, L'X', f_white, b_black, S_BOLD));
    set_saved_canvas(context, BLINK_O, generate_character_canvas(1, 1, L'O', f_white, b_black, S_BOLD | S_BLINKING));
    set_saved_canvas(context, BLINK_X, generate_character_canvas(1, 1, L'X', f_white, b_black, S_BOLD | S_BLINKING));
    set_saved_canvas(context, CLEAR_TIC_TAC_TOE, generate_canvas(clear_tic_tac_toe, 5, 6, f_white, b_black, S_BOLD));
    set_saved_canvas(context, SCREEN_CLEAR, generate_clear_screen());
    set_saved_canvas(context, CLEAR_LINES, generate_clear_lines(context->height - context->height / 2));

    size_t width, height;
    canvas_get_position(context->saved_canvases[BORDER], canvas_bottom_left, &width, &height);
    set_saved_canvas(context, CONSOLE_PRINT, generate_goto(height + 1, width));

    size_t rel_x, rel_y;
    canvas_get_position(client->context->saved_canvases[BORDER], canvas_middle, &rel_x, &rel_y);
    size_t ttt_x, ttt_y;
    canvas_get_position(client->context->saved_canvases[EMPTY_TIC_TAC_TOE], canvas_middle, &ttt_x, &ttt_y);

    client->grid = 0;
    client->user_char = user_char;
    client->ttt_xpos = rel_x - ttt_x;
    client->ttt_ypos = rel_y - ttt_y;

    return client;   
}

void draw_ttt_window(TTTClient *client)
{
    wchar_t *tic_tac_toe_name[] = {
        L" Tic-Tac-Toe "
    };

    push_saved_canvas_instruction(client->context, SCREEN_CLEAR, 0, 0);
    push_saved_canvas_instruction(client->context, BORDER, 1, 1);
    push_instruction(client->context->queue, generate_text(tic_tac_toe_name, 1, 14), 5, 1, 1);
    push_saved_canvas_instruction(client->context, EMPTY_TIC_TAC_TOE, client->ttt_xpos, client->ttt_ypos);
    push_saved_canvas_instruction(client->context, CONSOLE_PRINT, 0, 0);
    execute_all_instructions(client->context->queue);
}

char ttt_is_complete(TTTClient *client)
{
    for (int i = 0; i < 8; ++i)
    {
        if ((client->grid >> ttt_O & patterns[i]) == patterns[i] || (client->grid >> ttt_X & patterns[i]) == patterns[i] || (client->grid >> ttt_Combine & 511) == 511) return 1;
    }
    return 0;
}

void get_rowcol_pos(TTTClient *client, char row, char col, size_t *x_pos, size_t *y_pos)
{
    *x_pos = client->ttt_xpos + 2 * col;
    *y_pos = client->ttt_ypos + 2 * row;
}

// 000 000 000
char ttt_set_value(TTTClient *client, char row, char col, TTTUser user_char)
{
    if (!(client->grid >> ttt_Combine & 1 << row * 3 + col))
    {
        client->grid |= 1 << row * 3 + col << ttt_Combine;
        client->grid |= 1 << row * 3 + col << user_char;

        size_t x, y;
        get_rowcol_pos(client, row, col, &x, &y);
        push_saved_canvas_instruction(client->context, user_char == ttt_O ? NO_BLINK_O : NO_BLINK_X, x, y);
        push_saved_canvas_instruction(client->context, CONSOLE_PRINT, 0, 0);
        execute_all_instructions(client->context->queue);

        return 1;
    }
    return 0;
}

void debug_print_TTTClient(TTTClient *client)
{
    int grid = client->grid;
    for (int i = 0; i < 9; ++i)
    {
        if (i && i % 3 == 0) PRINT("\n");
        if (grid >> ttt_Combine & 1 << i)
        {
            PRINTF("%c", grid >> ttt_O & 1 << i ? 'O' : 'X');
        }
        else PRINT("_");
    }
    PRINT("\n");
}

char ttt_get_winner(TTTClient *client, TTTUser *winner)
{
    if ((client->grid >> ttt_Combine & 511) == 511)
    {
        *winner = ttt_Combine;
        return 1;
    }

    for (int i = 0; i < 8; ++i)
    {
        if ((client->grid >> ttt_O & patterns[i]) == patterns[i]) 
        {
            *winner = ttt_O;
            return 1;
        }
        else if ((client->grid >> ttt_X & patterns[i]) == patterns[i])
        { 
            *winner = ttt_X;
            return 1;
        }
    }

    *winner = ttt_Combine;
    return 0;
}

void free_ttt_client(TTTClient *client)
{
    free_window_context(client->context);
    free(client);
}