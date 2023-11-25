#include <stdint.h>
#include "gameboy.h"
// RN. R = Register.  N = size in bits (16/8).
// UN. U = value (unsinged integer).  N = size in bits (16/8).

void NOP(){}

void STOP(GameBoy *gb){

	uint8_t stop_loop = FALSE;

	while( stop_loop == FALSE){
		//check for any button press
	}

	fetch(gb);	//for some reason it seams that the STOP instruction skips 1 byte 
}

