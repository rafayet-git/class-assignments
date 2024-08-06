#include "Canvas.h"

#include <string.h>
#include <stdlib.h>
#include <wchar.h>

Canvas *make_canvas(size_t width, size_t height, CanvasCharacterOption option)
{
    Canvas *canvas = (Canvas*) malloc(sizeof(Canvas));
    canvas->width = width;
    canvas->height = height;
    canvas->choice = option;

    if (option == use_style_char)
    {
        char *buffer = (char*) malloc(sizeof(StyleChar) * width * height);

        for (int i = 0; i < width * height; ++i)
            *(wchar_t*) (buffer + (offsetof(StyleChar, character) + i * sizeof(StyleChar))) = NO_RENDER; // dont u love C

        canvas->characters = (void* ) buffer; 
    }
    else
    {
        wchar_t *buffer = (wchar_t*) malloc(sizeof(wchar_t) * width * height);
        for (int i = 0; i < width * height; ++i) buffer[i] = L' ';

        canvas->characters = (void* ) buffer;
    }

    return canvas;
}

StyleChar *get_canvas_row(Canvas *canvas, size_t row_index)
{
    if (canvas->choice == use_raw_char) return NULL;

    return (StyleChar*) canvas->characters + row_index * canvas->width;
}

StyleChar *get_canvas_char(Canvas *canvas, size_t row_index, size_t col_index)
{
    return get_canvas_row(canvas, row_index) + col_index;
}

int set_canvas_row(Canvas *canvas, StyleChar *buffer, size_t buffer_size, size_t row, size_t offset)
{
    if (canvas->choice == use_raw_char || buffer_size + offset > canvas->width) return -1;
    memcpy(get_canvas_char(canvas, row, offset), buffer, buffer_size * sizeof(StyleChar));
    return 0;
}

int set_canvas_col(Canvas *canvas, StyleChar *buffer, size_t buffer_size, size_t col, size_t offset)
{

    if (canvas->choice == use_raw_char || buffer_size + offset > canvas->height) return -1; // err - too big
    StyleChar *src = get_canvas_char(canvas, offset, col);
    for (int i = 0; i < buffer_size; ++i, src += canvas->width)
    {
        memcpy(src, buffer + i, sizeof(StyleChar));
    }
    return 0;
}

int set_canvas_char(Canvas *canvas, size_t row_index, size_t col_index, StyleChar *style_char)
{
    if (canvas->choice == use_raw_char || row_index > canvas->height && col_index > canvas->width) return -1;
    memcpy(get_canvas_char(canvas, row_index, col_index), style_char, sizeof(StyleChar));
    return 0;
}

void debug_print_canvas(Canvas *canvas, char output_canvas)
{
    PRINTF("Canvas[%d:%d]\n", canvas->width, canvas->height);
    if (!output_canvas) return;
    for (int i = 0; i < canvas->height; ++i)
    {
        println_style_line(get_canvas_row(canvas, i), canvas->width);
    }
}

void canvas_get_position(Canvas *canvas, CanvasPosition position, size_t *x, size_t *y)
{
    *x = position % 3 ? position % 3 >> 1 ? canvas->width : canvas->width / 2 : 0;
    *y = position / 3 ? position / 6 ? canvas->height : canvas->height / 2 : 0;
}

void free_canvas(Canvas *canvas)
{
    free(canvas->characters);
    free(canvas);
}