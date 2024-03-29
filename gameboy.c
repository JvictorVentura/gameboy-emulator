#include <stdint.h>
#include <stdio.h>
#include "mmu.h"
#include "lookup_table.h"

void not_impl(GameBoy *gb){
	//printf("Instruction not implemented\n");
	print_opcode(gb->opcode);
	gb->stop_execution = true;
}

void prefix_not_impl(GameBoy *gb){
	//printf("Instruction not implemented\n");
	prefix_print_opcode(gb->opcode);
	gb->stop_execution = true;
}

uint16_t join_two_bytes(const uint8_t byte_A, const uint8_t byte_B){
	return (byte_A << 8) + byte_B;
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
		return true;
	}else{
		return false;
	}
}

uint8_t check_lower_half_carry(int8_t value_a, int8_t value_b){		// WRONG FIX LATER
	value_a = value_a & 0xF;	//  get 4 lower bits
	value_b = value_b & 0xF;	//  get 4 lower bits
	int8_t result = value_a - value_b;
	if (result < 0){		//	borrow
		return true;
	}else{
		return false;
	}

}

uint8_t check_flag(uint8_t *flag_register, const uint8_t flag){
	if ( (*flag_register & flag) == 0x0)
		return OFF;
	else
		return ON;
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

void execute_cpu(GameBoy *gb){

	printf("Instruction : %s\nHex: 0x%.2x\n\n", instruction_name[gb->opcode], gb->opcode);
	instruction[gb->opcode](gb);

}

void execute_ppu(){
  
}

/*void decode(GameBoy *gb){
	
}*/
