#include "Preset.h"

#include <wchar.h>
#include <string.h>
#include <stdlib.h>

Canvas *generate_canvas(wchar_t **canvas_text, size_t height, size_t width, _STYLE_TEXT_SETTING_PARAMETERS)
{
    Canvas *canvas = make_canvas(width, height, use_style_char);

    for (size_t i = 0; i < height; ++i)
    {
        init_style_char_buffer(get_canvas_row(canvas, i), canvas_text[i], foreground, background, style);
    }

    return canvas;
}

Canvas *generate_horizontal_line(wchar_t line_char, size_t width, wchar_t left_endpoint, wchar_t right_endpoint, _STYLE_TEXT_SETTING_PARAMETERS)
{
    Canvas *canvas = make_canvas(width, 1, use_style_char);
    left_endpoint = left_endpoint ? left_endpoint : line_char;
    right_endpoint = right_endpoint ? right_endpoint : line_char;
    init_style_char(get_canvas_row(canvas, 0), left_endpoint, foreground, background, style);
    for (int i = 1; i < width - 1; ++i)
    {
        init_style_char(get_canvas_row(canvas, 0) + i, line_char, foreground, background, style);
    }
    init_style_char(get_canvas_row(canvas, 0) + width - 1, right_endpoint, foreground, background, style);

    return canvas;
}

Canvas *generate_vertical_line(wchar_t line_char, size_t height, wchar_t top_endpoint, wchar_t bottom_endpoint, _STYLE_TEXT_SETTING_PARAMETERS)
{
    Canvas *canvas = make_canvas(1, height, use_style_char);
    top_endpoint = top_endpoint ? top_endpoint : line_char;
    bottom_endpoint = bottom_endpoint ? bottom_endpoint : line_char;
    init_style_char(get_canvas_char(canvas, 0, 0), top_endpoint, foreground, background, style);
    for (int i = 1; i < height - 1; ++i)
    {
        init_style_char(get_canvas_char(canvas, i, 0), line_char, foreground, background, style);
    }
    init_style_char(get_canvas_char(canvas, height - 1, 0), bottom_endpoint, foreground, background, style);

    return canvas;
}

Canvas *generate_border(size_t width, size_t height, wchar_t horizontal, wchar_t vertical, wchar_t top_left, wchar_t top_right, wchar_t bottom_left, wchar_t bottom_right, _STYLE_TEXT_SETTING_PARAMETERS)
{
    Canvas *canvas = make_canvas(width, height, use_style_char);

    // top and bottom row
    init_style_char(get_canvas_row(canvas, 0), top_left, foreground, background, style);
    init_style_char(get_canvas_row(canvas, height - 1), bottom_left, foreground, background, style);
    for (int i = 1; i < width - 1; ++i)
    {
        init_style_char(get_canvas_row(canvas, 0) + i, horizontal, foreground, background, style);
        init_style_char(get_canvas_row(canvas, height - 1) + i, horizontal, foreground, background, style);
    }
    init_style_char(get_canvas_row(canvas, 0) + width - 1, top_right, foreground, background, style);
    init_style_char(get_canvas_row(canvas, height - 1) + width - 1, bottom_right, foreground, background, style);

    // columns
    for (int i = 1; i < height - 1; ++i)
    {
        init_style_char(get_canvas_char(canvas, i, 0), vertical, foreground, background, style);
        init_style_char(get_canvas_char(canvas, i, width - 1), vertical, foreground, background, style);
    }

    return canvas;
}


Canvas *generate_clear_lines(size_t height)
{
    // \033[K
    Canvas *canvas = make_canvas(4, height, use_raw_char);

    for (int i = 0; i < height; ++i)
    {
        wcpcpy((wchar_t* ) (canvas->characters) + 4 * i, L"\033[K");
    }

    return canvas;
}

Canvas *generate_clear_screen()
{
    // \033[2J
    Canvas *canvas = make_canvas(5, 1, use_raw_char);
    wcpcpy((wchar_t *) canvas->characters, L"\033[2J");

    return canvas;
}

Canvas *generate_goto(size_t row, size_t col)
{
    // \033[y;xH
    wchar_t wstr[64];
    swprintf(wstr, 64, L"\033[%ld;%ldH", row, col);

    Canvas *canvas = make_canvas(wcslen(wstr) + 1, 1, use_raw_char);
    wcpcpy((wchar_t* ) canvas->characters, wstr);

    return canvas;
}

Canvas *generate_text(wchar_t **strings, size_t rows, size_t max_str_len)
{
    Canvas *canvas = make_canvas(max_str_len + 1, rows, use_raw_char);

    for (int i = 0; i < rows; ++i)
    {
        if (wcslen(strings[i]) > max_str_len)
        {
            free_canvas(canvas);
            return NULL;
        }
        else
        {
            wcscpy((wchar_t*) canvas->characters + (max_str_len + 1) * i, strings[i]);
        }
    }

    return canvas;   
}

Canvas *generate_character_canvas(size_t width, size_t height, wchar_t character, _STYLE_TEXT_SETTING_PARAMETERS)
{
    Canvas *canvas = (Canvas*) malloc(sizeof(Canvas));
    canvas->width = width;
    canvas->height = height;
    canvas->choice = use_style_char;

    StyleChar *style_char = make_style_char(character, foreground, background, style);

    StyleChar *buffer = (StyleChar*) malloc(sizeof(StyleChar) * width * height);

    for (int i = 0; i < width * height; ++i)
    {
        memcpy(buffer + i, style_char, sizeof(StyleChar));
    }

    free(style_char);
    canvas->characters = (void* ) buffer; 

    return canvas;
}