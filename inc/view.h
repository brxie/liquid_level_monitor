#ifndef __VIEW_H__
#define __VIEW_H__
#include "pcd8544.h"
#include "stm8s.h"
#include <stdlib.h>

void draw_layout();
void draw_level(float prct);
void draw_percent(uint8_t prct);
void draw_stats(uint16_t cap, uint16_t used, uint16_t free);
void render_main_menu(uint8_t percent_fill, uint16_t tank_cap, uint16_t last, uint16_t max);
void render_settings();
void render_stats();
#endif