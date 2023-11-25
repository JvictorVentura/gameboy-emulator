#define SCREEN_WIDTH 160
#define SCREEN_HEIGHT 144
#define RAM_SIZE 8192
#include <stdint.h>

typedef struct{
	uint8_t A;
	uint8_t F;
	uint8_t B;
	uint8_t C;
	uint8_t D;
	uint8_t E;
	uint8_t H;
	uint8_t L;

	uint16_t stack_pointer;
	uint16_t PC;

	uint8_t ram[RAM_SIZE];
	uint8_t screen[SCREEN_HEIGHT][SCREEN_WIDTH];
} GameBoy;

//uint8_t ram[RAM_SIZE];
//uint8_t screen[SCREEN_HEIGHT][SCREEN_WIDTH]; 
//enum {HIGHER, LOWER};
enum {TRUE, FALSE};

uint8_t fetch(GameBoy *gb);
