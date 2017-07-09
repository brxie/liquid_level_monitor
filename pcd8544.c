/*
 * pcd8544.c - functions for work with display controller
 *
 * Copyright 2015 Edward V. Emelianoff <eddy@sao.ru, edward.emelianoff@gmail.com>
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston,
 * MA 02110-1301, USA.
 */

/*
 * we have two modes: direct write into LCD (with local buffer update) - for text
 * and refresh whole buffer - for graphics
 * all writings are in horizontal addressing mode
 */

#include "pcd8544.h"

// here should be functions spiWrite(uint8_t *data, bufsz_t size) & spi_write_byte(uint8_t onebyte)
// max SPI speed is 4MHz
//#include "spi.h"
/* here are functions & macros for changing command pins state:
 *   SET_DC()    - set D/~C pin high (data)
 *   CLEAR_DC()  - clear D/~C (command)
 *   CHIP_EN()   - clear ~SCE
 *   CHIP_DIS()  - set ~SCE (disable chip)
 *   CLEAR_RST() - set 1 on RST pin (SHOULD BE 0 AT START - USE PULLING RESISTOR!!!)
 */

const scrnsz_t LTRS_IN_ROW = XSIZE / LTR_WIDTH;
const scrnsz_t ROW_MAX = YSIZE / 8;
// array for fast pixel set/reset
const uint8_t const pixels_set[] = {1,2,4,8,0x10,0x20,0x40,0x80};
const uint8_t const pixels_reset[] = {0xfe,0xfd,0xfb,0xf7,0xef,0xdf,0xbf,0x7f};
/**
 * I use horizontal addressing of PCD8544, so data in buffer
 * stored line by line, each byte is 8 vertical pixels (LSB upper)
 *
 * As refresh speed is fast enough, I don't use partial update for graphics
 * (but use for letters)
 */
#define DISPLAYBUFSIZE   (XSIZE*YCHARSZ)
static uint8_t displaybuf[DISPLAYBUFSIZE];

// current letter coordinates - for "printf"
static scrnsz_t cur_x = 0, cur_y = 0;

void pcd8544_setbias(uint8_t val){
	CMD(PCD8544_EXTENDEDINSTRUCTION);
	SETBIAS(val);
	CMD(PCD8544_DEFAULTMODE);
}

void pcd8544_setvop(uint8_t val){
	CMD(PCD8544_EXTENDEDINSTRUCTION);
	SETVOP(val);
	CMD(PCD8544_DEFAULTMODE);
}

void pcd8544_settemp(uint8_t val){
	CMD(PCD8544_EXTENDEDINSTRUCTION);
	SETTEMP(val);
	CMD(PCD8544_DEFAULTMODE);
}

/**
 * Init SPI & display
 */
void pcd8544_init(){
	spi_init();
	CHIP_DIS();
	SET_DC();
	LCD_RST();
	// msleep(10);
	CLEAR_RST(); // set ~RST to 1, performing out of RESET stage
//	CMD(0x21); CMD(0xc8); CMD(0x06); CMD(0x13); CMD(0x20); CMD(0x0c);

	// set LCD to optimal mode by datasheet: bias 1/48 (n=4), Vlcd 6.06 (Vop=50), normal Tcorr (1)
	CMD(PCD8544_EXTENDEDINSTRUCTION);
	SETBIAS(BIAS);
	SETVOP(VOP);
	SETTEMP(TEMP);
	// return to regular instructions set, horizontal addressing & prepare normal display mode
	CMD(PCD8544_DEFAULTMODE);
	CMD(PCD8544_DISPLAYNORMAL);

	pcd8544_cls();
}

static void spi_init() {
	SPI_DeInit();
	gpio_config();
	SPI_Init(SPI_FIRSTBIT_MSB,
			SPI_BAUDRATEPRESCALER_32,
			SPI_MODE_MASTER,          
			SPI_CLOCKPOLARITY_HIGH,   
			SPI_CLOCKPHASE_2EDGE,     
			SPI_DATADIRECTION_2LINES_FULLDUPLEX, 
			SPI_NSS_HARD,                        
			0x00                                 
			);
	SPI_Cmd(ENABLE);
}

