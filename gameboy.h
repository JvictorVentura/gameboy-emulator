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
void jump(GameBoy *gb, uint16_t address);
uint16_t join_two_bytes(uint8_t byte_A, uint8_t byte_B);// join 2 bytes in one variable of 16bit and return, example: receives 0xc3 and 0x02 returns 0xc302
void reg_to_reg_8b(uint8_t *reg_A, uint8_t *reg_B);//	register passed to reg_A receives the contents of the register passed to reg_B

//	Instructions
void NOP(GameBoy *gb);		//0x00
void JP_a16(GameBoy *gb);	//0xc3
void LD_HC(GameBoy *gb);	//0x61
void XOR_A(GameBoy *gb);	//0xAF
