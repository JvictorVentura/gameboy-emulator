#define LINE_MAX_SPRITES 10
#define OAM_MAX_SPRITES 40
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