static void gpio_config()
{
	LCD_PORT->DDR |= LCD_DC_PIN | LCD_CE_PIN | LCD_RST_PIN;
	LCD_PORT->CR1 |= LCD_DC_PIN | LCD_CE_PIN | LCD_RST_PIN;
	LCD_PORT->CR2 |= LCD_DC_PIN | LCD_CE_PIN | LCD_RST_PIN;
}

static void spi_send_byte(uint8_t data){
	while(SPI->SR & SPI_SR_BSY);
	SPI->ICR = 0;
	SPI_SendData(data);
	while(!(SPI->SR & SPI_SR_RXNE));
	SPI->DR;
}

/**
 * Send command (cmd != 0) or data (cmd == 0) byte
 */
void pcd8544_send_byte(uint8_t byte, uint8_t cmd){
	CHIP_EN();
	if(cmd)
		CLEAR_DC();
	else
		SET_DC();
	spi_send_byte(byte);
}

/**
 * Send data sequence
 */
void pcd8544_send_data(uint8_t *data, bufsz_t size, uint8_t cmd){
  uint16_t i;
	CHIP_EN();
	if(cmd)
		CLEAR_DC();
	else
		SET_DC();

	for (i=0; i < size; ++i) {
		spi_send_byte(data[i]);
	}
	CHIP_DIS();
}

void draw_pixel(scrnsz_t x, scrnsz_t y, uint8_t set){
	bufsz_t idx;
	if(bad_coords(x,y)) return;
	idx = x + (y/8) * XSIZE;
	y %= 8;
	if(set)
		displaybuf[idx] |= pixels_set[y];
	else
		displaybuf[idx] &= pixels_reset[y];
}

void pcd8544_cls(){
	memset(displaybuf, 0, DISPLAYBUFSIZE);
	cur_x = cur_y = 0;
	pcd8544_refresh();
}

void pcd8544_cls_soft(){
	memset(displaybuf, 0, DISPLAYBUFSIZE);
	cur_x = cur_y = 0;
}

/**
 * send full data buffer onto display
 */
void pcd8544_refresh(){
	SETXADDR(0);
	SETYADDR(0);
	DBUF(displaybuf, DISPLAYBUFSIZE);
}

/**
 * draw letter at x,y position in char coordinates (XCHARSZ x YCHARSZ)
 * @return 0 if fail
 */
int pcd8544_put(uint8_t koi8, scrnsz_t x, scrnsz_t y){
	uint8_t *symbol;
	bufsz_t idx;
	if(x >= XCHARSZ || y >= YCHARSZ) return 0;
	if(koi8 < 32) return 0;
	symbol = (uint8_t*)letter(koi8);
	x *= LTR_WIDTH;
	idx = x + y*XSIZE;
	// put letter into display buffer
	memcpy(&displaybuf[idx], symbol, LTR_WIDTH);
	// and show it on display
	SETXADDR(x);
	SETYADDR(y);
	DBUF(symbol, LTR_WIDTH);
	return 1;
}

int pcd8544_put_big(uint8_t koi8, scrnsz_t x, scrnsz_t y){
	uint8_t tmp_buff[XSIZE];
	uint8_t *symbol;
	uint8_t xpos = x;
	uint16_t i;
	bufsz_t idx;
	symbol = (uint8_t*)big_symbol(koi8);
	for (i=0; i < BIG_FONT_LEN; i += BIG_FONT_XSIZE) {
		memcpy(&tmp_buff, &symbol[i], BIG_FONT_XSIZE);
		xpos++;
		if (!(i % BIG_FONT_XSIZE) && (i != 0)) {
			xpos = x;
			y++;
		}
		idx = xpos + (y*XSIZE);
		memcpy(&displaybuf[idx], &symbol[i], BIG_FONT_XSIZE);
		SETYADDR(y);
		SETXADDR(xpos);
		DBUF(tmp_buff, BIG_FONT_XSIZE);
	}
	return 1;
}

