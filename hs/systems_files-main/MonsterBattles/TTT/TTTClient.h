#ifndef TTT_WINDOW_H
#define TTT_WINDOW_H

#include "../TUI/Window.h"

enum SavedCanvasIndex
{
    EMPTY_TIC_TAC_TOE,
    BORDER,
    NO_BLINK_O,
    NO_BLINK_X,
    BLINK_O,
    BLINK_X,
    CLEAR_TIC_TAC_TOE,
    SCREEN_CLEAR,
    CONSOLE_PRINT,
    CLEAR_LINES
};

typedef enum
{
    ttt_O = 0,
    ttt_X = 9,
    ttt_Combine = 18
} TTTUser;

typedef struct 
{
    WindowContext *context;
    int grid; // 4 bytes - 32 bits - only need 27 bits 
    TTTUser user_char;
    size_t ttt_xpos;
    size_t ttt_ypos;
} TTTClient;

// 1 1 1 1 1 1 1 1 1
typedef short TTTPattern;
extern const TTTPattern patterns[8]; 

TTTClient *make_ttt_client(TTTUser user_char);

void draw_ttt_window(TTTClient *client);

char ttt_is_complete(TTTClient *client);

char ttt_set_value(TTTClient *client, char row, char col, TTTUser user_char);

void debug_print_TTTClient(TTTClient *client);

void free_ttt_client(TTTClient *client);

char ttt_get_winner(TTTClient *client, TTTUser *winner);

#endif