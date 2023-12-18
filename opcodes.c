#include <stdint.h>
#include "gameboy.h"
// RN. R = Register.  N = size in bits (16/8).
// UN. U = value (unsinged integer).  N = size in bits (16/8).


void STOP(GameBoy *gb){

	uint8_t stop_loop = FALSE;

	while( stop_loop == FALSE){
		//check for any button press
	}

	fetch(gb);	//for some reason it seams that the STOP instruction skips 1 byte 
}

void NOP(GameBoy *gb){
}

void JP_a16(GameBoy *gb){
	uint8_t lower_byte = fetch(gb);
	uint8_t upper_byte = fetch(gb);
	
	uint16_t address = join_two_bytes(upper_byte, lower_byte);//	endianness?

	jump(gb, address);
}


void LD_HC(GameBoy *gb){
	reg_to_reg_8b(&gb->H, &gb->C);
}

void XOR_A(GameBoy *gb){	
	gb->A = gb->A ^ gb->A;

}

void LD_HL_n16(GameBoy *gb){	
	//get the value
	uint8_t byte_low = fetch(gb);
	uint8_t byte_high = fetch(gb);
	uint16_t value = join_two_bytes(byte_high, byte_low);

	//assign value H and L
	
	load_16b_register( &(gb->H), &(gb->L), value);
}

void LD_C_n8(GameBoy *gb){
	uint8_t value = fetch(gb);
	load_8b_register( &(gb->C), value);
}

void LD_B_n8(GameBoy *gb){
	uint8_t value = fetch(gb);
	load_8b_register( &(gb->B), value);
}


void LD_address_HLminus_A(GameBoy *gb){	
	uint16_t address = join_two_bytes(gb->H, gb->L);
	gb->memory_address[address] = gb->A;
	address--;
	load_16b_register( &(gb->H), &(gb->L), address);
}

void DEC_B(GameBoy *gb){	
	uint8_t before_decrement = gb->B;
	gb->B--;
	if(gb->B == 0){
		set_flag(&(gb->F), ZERO_FLAG, ON);
	}else{
		set_flag(&(gb->F), ZERO_FLAG, OFF);
	}

	set_flag(&(gb->F), SUBTRACTION_FLAG, ON);

	if (check_lower_half_carry(before_decrement, 1) == TRUE){		//	borrow
		set_flag(&(gb->F), HALF_CARRY_FLAG, ON);
	}else{
		set_flag(&(gb->F), HALF_CARRY_FLAG, OFF);		// no borrow
	}


}

void JR_NZ_e8(GameBoy *gb){
	int8_t jump_value = fetch(gb);

	if (check_flag( &(gb->F), ZERO_FLAG) == OFF){
		gb->PC += jump_value;
	}

}

void DEC_C(GameBoy *gb){	
	uint8_t before_decrement = gb->C;
	gb->C--;
	if(gb->C == 0){
		set_flag(&(gb->F), ZERO_FLAG, ON);
	}else{
		set_flag(&(gb->F), ZERO_FLAG, OFF);
	}

	set_flag(&(gb->F), SUBTRACTION_FLAG, ON);

	if (check_lower_half_carry(before_decrement, 1) == TRUE){		//	borrow
		set_flag(&(gb->F), HALF_CARRY_FLAG, ON);
	}else{
		set_flag(&(gb->F), HALF_CARRY_FLAG, OFF);		// no borrow
	}

//	if (gb->C < 1){
//		set_flag(&(gb->F), CARRY_FLAG, ON);		
//	}else{
//		set_flag(&(gb->F), CARRY_FLAG, OFF);
//	}

}

void LD_A_n8(GameBoy *gb){
	uint8_t value = fetch(gb);
	load_8b_register( &(gb->A), value);
}

void DI(GameBoy *gb){
	gb->interrupt_status = OFF;
}


void LDH_a8_A(GameBoy *gb){
	uint8_t offset = fetch(gb);
	gb->memory_address[0xFF00 + offset] = gb->A;
}

