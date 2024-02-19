#include "gameboy.h"

uint8_t fetch(GameBoy *gb){
	return gb->memory_address[gb->PC++];
}

void jump(GameBoy *gb, const uint16_t address){
	gb->PC = address;
}

void load_16b_register(uint8_t *high_reg, uint8_t *low_reg, uint16_t value){
	*high_reg = (value >> 8);
	*low_reg = value & 0x00FF;
}

void load_8b_register(uint8_t *reg, uint8_t value){
	*reg = value;
}

void stack_push_n16(GameBoy *gb, const uint16_t value){

	gb->stack_pointer--;
	gb->memory_address[gb->stack_pointer] = value >> 8;
		
	gb->stack_pointer--;
	gb->memory_address[gb->stack_pointer] = value & 0x00FF;
}


uint16_t stack_pop_n16(GameBoy *gb){
	
	uint8_t lower_byte = gb->memory_address[gb->stack_pointer];
	gb->stack_pointer++;

	uint8_t upper_byte = gb->memory_address[gb->stack_pointer];
	gb->stack_pointer++;

	return join_two_bytes(upper_byte, lower_byte);

}

uint16_t get_next_two_bytes(GameBoy *gb){
	uint8_t byte_low = fetch(gb);
	uint8_t byte_high = fetch(gb);
	return join_two_bytes(byte_high, byte_low);
}


