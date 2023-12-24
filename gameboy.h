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

	uint8_t memory_address[ADDRESS_SIZE]; 
	uint8_t screen[SCREEN_HEIGHT][SCREEN_WIDTH];

	uint8_t *boot_rom;
	uint16_t boot_rom_size;
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
enum {ZERO_FLAG = 0x80, SUBTRACTION_FLAG = 0x40, HALF_CARRY_FLAG = 0x20, CARRY_FLAG = 0x10 };

uint8_t fetch(GameBoy *gb);
void print_opcode(uint8_t opcode); 
void prefix_print_opcode(uint8_t opcode);
void decode(GameBoy *gb, uint8_t opcode);
void execute(GameBoy *gb);
void prefixed_instruction(GameBoy *gb);
void handle_interrupts(GameBoy *gb);
void not_impl(GameBoy *gb);
void prefix_not_impl(GameBoy *gb);
void jump(GameBoy *gb, uint16_t address);
uint16_t join_two_bytes(uint8_t byte_A, uint8_t byte_B);// join 2 bytes in one variable of 16bit and return, example: receives 0xc3 and 0x02 returns 0xc302
//void reg_to_reg_8b(uint8_t *reg_A, uint8_t *reg_B);//	register passed to reg_A receives the contents of the register passed to reg_B
void load_16b_register(uint8_t *high_reg, uint8_t *low_reg, uint16_t value);
//void load_8b_register(uint8_t *reg, uint8_t value);
void set_flag(uint8_t *flag_register, uint8_t flag, uint8_t set_flag_to);
uint8_t check_upper_half_carry(uint8_t value_a, uint8_t value_b);
uint8_t check_lower_half_carry(int8_t value_a, int8_t value_b);
uint8_t check_flag(uint8_t *flag_register, uint8_t flag);
void stack_push_n16(GameBoy *gb, uint16_t value);
uint16_t stack_pop_n16(GameBoy *gb);
uint16_t get_next_two_bytes(GameBoy *gb);

//	Instructions
void NOP(GameBoy *gb);			//0x00
void JP_a16(GameBoy *gb);		//0xc3
void LD_H_C(GameBoy *gb);		//0x61
void XOR_A_A(GameBoy *gb);	//0xaf
void LD_HL_n16(GameBoy *gb);//0x21
void LD_C_n8(GameBoy *gb);	//0x0e
void LD_B_n8(GameBoy *gb);	//0x06
void LD_address_HLminus_A(GameBoy *gb);//0x32
void DEC_B(GameBoy *gb);		//0x05
void JR_NZ_e8(GameBoy *gb);	//0x20						
void DEC_C(GameBoy *gb);		//0x0d
void LD_A_n8(GameBoy *gb);	//0x3e
void DI(GameBoy *gb);				//0xf3
void LDH_a8_A(GameBoy *gb);	//0xe0
void LDH_A_a8(GameBoy *gb);	//0xf0
void CP_A_n8(GameBoy *gb);	//0xfe
void LD_SP_n16(GameBoy *gb);//0x31
void BIT_7_H(GameBoy *gb);	//0xcb7c
void LD_C_plus_offset_A(GameBoy *gb);//0xe2
void INC_C(GameBoy *gb);		//0x0c
void LD_address_HL_A(GameBoy *gb);//0x77
void LD_DE_n16(GameBoy *gb);//0x11
void LD_A_address_DE(GameBoy *gb);//0x1a
void CALL_a16(GameBoy *gb);	//0xcd
void LD_C_A(GameBoy *gb);		//0x4f
void PUSH_BC(GameBoy *gb);	//0xc5
void RL_C(GameBoy *gb);			//0xcb11
void RL_A(GameBoy *gb);			//0x17
void POP_BC(GameBoy *gb);		//0xc1
void LD_address_HLplus_A(GameBoy *gb);//0x22
void INC_HL(GameBoy *gb);		//0x23
void RET_a16(GameBoy *gb);	//0xc9
void INC_DE(GameBoy *gb);		//0x13
void LD_A_E(GameBoy *gb);		//0x7b
void LD_a16_A(GameBoy *gb);	//0xea
void DEC_A(GameBoy *gb);		//0x3d
void JR_Z_e8(GameBoy *gb);	//0x28
void LD_L_n8(GameBoy *gb);	//0x2e
void JR_e8(GameBoy *gb);		//0x18
void LD_H_A(GameBoy *gb);		//0x67
void LD_D_A(GameBoy *gb);		//0x57
void INC_B(GameBoy *gb);		//0x04
void LD_E_n8(GameBoy *gb);	//0x1e