void LDH_A_a8(GameBoy *gb){
	uint8_t offset = fetch(gb);
	 gb->A = gb->memory_address[0xFF00 + offset];
}

void CP_A_n8(GameBoy *gb){	
	uint8_t value = fetch(gb);
	uint8_t before_subtraction= gb->A;
	uint8_t after_subtraction= gb->A - value;

	if(after_subtraction == 0){
		set_flag(&(gb->F), ZERO_FLAG, ON);
	}else{
		set_flag(&(gb->F), ZERO_FLAG, OFF);
	}

	set_flag(&(gb->F), SUBTRACTION_FLAG, ON);

	if (check_lower_half_carry(before_subtraction, value) == TRUE){		
		set_flag(&(gb->F), HALF_CARRY_FLAG, ON);
	}else{
		set_flag(&(gb->F), HALF_CARRY_FLAG, OFF);		
	}

	if (gb->A < value){
		set_flag(&(gb->F), CARRY_FLAG, ON);		
	}else{
		set_flag(&(gb->F), CARRY_FLAG, OFF);
	}



}

void LD_SP_n16(GameBoy *gb){
	uint8_t lower_byte = fetch(gb);	
	uint8_t higher_byte = fetch(gb);	
	uint16_t address = join_two_bytes(higher_byte, lower_byte);
	gb->stack_pointer = address;
}

void BIT_7_H(GameBoy *gb){
	if( (gb->H & 0x80) == 0x80){	// 7th bit
		set_flag(&(gb->F), ZERO_FLAG, OFF);
	}else{
		set_flag(&(gb->F), ZERO_FLAG, ON);
	}
	set_flag(&(gb->F), SUBTRACTION_FLAG, OFF);
	set_flag(&(gb->F), HALF_CARRY_FLAG, ON);

}

void LD_C_plus_offset_A(GameBoy *gb){
	gb->memory_address[0xFF00 + gb->C] = gb->A;
}

void INC_C(GameBoy *gb){
	uint8_t before_increment = gb->C;
	gb->C++;
	if(gb->C == 0){
		set_flag(&(gb->F), ZERO_FLAG, ON);
	}else{
		set_flag(&(gb->F), ZERO_FLAG, OFF);
	}

	set_flag(&(gb->F), SUBTRACTION_FLAG, OFF);

	if (check_upper_half_carry(before_increment, 1) == TRUE){		//	borrow
		set_flag(&(gb->F), HALF_CARRY_FLAG, ON);
	}else{
		set_flag(&(gb->F), HALF_CARRY_FLAG, OFF);		// no borrow
	}

}

void LD_address_HL_A(GameBoy *gb){
	uint16_t address = join_two_bytes(gb->H, gb->L);
	gb->memory_address[address] = gb->A;
}

void LD_DE_n16(GameBoy *gb){
	uint8_t lower_byte = fetch(gb);
	uint8_t upper_byte = fetch(gb);

	uint16_t value = join_two_bytes(upper_byte, lower_byte);

	load_16b_register( &(gb->D), &(gb->E), value);

}

void LD_A_address_DE(GameBoy *gb){
	uint16_t address = join_two_bytes(gb->D, gb->E);
	gb->A = gb->memory_address[address];
}

void CALL_a16(GameBoy *gb){	
	uint8_t lower_byte = fetch(gb);
	uint8_t upper_byte = fetch(gb);

	uint16_t address = join_two_bytes(upper_byte, lower_byte);

	stack_push_n16(gb, gb->PC);

	gb->PC = address;

}

void LD_C_A(GameBoy *gb){

	gb->C = gb->A;

}
/*	//get the address
	uint16_t address;
	address = fetch(gb);
	address += (fetch(gb) << 8);

	//get the value
	uint16_t value;
	value = gb->memory_address[address];	
	value += (gb->memory_address[address + 1] << 8);	

*/
