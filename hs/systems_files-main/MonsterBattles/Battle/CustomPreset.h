#ifndef BATTLE_CUSTOM_PRESET_H
#define BATTLE_CUSTOM_PRESET_H

#include <stddef.h>
#include "../TUI/Canvas.h"

#define _STYLE_TEXT_SETTING_PARAMETERS TextForeground foreground, TextBackground background, TextStyle style

Canvas *generate_party_canvas(size_t width, size_t height, _STYLE_TEXT_SETTING_PARAMETERS);

Canvas *generate_health_bar(size_t cur_health, size_t total_health);

#endif 