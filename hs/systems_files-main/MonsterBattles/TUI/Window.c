#include "Window.h"

#include <stdlib.h>
#include <locale.h>
#include <sys/ioctl.h>
#include <unistd.h>

WindowContext *make_window_context()
{
    setlocale(LC_ALL, "");
    WindowContext *context = (WindowContext*) malloc(sizeof(WindowContext));

    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    context->width = w.ws_col;
    context->height = w.ws_row;

    context->queue = make_instruction_queue();

    for (int i = 0; i < CANVAS_BUFFER_LENGTH; ++i)
    {
        context->saved_canvases[i] = NULL;
    }

    return context;
}

void set_saved_canvas(WindowContext *context, const size_t index, Canvas *canvas)
{
    context->saved_canvases[index] = canvas;
}

void free_window_context(WindowContext *context)
{
    for (int i = 0; i < CANVAS_BUFFER_LENGTH; ++i)
    {
        if (context->saved_canvases[i]) free_canvas(context->saved_canvases[i]);
    }
    free_queue(context->queue);
    free(context);
}

void push_saved_canvas_instruction(WindowContext *context, const size_t index, size_t x_offset, size_t y_offset)
{
    push_instruction(context->queue, context->saved_canvases[index], x_offset, y_offset, 0);
}