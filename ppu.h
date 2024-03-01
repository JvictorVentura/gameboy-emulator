#include "gameboy.h"
#include <stdlib.h>

#define LINE_MAX_SPRITES 10
#define OAM_MAX_SPRITES 40

#define	LCD_CONTROL					0xFF40
#define	LCDC_STATUS					0xFF41
#define	SCROLL_Y						0xFF42
#define	SCROLL_X						0xFF43
#define	LCDC_Y_COORDINATE		0xFF44
#define	LY_COMPARE					0xFF45
#define	DMA									0xFF46
#define	BG_PALETTE_DATA			0xFF47
#define	OBJECT_PALETTE_0		0xFF48
#define	OBJECT_PALETTE_1		0xFF49
#define	WINDOW_Y_POSITION		0xFF4A
#define	WINDOW_X_POSITION		0xFF4B



enum {NORMAL_SPRITE= 8, LARGE_SPRITE= 16};

typedef struct{
	uint8_t y_pos;
	uint8_t x_pos;
	uint8_t tile_index;
	uint8_t attributes;

}sprite;

void ppu_execute(GameBoy *gb);
void search_OAM(uint8_t screen_Y, sprite (*current_line_sprites)[10], GameBoy *gb);
void vertical_flip_sprite(uint8_t (*sprite)[8][8]);
void horizontal_flip_sprite(uint8_t (*sprite)[8][8]);
