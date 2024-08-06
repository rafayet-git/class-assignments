#ifndef TUI_WINDOW_H
#define TUI_WINDOW_H

#include <stddef.h>

#include "Instruction.h"

#define CANVAS_BUFFER_LENGTH 25

/**
 * A struct storing useful data. while it is not necessary, it is very useful
 * 
 * @note should be instantiated using make_window_context function
 * @note do not use free() on the WindowContext* as it will lead to a memory leak. use free_window_context function instead.
 * @note it is useful to create an enumerators corresponding to the saved canvases as it is more expressive in the code
 * 
 * @data width - the width of the terminal upon the call of make_window_context function
 * @data height - the height of the terminal upon the call of make_window_context function
 * @data queue - a pointer to the associated instruction queue
 * @data saved_canvases - an array of saved Canvas objects to reduce instantiation and promote reusability. should be filled with commonly
 * used or large Canvas objects. 
*/
typedef struct 
{
    size_t width;
    size_t height;

    InstructionQueue *queue;
    Canvas *saved_canvases[CANVAS_BUFFER_LENGTH];
} WindowContext;

/**
 * creates and initializes a WindowContext
 * 
 * @return a pointer to the WindowContext object on the heap
*/
WindowContext *make_window_context();

/**
 * saves a canvas into a WindowContext
 * 
 * @note the canvas should be dynamically allocated to extend its lifetime. otherwise, it will be a dangling pointer
 * 
 * @arg context - a pointer to the WindowContext
 * @arg index - the index of the saved canvases that the canvas will be saved to
 * @arg canvas - the canvas to save.
*/
void set_saved_canvas(WindowContext *context, const size_t index, Canvas *canvas);

/**
 * frees the window context appropriately
 * 
 * @arg context - the WindowContext on the heap to free.
*/
void free_window_context(WindowContext *context);

/**
 * pushes a saved canvas onto the instruction queue appropriately
 * 
 * @note this function simply wraps push_instruction except that do_free_mem is always false to preserve the saved canvases
 * 
 * @arg context - the WindowContext that stores the saved canvases
 * @arg index - the index of the saved canvases
 * @arg x_offset - the x position to start drawing the canvas
 * @arg y_offset - the y position to start drawing the canvas
*/
void push_saved_canvas_instruction(WindowContext *context, const size_t index, size_t x_offset, size_t y_offset);

#endif