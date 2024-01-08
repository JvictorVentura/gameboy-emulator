#define LINE_MAX_SPRITES 10
#define OAM_MAX_SPRITES 40

typedef struct{
	uint8_t y_pos;
	uint8_t x_pos;
	uint8_t sprite_location;
	uint8_t attributes;

}sprite;
void ppu_execute();
