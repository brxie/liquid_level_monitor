#include "view.h"
#include "stats.h"

char buff[10];

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
    
    uint8_t x = 28; uint8_t y = 0;
    uint8_t offset = 0;
    pcd8544_fill_rect(28, 0, XSIZE-x, 18, 0);
    set_curr_pos(x, y);
    _itoa(prct, buff, 10);
    pcd8544_print_big(buff);
    offset = (x/8) + 5;
    if (prct>9) {offset+=2;}
    if (prct>99) {offset+=3;}
    set_curr_pos(offset, y+1);
    pcd8544_print("%");
    pcd8544_refresh();
}

void draw_stats(uint16_t cap, uint16_t used, uint16_t free) {
    uint8_t x = 5; uint8_t y = 3;

    /* clear statistics area on each refresh */
    pcd8544_fill_rect((x-1)*8, y*8, 55, 25, 0);

    set_curr_pos(x, y);
    pcd8544_print("USE:  ");
    _itoa(get_space_used(), buff, 10);
    pcd8544_print(buff);

    set_curr_pos(x, y+1);
    pcd8544_print("FREE: ");
    _itoa(get_space_left(), buff, 10);
    pcd8544_print(buff);
}

void render_main_menu(uint8_t percent_fill, uint16_t tank_cap, uint16_t last, uint16_t max) {
    draw_layout();
    draw_stats(tank_cap, last, max);
    draw_percent(percent_fill);
    draw_level(percent_fill);
}

void render_settings() {
    pcd8544_cls_soft();
    set_curr_pos(3, 0);
    pcd8544_print("CALIB:");

    _itoa(get_tank_cap(), buff, 10);
    set_curr_pos(0, 2);
    pcd8544_print(" C:");
    pcd8544_print(buff);
    
    _itoa(315, buff, 10);
    set_curr_pos(0, 3);
    pcd8544_print(" M:");
    pcd8544_print(buff);
    
    _itoa(400, buff, 10);
    set_curr_pos(0, 4);
    pcd8544_print(" AS:");
    pcd8544_print(buff);

    pcd8544_refresh();
}

void render_stats() {
    pcd8544_cls_soft();
    set_curr_pos(0, 0);
    pcd8544_print("STATS:");
    pcd8544_refresh();

    set_curr_pos(0, 2);
    pcd8544_print("C: ");
    _itoa(get_tank_cap(), buff, 10);
    pcd8544_print(buff);

    set_curr_pos(0, 3);
    pcd8544_print("U: ");
    _itoa(get_space_used(), buff, 10);
    pcd8544_print(buff);

    set_curr_pos(0, 4);
    pcd8544_print("F: ");
    _itoa(get_space_left(), buff, 10);
    pcd8544_print(buff);

    set_curr_pos(0, 5);
    pcd8544_print("A: ");
    _itoa(get_adc_val(), buff, 10);
    pcd8544_print(buff);
}