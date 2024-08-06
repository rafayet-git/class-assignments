#ifndef TUI_PRESET_H
#define TUI_PRESET_H

#include "Canvas.h"

// is this bad practice? probably, just saves me on typing
#define _STYLE_TEXT_SETTING_PARAMETERS TextForeground foreground, TextBackground background, TextStyle style

/**
 * generates a canvas with the same style settings from a buffer of wide strings.
 * 
 * @arg canvas_text - a buffer of wide strings to bestored in the canvas
 * @arg height - the length of the buffer aka the number of rows of wide strings
 * @arg width - the total width of the canvas. This should be greater than or equal to the max string length in the buffer
 * @arg foreground - the foreground color of the text
 * @arg background - the background color of the text
 * @arg style - the TextStyle of the text
 * @return a pointer to a canvas object on the heap with the provided data
*/
Canvas *generate_canvas(wchar_t **canvas_text, size_t height, size_t width, _STYLE_TEXT_SETTING_PARAMETERS);

/**
 * generates a canvas that draws a repeated character horizontally
 * 
 * @arg line_char - the main character of the repeated horizontal sequence
 * @arg width - the width of the horizontal sequence
 * @arg left_endpoint - the character at the left endpoint. set this to 0 if there is no custom left endpoint character
 * @arg right_endpoint - the character at the right endpoint. set this to 0 if there is no custom right endpoint character
 * @arg foreground - the foreground color of the text
 * @arg background - the background color of the text
 * @arg style - the TextStyle of the text
 * @return a pointer to a canvas object on the heap with the provided data
*/
Canvas *generate_horizontal_line(wchar_t line_char, size_t width, wchar_t left_endpoint, wchar_t right_endpoint, _STYLE_TEXT_SETTING_PARAMETERS);

/**
 * generates a canvas that draws a repeated character vertically
 * 
 * @arg line_char - the main character of the repeated vertical sequence
 * @arg height - the height of the vertical sequence
 * @arg top_endpoint - the character at the top endpoint. set this to 0 if there is no custom top endpoint character
 * @arg bottom_endpoint - the character at the bottom endpoint. set this to 0 if there is no custom bottom endpoint character
 * @arg foreground - the foreground color of the text
 * @arg background - the background color of the text
 * @arg style - the TextStyle of the text
 * @return a pointer to a canvas object on the heap with the provided data
*/
Canvas *generate_vertical_line(wchar_t line_char, size_t height, wchar_t top_endpoint, wchar_t bottom_endpoint, _STYLE_TEXT_SETTING_PARAMETERS);

/**
 * generates a border from the provided characters and size
 * 
 * @arg width - the width of the border
 * @arg height - the height of the border
 * @arg horizontal - the character for the horizontal line segments
 * @arg vertical - the character for the vertical line segments
 * @arg top_left - the character for the top left corner
 * @arg top_right - the character for the top right corner
 * @arg bottom_left - the character for the bottom left corner
 * @arg bottom_right - the character for the bottom right corner
 * @arg foreground - the foreground color of the text
 * @arg background - the background color of the text
 * @arg style - the TextStyle of the text
 * @return a pointer to a canvas object on the heap with the provided data
*/
Canvas *generate_border(size_t width, size_t height, wchar_t horizontal, wchar_t vertical, wchar_t top_left, wchar_t top_right, wchar_t bottom_left, wchar_t bottom_right, _STYLE_TEXT_SETTING_PARAMETERS);

/**
 * generates a canvas that clears a variable number of lines
 * 
 * @arg height - the number of lines to clear
 * @return a pointer to a canvas object on the heap with the provided data
*/
Canvas *generate_clear_lines(size_t height);

/**
 * generates a canvas that clears the screen and moves the cursor to (1,1) on the terminal
 * 
 * @return a pointer to a canvas object on the heap with the provided data
*/
Canvas *generate_clear_screen();

/**
 * generates a canvas that moves the cursor to (row, col) on the terminal
 * 
 * @arg row - the row to move to
 * @arg col - the col to move to
 * @return a pointer to a canvas object on the heap with the provided data
*/
Canvas *generate_goto(size_t row, size_t col);

/**
 * generates a canvas containing the plain text
 * 
 * @arg strings - a buffer of wide strings 
 * @arg rows - the number of rows in the canvas and also the length of the buffer
 * @arg max_str_len - the number of cols in the canvas and should be greater than the maximum string length
 * @return a pointer to a canvas object on the heap with the provided data
*/
Canvas *generate_text(wchar_t **strings, size_t rows, size_t max_str_len);

/**
 * generate a canvas containing of size width and height. each value in the canvas will be the same.
 * 
 * @arg width - the width of the canvas
 * @arg height - the height of the canvas
 * @arg character - the character to fill the canvas with
 * @arg foreground - the foreground color of the text
 * @arg background - the background color of the text
 * @arg style - the TextStyle of the text
 * @return a pointer to a canvas object on the heap with the provided data
*/
Canvas *generate_character_canvas(size_t width, size_t height, wchar_t character, _STYLE_TEXT_SETTING_PARAMETERS);

#endif