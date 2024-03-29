#include <stdint.h>
#include "gameboy.h"
#include "mmu.h"


void STOP(GameBoy *gb){

	uint8_t stop_loop = false;

	while( stop_loop == false){
		//check for any button press
	}

	fetch(gb);	//for some reason it seams that the STOP instruction skips 1 byte 
}

void NOP(GameBoy *gb){
}

void JP_a16(GameBoy *gb){
	//uint8_t lower_byte = fetch(gb);
	//uint8_t upper_byte = fetch(gb);
	//uint16_t address = join_two_bytes(upper_byte, lower_byte);//	endianness?
	uint16_t address = get_next_two_bytes(gb);
	jump(gb, address);
}


void LD_H_C(GameBoy *gb){
	gb->H = gb->C;

}

void XOR_A_A(GameBoy *gb){	
	gb->A = gb->A ^ gb->A;

}

void LD_HL_n16(GameBoy *gb){	
	//uint8_t byte_low = fetch(gb);
	//uint8_t byte_high = fetch(gb);
	//uint16_t value = join_two_bytes(byte_high, byte_low);
		
	uint16_t value = get_next_two_bytes(gb);
	load_16b_register( &(gb->H), &(gb->L), value);
}

void LD_C_n8(GameBoy *gb){
	uint8_t value = fetch(gb);
	gb->C = value;
}

