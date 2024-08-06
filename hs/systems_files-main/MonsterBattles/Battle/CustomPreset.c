#include "CustomPreset.h"

#include <stdlib.h>
#include "../TUI/Preset.h"

#define TOTAL_HEALTH_BAR 15

Canvas *generate_party_canvas(size_t width, size_t height, _STYLE_TEXT_SETTING_PARAMETERS)
{
    Canvas *border_canvas = generate_border(width, height, L'─', L'│', L'╭', L'╮', L'╰', L'╯', foreground, background, style);
    Canvas *hori_canvas = generate_horizontal_line(L'─', width, L'├', L'┤', foreground, background, style);
    Canvas *vert_canvas = generate_vertical_line(L'│', height, L'┬', L'┴', foreground, background, style);

    size_t col, row;
    canvas_get_position(border_canvas, canvas_middle, &col, &row);
    set_canvas_row(border_canvas, (StyleChar*) hori_canvas->characters, hori_canvas->width, row, 0);
    set_canvas_col(border_canvas, (StyleChar*) vert_canvas->characters, vert_canvas->height, col, 0);

    StyleChar *mid_char = make_style_char(L'┼', foreground, background, style);
    set_canvas_char(border_canvas, row, col, mid_char);

    free(mid_char);
    free_canvas(vert_canvas);
    free_canvas(hori_canvas);

    return border_canvas;
}

#include <wchar.h>

Canvas *generate_health_bar(size_t cur_health, size_t total_health)
{
    int bars = (double) cur_health / total_health * (TOTAL_HEALTH_BAR - 1) + 1;

    wchar_t *buffer[1];
    buffer[0] = malloc(sizeof(wchar_t) * TOTAL_HEALTH_BAR);
    for (int i = 0; i < TOTAL_HEALTH_BAR; ++i)
    {
        buffer[0][i] = i < bars ? L'■' : L'▢';
    }

    Canvas *canvas = generate_canvas(buffer, 1, TOTAL_HEALTH_BAR, f_white, b_black, S_BOLD);

    free(buffer[0]);
    return canvas;
}