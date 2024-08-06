#include "StyleChar.h"

#include <stdlib.h>
#include <stdio.h>
#include <wchar.h>

#include "Macros.h"

const TextStyle S_BOLD = 1;
const TextStyle S_ITALICS = 2;
const TextStyle S_UNDERLINE = 4;
const TextStyle S_BLINKING = 8;

StyleChar *make_style_char(wchar_t character, TextForeground foreground, TextBackground background, TextStyle style)
{
    StyleChar *style_char = (StyleChar*) malloc(sizeof(StyleChar));

    // could replace with init_style_char but dont know if it will inline
    style_char->character = character;
    style_char->foreground_color = foreground;
    style_char->background_color = background;
    style_char->style = style;

    return style_char;
}

StyleChar *make_empty_style_char()
{
    StyleChar *style_char = (StyleChar*) calloc(1, sizeof(StyleChar));
    style_char->character = NO_RENDER;

    return style_char;
}

void init_style_char(StyleChar *style_char, wchar_t character, TextForeground foreground, TextBackground background, TextStyle style)
{
    style_char->character = character;
    style_char->foreground_color = foreground;
    style_char->background_color = background;
    style_char->style = style;
}

void init_style_char_buffer(StyleChar *buffer, wchar_t *string, TextForeground foreground, TextBackground background, TextStyle style)
{
    while (*string)
    {
        buffer->character = *string;
        buffer->foreground_color = foreground;
        buffer->background_color = background;
        buffer->style = style;
        
        ++buffer;
        ++string;
    }
}

void init_empty_style_char(StyleChar *style_char)
{
    init_style_char(style_char, NO_RENDER, 0, 0, 0);
}


void debug_print_style_char(StyleChar *style_char)
{
    PRINTF("schar[.fg=%d, .bg=%d, .style=%d, .char=%lc]\n", style_char->foreground_color, style_char->background_color, (int) style_char->style, style_char->character);
}

// has to be fast, 80-20 rule. this is part of the 20

void write_style_char(StyleChar *style_char, wchar_t buffer[STYLE_CHAR_BUFFER])
{
    if (style_char->character == NO_RENDER) 
    {
        wcpcpy(buffer, CONSOLE_FORWARD);
        return;
    }
    // 0000 0001 0010 0011 0100 0101 0110 0111 
    // 1000 1001 1010 1011 1100 1101 1110 1111
    const char rightmost_table[16] = { -1, 0, 1, 0, 2, 0, 1, 0, 
                                        3, 0, 1, 0, 2, 0, 1, 0 }; // symmetrical -- optimizable? 
    const char count_table[16] = { 0, 1, 1, 2, 1, 2, 2, 3,
                                   1, 2, 2, 3, 2, 3, 3, 4 };
    const int style_lookup[4] = { 1, 3, 4, 5 };

    const char count = count_table[style_char->style];
    int styles[count];
    TextStyle cpy = style_char->style;

    for (int i = 0; i < count; ++i)
    {
        styles[i] = style_lookup[rightmost_table[cpy]];
        cpy &= ~(1 << rightmost_table[cpy]);
    }

    switch (count)
    {
        case 0:
        {
            swprintf(buffer, STYLE_CHAR_BUFFER, L"\033[%d;%dm%lc\033[0m", style_char->foreground_color, style_char->background_color, style_char->character);
            return;
        }
        case 1:
        {
            swprintf(buffer, STYLE_CHAR_BUFFER, L"\033[%d;%d;%dm%lc\033[0m", styles[0], style_char->foreground_color, style_char->background_color, style_char->character);
            return;
        }
        case 2:
        {
            swprintf(buffer, STYLE_CHAR_BUFFER, L"\033[%d;%d;%d;%dm%lc\033[0m", styles[0], styles[1], style_char->foreground_color, style_char->background_color, style_char->character);
            return;
        }
        case 3:
        {
            swprintf(buffer, STYLE_CHAR_BUFFER, L"\033[%d;%d;%d;%d;%dm%lc\033[0m", styles[0], styles[1], styles[2], style_char->foreground_color, style_char->background_color, style_char->character);
            return;
        }
        case 4:
        {
            swprintf(buffer, STYLE_CHAR_BUFFER, L"\033[%d;%d;%d;%d;%d;%dm%lc\033[0m", styles[0], styles[1], styles[2], styles[3], style_char->foreground_color, style_char->background_color, style_char->character);
            return;
        }
        default:
        {
            PRINT("UNEXPECTED ERROR\n"); // TODO: Better error message
            exit(1);
        }
    }
}

void print_style_line(StyleChar *style_line, size_t line_size, wchar_t end_char)
{
    wchar_t buffer[STYLE_CHAR_BUFFER];
    for (int i = 0; i < line_size; ++i)
    {
        write_style_char(style_line + i, buffer);
        PRINTF("%ls", buffer);
    }
    if (end_char) PRINTF("%c", end_char);
}