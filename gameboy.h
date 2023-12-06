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
	uint8_t interrupt_status;
} GameBoy;

//uint8_t ram[RAM_SIZE];
//uint8_t screen[SCREEN_HEIGHT][SCREEN_WIDTH]; 
//enum {HIGHER, LOWER};
enum {TRUE, FALSE};
enum {ON, OFF};
enum {ZERO_FLAG = 2, SUBTRACTION_FLAG = 4, CARRY_FLAG = 8, HALF_CARRY_FLAG = 16};

uint8_t fetch(GameBoy *gb);
void print_opcode(uint8_t opcode); 
void decode(GameBoy *gb, uint8_t opcode);
void execute(GameBoy *gb);
void handle_interrupts(GameBoy *gb);
void not_impl(GameBoy *gb);
void jump(GameBoy *gb, uint16_t address);
uint16_t join_two_bytes(uint8_t byte_A, uint8_t byte_B);// join 2 bytes in one variable of 16bit and return, example: receives 0xc3 and 0x02 returns 0xc302
void reg_to_reg_8b(uint8_t *reg_A, uint8_t *reg_B);//	register passed to reg_A receives the contents of the register passed to reg_B
void load_16b_register(uint8_t *high_reg, uint8_t *low_reg, uint16_t value);
void load_8b_register(uint8_t *reg, uint8_t value);
void set_flag(uint8_t *flag_register, uint8_t flag, uint8_t set_flag_to);
uint8_t check_upper_half_carry(uint8_t value_a, uint8_t value_b);
uint8_t check_lower_half_carry(int8_t value_a, int8_t value_b);
uint8_t check_flag(uint8_t *flag_register, uint8_t flag);

//	Instructions
void NOP(GameBoy *gb);		//0x00
void JP_a16(GameBoy *gb);	//0xc3
void LD_HC(GameBoy *gb);	//0x61
void XOR_A(GameBoy *gb);	//0xaf
void LD_HL_n16(GameBoy *gb);//0x21
void LD_C_n8(GameBoy *gb);	//0x0e
void LD_B_n8(GameBoy *gb);	//0x06
void LD_address_HLminus_A(GameBoy *gb);	//0x32
void DEC_B(GameBoy *gb);		//0x05
void JR_NZ_e8(GameBoy *gb);	//0x20						
void DEC_C(GameBoy *gb);		//0x0d
void LD_A_n8(GameBoy *gb);	//0x3e
void DI(GameBoy *gb);				//0xf3
void LDH_a8_A(GameBoy *gb);	//0xe0
void LDH_A_a8(GameBoy *gb);	//0xf0
void CP_A_n8(GameBoy *gb);	//0xfe
