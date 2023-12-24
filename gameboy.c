#include <stdint.h>
#include "gameboy.h"
#include <stdio.h>
#include "lookup_table.h"

uint8_t fetch(GameBoy *gb){
	return gb->memory_address[gb->PC++];
}

void not_impl(GameBoy *gb){
	//printf("Instruction not implemented\n");
	print_opcode(gb->opcode);
	gb->stop_execution = TRUE;
}

void prefix_not_impl(GameBoy *gb){
	//printf("Instruction not implemented\n");
	prefix_print_opcode(gb->opcode);
	gb->stop_execution = TRUE;
}

void jump(GameBoy *gb, uint16_t address){
	gb->PC = address;
}

uint16_t join_two_bytes(uint8_t byte_A, uint8_t byte_B){
	return (byte_A << 8) + byte_B;
}

void reg_to_reg_8b(uint8_t *reg_A, uint8_t *reg_B){
	*reg_A = *reg_B;
}

void load_16b_register(uint8_t *high_reg, uint8_t *low_reg, uint16_t value){
	*high_reg = (value >> 8);
	*low_reg = value & 0x00FF;
}

void load_8b_register(uint8_t *reg, uint8_t value){
	*reg = value;
}

void set_flag(uint8_t *flag_register, uint8_t flag, uint8_t set_flag_to){
	if (set_flag_to == ON){
		*flag_register = *flag_register | flag;
	}else{
		if( (*flag_register & flag) == flag){		//if the bit is 1, flip, if its not, do nothing
			*flag_register = *flag_register ^ flag;
		}
	}

}



uint8_t check_upper_half_carry(uint8_t value_a, uint8_t value_b){
	value_a = value_a & 0xF;	//  get 4 lower bits
	value_b = value_b & 0xF;	//  get 4 lower bits
	uint8_t result = value_a + value_b;
	if (result >= 0x10){
		return TRUE;
	}else{
		return FALSE;
	}
}

uint8_t check_lower_half_carry(int8_t value_a, int8_t value_b){		// WRONG FIX LATER
	value_a = value_a & 0xF;	//  get 4 lower bits
	value_b = value_b & 0xF;	//  get 4 lower bits
	int8_t result = value_a - value_b;
	if (result < 0){		//	borrow
		return TRUE;
	}else{
		return FALSE;
	}

}

uint8_t check_flag(uint8_t *flag_register, uint8_t flag){
	if ( (*flag_register & flag) == 0x0)
		return OFF;
	else
		return ON;
}

void stack_push_n16(GameBoy *gb, uint16_t value){

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

void print_opcode(uint8_t opcode){
	//	for debug purposes
		printf("Instruction to implement: %s opcode: 0x%.2x \n", instruction_name[opcode], opcode);

}

void prefix_print_opcode(uint8_t opcode){
	//	for debug purposes
		printf("Instruction to implement: %s opcode: 0xcb%.2x \n", prefixed_instruction_name[opcode], opcode);

}
void prefixed_instruction(GameBoy *gb){
	gb->opcode = fetch(gb);
	printf("Instruction : %s\nHex: 0xcb%.2x\n\n", prefixed_instruction_name[gb->opcode], gb->opcode);
	instruction_prefix[gb->opcode](gb);

}

void execute(GameBoy *gb){

	printf("Instruction : %s\nHex: 0x%.2x\n\n", instruction_name[gb->opcode], gb->opcode);
	instruction[gb->opcode](gb);

}

void handle_interrupts(GameBoy *gb){
	// TO DO
}

/*void decode(GameBoy *gb){
	
}*/
