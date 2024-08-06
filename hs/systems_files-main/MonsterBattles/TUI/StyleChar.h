#ifndef STYLE_CHAR_H
#define STYLE_CHAR_H

#include <stddef.h>

#define NO_RENDER L'\033' // use escape for escape char rendering

#ifndef TUI_PRINT
#define TUI_PRINT

#define PRINT(string) wprintf(L ## string)
#define PRINTF(string, ...) wprintf(L ## string, __VA_ARGS__)

#endif

/**
 * Basic format \033[aa;bb;cc;ee;ff;ggmC\033[0m which is at max 26 characters long including null terminator
*/
#define STYLE_CHAR_BUFFER 26

typedef enum
{
    f_black = 30,
    f_red,
    f_green,
    f_yellow,
    f_blue,
    f_magenta,
    f_cyan,
    f_white
} TextForeground;

typedef enum
{
    b_black = 40,
    b_red,
    b_green,
    b_yellow,
    b_blue,
    b_magenta,
    b_cyan,
    b_white
} TextBackground;

typedef unsigned char TextStyle;

extern const TextStyle S_BOLD;
extern const TextStyle S_ITALICS;
extern const TextStyle S_UNDERLINE;
extern const TextStyle S_BLINKING;

/**
 * represents a formatted char modified with escape sequence.
 * favors space over speed by not storing the string with escape sequence
 * why? sizeof(StyleChar) would likely be 26 bytes. Using StyleChar in a
 * large 2D grid would cause huge memory allocation. This version uses 
 * significantly less bytes (around 12 bytes).
*/
typedef struct
{
    TextForeground foreground_color;
    TextBackground background_color;
    TextStyle style;
    wchar_t character;
} StyleChar;

/**
 * creates a StyleChar on the heap and initializes it.
 * 
 * @arg foreground - text foreground color
 * @arg background - text background color
 * @arg style - bitset containing styles from S_BOLD, S_ITALICS, S_UNDERLINE, or S_BLINKING.
 * @return a StyleChar on the heap
*/
StyleChar *make_style_char(wchar_t character, TextForeground foreground, TextBackground background, TextStyle style);

/**
 * creates an empty StyleChar on the heap.
 * 
 * @return an empty StyleChar on the heap.
*/
StyleChar *make_empty_style_char();

/**
 * initializes a StyleChar on already allocated memory
 * @args style_char - address to allocated StyleChar
 * @arg character - the character to store in the StyleChar
 * @arg foreground - text foreground color
 * @arg background - text background color
 * @arg style - bitset containing styles from S_BOLD, S_ITALICS, S_UNDERLINE, or S_BLINKING.
*/
void init_style_char(StyleChar *style_char, wchar_t character, TextForeground foreground, TextBackground background, TextStyle style);

/**
 * initializes a buffer of StyleChar with a string and sets appropriate settings
 * 
 * @arg buffer - buffer of uninitialized StyleChar
 * @arg string - wide string to be stored in the StyleChar buffer
 * @arg foreground - text foreground color
 * @arg background - text background color
 * @arg style - bitset containing styles from S_BOLD, S_ITALICS, S_UNDERLINE, or S_BLINKING.
*/
void init_style_char_buffer(StyleChar *buffer, wchar_t *string, TextForeground foreground, TextBackground background, TextStyle style);

/**
 * initializes a StyleChar to be empty
 * 
 * @arg style_char - address to allocated StyleChar
*/
void init_empty_style_char(StyleChar *style_char);

/**
 * prints the style_char contents for debugging
 * 
 * @arg style_char - Address to allocated StyleChar 
*/
void debug_print_style_char(StyleChar *style_char);

/**
 * converts a StyleChar to a printable string that is on the provided buffer.
 * 
 * @arg style_char - address to an initialized StyleChar
 * @arg buffer - the buffer to copy the formatted string to
*/
void write_style_char(StyleChar *style_char, wchar_t buffer[STYLE_CHAR_BUFFER]);

/**
 * utility function that prints a line of StyleChar.
 * 
 * @arg style_line - a buffer of StyleChar to be printed
 * @arg line_size - the size of the buffer
 * @arg end_char - char to print at the end
*/
void print_style_line(StyleChar *style_line, size_t line_size, wchar_t end_char);

#define println_style_line(style_line, line_size) print_style_line(style_line, line_size, L'\n')

#endif