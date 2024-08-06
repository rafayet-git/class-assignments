#ifndef TUI_CANVAS_H
#define TUI_CANVAS_H

#include <stddef.h>
#include "StyleChar.h"

typedef enum
{
    use_style_char,
    use_raw_char
} CanvasCharacterOption;

/**
 * contains data involving the width, height or the canvas
 * also contains a void *character which can either be StyleChar* or wchar_t*
 * the type of the void* is determined by the CanvasCharacterOption.
 * 
 * @invariant use_style_char means that characters should be cast to StyleChar*
 * @invariant use_raw_char means that characters should be cast to wchar_t*
*/
typedef struct
{
    size_t width;
    size_t height;

    CanvasCharacterOption choice;
    void *characters;
} Canvas;

typedef enum 
{
    canvas_top_left, 
    canvas_top_middle, 
    canvas_top_right, 

    canvas_middle_left, 
    canvas_middle, 
    canvas_middle_right, 

    canvas_bottom_left,
    canvas_bottom_middle,
    canvas_bottom_right
} CanvasPosition;

/**
 * creates a Canvas on the heap and initializes it
 * 
 * @arg width - the width of the canvas
 * @arg height - the height of the canvas
 * @arg option - the CanvasCharacterOption of either a style wchar or a raw wchar
 * @return a pointer to the allocated Canvas
*/
Canvas *make_canvas(size_t width, size_t height, CanvasCharacterOption option);

/**
 * returns a StyleChar pointer to the row of the canvas. The StyleChar must have the use_style_char option
 * 
 * @arg canvas - a pointer to the canvas object being accessed
 * @arg row_index - the row index of the canvas to access
 * @return the pointer to the row of StyleChar or NULL if the StyleChar has CanvasCharacterOption::use_raw_char
*/
StyleChar *get_canvas_row(Canvas *canvas, size_t row_index);

/**
 * returns a pointer to a specific StyleChar from the row and col index. The StyleChar must have the use_style_char option
 * 
 * @arg canvas - a pointer to the canvas object being accessed
 * @arg row_index -  the row index of the canvas to access
 * @arg col_index - the col index of the canvas to access
 * @return the pointer to the StyleChar or NULL if the StyleChar has CanvasCharacterOption::use_raw_char
*/
StyleChar *get_canvas_char(Canvas *canvas, size_t row_index, size_t col_index);

/**
 * sets a canvas row with a buffer of StyleChar. The StyleChar must have the use_style_char option
 * 
 * @arg canvas - a pointer to the canvas object being accessed
 * @arg buffer - the buffer of StyleChar objects to set the canvas row
 * @arg buffer_size - the size of the buffer
 * @arg row - the row of Canvas to set
 * @arg offset - the offset in the row to begin setting (acts like a col index)
 * @return returns 0 on success. returns -1 on failure
*/
int set_canvas_row(Canvas *canvas, StyleChar *buffer, size_t buffer_size, size_t row, size_t offset);

/**
 * sets a canvas col with a buffer of StyleChar. The StyleChar must have the use_style_char option
 * 
 * @arg canvas - a pointer to the canvas object being accessed
 * @arg buffer - the buffer of StyleChar objects to set the canvas row
 * @arg buffer_size - the size of the buffer
 * @arg col - the col of Canvas to set
 * @arg offset - the offset in the col to begin setting (acts like a row index)
 * @return returns 0 on success. returns -1 on failure
*/
int set_canvas_col(Canvas *canvas, StyleChar *buffer, size_t buffer_size, size_t col, size_t offset);

/**
 * sets a value in the Canvas with a StyleChar. The StyleChar must have the use_style_char option
 * 
 * @arg canvas - a pointer to the canvas object being accessed
 * @arg row_index - the index of the row to set
 * @arg col_index - the index of the col to set
 * @arg style_char - the StyleChar to write
 * @return returns 0 on success. returns -1 on failure
*/
int set_canvas_char(Canvas *canvas, size_t row_index, size_t col_index, StyleChar *style_char);

/**
 * prints the canvas contents for debugging
 * 
 * @arg canvas - a pointer to the canvas object being printed
 * @arg output_canvas - a boolean stating if the style_char should be printed
*/
void debug_print_canvas(Canvas *canvas, char output_canvas);

/**
 * function that returns the relative position to a canvas
 * 
 * @arg canvas - a pointer to the canvas object 
 * @arg position - a CanvasPosition value denoting useful relative positioning
 * @arg x - a pointer to a size_t to set with the x relative position to the top-left of the canvas
 * @arg y - a pointer to a size_t to set with the y relative position to the top-left of the canvas
*/
void canvas_get_position(Canvas *canvas, CanvasPosition position, size_t *x, size_t *y);

void free_canvas(Canvas *canvas);

#endif