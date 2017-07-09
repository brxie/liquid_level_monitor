#ifndef __VIEW_H__
#define __VIEW_H__
#include "pcd8544.h"
#include "stm8s.h"
#include <stdlib.h>

void draw_layout();
void draw_level(float prct);
void draw_percent(uint8_t prct);
void draw_stats(uint16_t last, uint16_t max);

#endif