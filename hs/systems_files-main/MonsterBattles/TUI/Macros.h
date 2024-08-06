#ifndef TUI_MACROS_H
#define TUI_MACROS_H

#define CONSOLE_FORWARD L"\033[1C"
#define CONSOLE_RESET L"\033[0m"
#define CONSOLE_ERASE_LINE L"\033[K"
#define CONSOLE_SAVE_POSITION L"\033[s"
#define CONSOLE_RESTORE_POSITION L"\033[u"

// less useful
#define CONSOLE_DOWN(n) L"\033[" #n "B"
#define CONSOLE_UP(n) L"\033[" #n "A"

#ifndef TUI_PRINT
#define TUI_PRINT

#define PRINT(string) wprintf(L ## string)
#define PRINTF(string, ...) wprintf(L ## string, __VA_ARGS__)

#endif

#endif