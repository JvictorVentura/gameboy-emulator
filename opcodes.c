#include "components.c"

void LD_0x01( int16b value){
	Cpu.BC = value;	
}

void LD_0x02(){
	RAM[Cpu.BC] = get_A();	
}
