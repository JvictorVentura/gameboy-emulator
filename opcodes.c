#include "components.c"
#include "util.h"
// RN. R = Register.  N = size in bits (16/8).
// UN. U = value (unsinged integer).  N = size in bits (16/8).

void NOP(){}

void load_R16_U16(){
	
	int16b value = (fetch() << 8) + fetch();

	int16b *register_adress[] = {
		&Cpu.BC,
		&Cpu.DE,
		&Cpu.HL,
		&Cpu.stack_pointer,
		&Cpu.AF
	};

	byte index = opcode >> 4;

	*register_adress[index] = value;
}

void STOP(){

	byte stop_loop = FALSE;

	while( stop_loop == FALSE){
		//check for any button press
	}

	fetch();	//for some reason it seams that the STOP instruction skips 1 byte
}

void jump_if_not_flag_U8(){
	byte adress = fetch();

	if(opcode == 0x20){
		
	}

}


