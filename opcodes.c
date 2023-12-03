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
	uint8_t byte_A = fetch(gb);
	uint8_t byte_B = fetch(gb);
	
	uint16_t address = join_two_bytes(byte_B, byte_A);//	endianness?

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

/*	//get the address
	uint16_t address;
	address = fetch(gb);
	address += (fetch(gb) << 8);

	//get the value
	uint16_t value;
	value = gb->memory_address[address];	
	value += (gb->memory_address[address + 1] << 8);	

*/
