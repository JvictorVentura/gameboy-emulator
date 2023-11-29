#define SCREEN_WIDTH 160
#define SCREEN_HEIGHT 144
#define RAM_SIZE 8192
#define ADDRESS_SIZE 65535
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

	//uint8_t ram[RAM_SIZE];
	uint8_t memory_address[ADDRESS_SIZE];
	uint8_t screen[SCREEN_HEIGHT][SCREEN_WIDTH];

	uint8_t *rom;
	uint16_t rom_size;

	uint8_t opcode;
	uint8_t stop_execution;

	uint32_t frequency;
} GameBoy;

//uint8_t ram[RAM_SIZE];
//uint8_t screen[SCREEN_HEIGHT][SCREEN_WIDTH]; 
//enum {HIGHER, LOWER};
enum {TRUE, FALSE};

uint8_t fetch(GameBoy *gb);
void print_opcode(uint8_t opcode); 
void decode(GameBoy *gb, uint8_t opcode);
void execute(GameBoy *gb);
void not_impl(GameBoy *gb);
