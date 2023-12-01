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
