#include "components.c"

void LD_0x01( int16b value){
	//Cpu.BC = value;	
	set_16bit_register( value, &Cpu.BC );
}

void LD_0x02(){
	RAM[Cpu.BC] = get_higher_bits(&Cpu.AF);	
}

void INC_0x03(){
	//++BC;
	increment_16bit_register(&Cpu.BC);
}

void INC_0x04(){
	increment_8bit_register(&Cpu.BC, 'H');
}