void pcd8544_rect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t set)
{
	int16_t i;
	for (i=x; i<x+w; i++) {
		draw_pixel(i, y, set);
		draw_pixel(i, y+h-1, set);
	}
	for (i=y; i<y+h; i++) {
		draw_pixel(x, i, set);
		draw_pixel(x+w-1, i, set);
	}
}

void pcd8544_fill_rect(uint8_t x, uint8_t y, uint8_t w, uint8_t h, uint8_t set)
{
	int16_t i;
	for (i=x; i<x+w; i++) {
		int16_t j;
		for (j=y; j<y+h; j++) {
			draw_pixel(i, j, set);
		}
	}
}

uint8_t pcd8544_bitmap(uint8_t *bitmap, uint8_t x, uint8_t y, uint8_t w, uint8_t h)
{
	const uint8_t size = w * h;
	uint8_t xpos = 0;
	uint16_t i;
	uint8_t tmp_buff[XSIZE];
	bufsz_t idx;
	for (i=0; i < (w*h); i += w) {
		memcpy(&tmp_buff, &bitmap[i], w);
		if (!(i % w) && (i != 0)) {
			xpos = x;
			y++;
		}
		idx = xpos + (y*XSIZE);
		memcpy(&displaybuf[idx], &bitmap[i], w);
		SETYADDR(y);
		SETXADDR(xpos);
		DBUF(tmp_buff, w);
		xpos++;
	}
	return 1;
}

/**
 * put char into current position or next line; return char if couldn't be printed
 * (if OK return 0 or '\n' if newline was made)
 */
uint8_t pcd8544_putch(uint8_t chr){
	scrnsz_t tabpos;
	uint8_t ret = 0;
	if(cur_x >= XCHARSZ || cur_y >= YCHARSZ) return chr;
	if(chr < 32){ // special symbols
		switch(chr){
			case '\n': // carriage return - return to beginning of current line
				++cur_y;
			// here shouldn't be a "break" because '\n' == "\r\n"
			case '\r': // newline
				cur_x = 0;
			break;
			case '\b': // return to previous position (backspace)
				if(cur_x) --cur_x;
			break;
			case '\t': // tabulation by 4 symbols
				tabpos = ((cur_x>>2)<<2) + 4;
				if(tabpos < XCHARSZ) cur_x = tabpos;
				else return chr;
			break;
		}
	}else{
		// increment x position here (there could be not writeable letters)
		pcd8544_put(chr, cur_x++, cur_y);
	}
	if(cur_x == XCHARSZ){
		cur_x = 0;
		++cur_y;
		return '\n';
	}
	return ret;
}

void pcd8544_print_big(uint8_t *koi8){
	while(*koi8){
		pcd8544_put_big(*koi8, cur_x, cur_y);
		cur_x += BIG_FONT_XSIZE;
		++koi8;
	}
}

/**
 * print zero-terminated string from current (cur_x, cur_y)
 * truncate long strings that don't fit into display
 * @return NULL if all OK or pointer to non-printed string
 */
uint8_t *pcd8544_print(uint8_t *koi8){
	while(*koi8){
		uint8_t chr = *koi8;
		if(pcd8544_putch(chr) == chr) return koi8;
		++koi8;
	}
	return NULL;
}

/**
 * roll screen by 1 line up
 */
void pcd8544_roll_screen(){
	bufsz_t idx = DISPLAYBUFSIZE-XSIZE;
	memmove(displaybuf, displaybuf + XSIZE, idx);
	memset(displaybuf+idx, 0, XSIZE);
	pcd8544_refresh();
	if(cur_y) --cur_y;
}

void set_curr_pos(uint8_t x, uint8_t y) {
	cur_x = x;
	cur_y = y;
}