void LD_B_n8(GameBoy *gb){
	uint8_t value = fetch(gb);
	gb->B = value;
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

	if (check_lower_half_carry(before_decrement, 1) == true){		//	borrow
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

	if (check_lower_half_carry(before_decrement, 1) == true){		//	borrow
		set_flag(&(gb->F), HALF_CARRY_FLAG, ON);
	}else{
		set_flag(&(gb->F), HALF_CARRY_FLAG, OFF);		// no borrow
	}

}

void LD_A_n8(GameBoy *gb){
	uint8_t value = fetch(gb);
	gb->A = value;
}

void DI(GameBoy *gb){
	gb->interrupt_master_enable = OFF;
}

void EI(GameBoy *gb){
	gb->interrupt_master_enable = ON;
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

	if (check_lower_half_carry(before_subtraction, value) == true){		
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
	//uint8_t lower_byte = fetch(gb);	
	//uint8_t higher_byte = fetch(gb);	
	//uint16_t address = join_two_bytes(higher_byte, lower_byte);
	uint16_t address = get_next_two_bytes(gb);
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

	if (check_upper_half_carry(before_increment, 1) == true){		//	borrow
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

	uint16_t value = get_next_two_bytes(gb);
	load_16b_register( &(gb->D), &(gb->E), value);

}

void LD_A_address_DE(GameBoy *gb){

	uint16_t address = join_two_bytes(gb->D, gb->E);
	gb->A = gb->memory_address[address];

}

void CALL_a16(GameBoy *gb){	

	uint16_t address = get_next_two_bytes(gb);
	stack_push_n16(gb, gb->PC);

	gb->PC = address;

}

void LD_C_A(GameBoy *gb){
	gb->C = gb->A;
}

void PUSH_BC(GameBoy *gb){
	uint16_t BC = join_two_bytes(gb->B, gb->C);
	stack_push_n16(gb, BC);

}

void RL_C(GameBoy *gb){
	const uint8_t mask = 0b10000000;
	uint8_t old_carry_flag = check_flag(&(gb->F), CARRY_FLAG);
	//uint8_t new_carry_flag;
	if( (gb->C & mask) == mask ){
		set_flag(&(gb->F), CARRY_FLAG, ON);
	}else{
		set_flag(&(gb->F), CARRY_FLAG, OFF);
	}

	gb->C <<= 1;

	if(old_carry_flag == ON){
		gb->C |= 0b00000001;
	}/*else{
		gb->C |= 0xfe;
	}*/

}

void RL_A(GameBoy *gb){
	const uint8_t mask = 0b10000000;
	uint8_t old_carry_flag = check_flag(&(gb->F), CARRY_FLAG);

	if( (gb->A & mask) == mask ){
		set_flag(&(gb->F), CARRY_FLAG, ON);
	}else{
		set_flag(&(gb->F), CARRY_FLAG, OFF);
	}

	gb->A <<= 1;

	if(old_carry_flag == ON){
		gb->A |= 0b00000001;
	}/*else{
		gb->C |= 0xfe;
	}*/

}

void POP_BC(GameBoy *gb){
	uint16_t BC_buffer = stack_pop_n16(gb);
	load_16b_register( &(gb->B) , &(gb->C), BC_buffer);
}

void LD_address_HLplus_A(GameBoy *gb){	
	uint16_t address = join_two_bytes(gb->H, gb->L);
	gb->memory_address[address] = gb->A;
	address++;
	load_16b_register( &(gb->H), &(gb->L), address);
}


void INC_HL(GameBoy *gb){
	uint16_t value = join_two_bytes(gb->H, gb->L);
	value++;
	load_16b_register( &(gb->H), &(gb->L), value);
}

void RET_a16(GameBoy *gb){	
	uint16_t address = stack_pop_n16(gb);
	gb->PC = address;

}

void INC_DE(GameBoy *gb){
	uint16_t value = join_two_bytes(gb->D, gb->E);
	value++;
	load_16b_register( &(gb->D), &(gb->E), value);
}

void LD_A_E(GameBoy *gb){
	gb->A = gb->E;
}


void LD_a16_A(GameBoy *gb){
	
	uint16_t address = get_next_two_bytes(gb);
	gb->memory_address[address] = gb->A;

}

void DEC_A(GameBoy *gb){	
	uint8_t before_decrement = gb->A;
	gb->A--;
	if(gb->A == 0){
		set_flag(&(gb->F), ZERO_FLAG, ON);
	}else{
		set_flag(&(gb->F), ZERO_FLAG, OFF);
	}

	set_flag(&(gb->F), SUBTRACTION_FLAG, ON);

	if (check_lower_half_carry(before_decrement, 1) == true){		//	borrow
		set_flag(&(gb->F), HALF_CARRY_FLAG, ON);
	}else{
		set_flag(&(gb->F), HALF_CARRY_FLAG, OFF);		// no borrow
	}


}


void JR_Z_e8(GameBoy *gb){
	int8_t address_offset = fetch(gb);

	if( check_flag( &(gb->F), ZERO_FLAG) == ON ){
		gb->PC += address_offset;
	}
}

void LD_L_n8(GameBoy *gb){
	uint8_t value = fetch(gb);
	gb->L = value;
}

void JR_e8(GameBoy *gb){
	int8_t address_offset = fetch(gb);
	gb->PC += address_offset;
}

void LD_H_A(GameBoy *gb){
	gb->H = gb->A;
}

void LD_D_A(GameBoy *gb){
	gb->D = gb->A;
}

void INC_B(GameBoy *gb){
	uint8_t before_increment = gb->B;
	gb->B++;
	if(gb->B == 0){
		set_flag(&(gb->F), ZERO_FLAG, ON);
	}else{
		set_flag(&(gb->F), ZERO_FLAG, OFF);
	}

	set_flag(&(gb->F), SUBTRACTION_FLAG, OFF);

	if (check_upper_half_carry(before_increment, 1) == true){		//	borrow
		set_flag(&(gb->F), HALF_CARRY_FLAG, ON);
	}else{
		set_flag(&(gb->F), HALF_CARRY_FLAG, OFF);		// no borrow
	}

}

void LD_E_n8(GameBoy *gb){
	uint8_t value = fetch(gb);
	gb->E = value;
}

void DEC_D(GameBoy *gb){	
	uint8_t before_decrement = gb->D;
	gb->D--;
	if(gb->D == 0){
		set_flag(&(gb->F), ZERO_FLAG, ON);
	}else{
		set_flag(&(gb->F), ZERO_FLAG, OFF);
	}

	set_flag(&(gb->F), SUBTRACTION_FLAG, ON);

	if (check_lower_half_carry(before_decrement, 1) == true){		//	borrow
		set_flag(&(gb->F), HALF_CARRY_FLAG, ON);
	}else{
		set_flag(&(gb->F), HALF_CARRY_FLAG, OFF);		// no borrow
	}

}

void LD_D_n8(GameBoy *gb){
	uint8_t value = fetch(gb);
	gb->D = value;
}

