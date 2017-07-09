#include "view.h"


void draw_layout() {
    pcd8544_fill_rect(26, 20, 58, 1, 1);
    pcd8544_fill_rect(26, 20, 1, 30, 1);
    pcd8544_refresh();
}

void draw_level(float prct) {
    uint8_t width = 25; uint8_t height = 48;
    uint8_t x; uint8_t y;
    uint8_t set = 1;
    float step = (height - 1)/(float)100;
    pcd8544_rect(0, 0, width, height, 1);
    for(x=1; x<width-1; x++){
        for(y=0; y<height-1; y++){
            set = !set;
            draw_pixel(x, y, set);
        }
    }
    pcd8544_fill_rect(1, 0, width-2, step*(100-prct), 0);
    pcd8544_refresh();
}

void draw_percent(uint8_t prct) {
    char buffer[10];
    uint8_t x = 28; uint8_t y = 0;
    uint8_t offset = 0;
    pcd8544_fill_rect(28, 0, XSIZE-x, 18, 0);
    set_curr_pos(x, y);
    _itoa(prct, buffer, 10);
    pcd8544_print_big(buffer);
    offset = (x/8) + 5;
    if (prct>9) {offset+=2;}
    if (prct>99) {offset+=3;}
    set_curr_pos(offset, y+1);
    pcd8544_print("%");
    pcd8544_refresh();
}

void draw_stats(uint16_t last, uint16_t max) {
    uint8_t x = 5; uint8_t y = 3;
    char buffer[10];
    pcd8544_fill_rect((x-1)*8, y*8, 55, 25, 0);
    set_curr_pos(x, y);
    pcd8544_print("Last: ");
    _itoa(last, buffer, 10);
    pcd8544_print(buffer);
    set_curr_pos(x, y+1);
    pcd8544_print("Max: ");
    _itoa(max, buffer, 10);
    pcd8544_print(buffer);
}