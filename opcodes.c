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

void INC_B(){//0x04
	increment_8bit_register(&Cpu.BC, 'H');
}

void INC_D(){//0x14
	increment_8bit_register(&Cpu.DE, 'H');
}

void INC_H(){//0x24
	increment_8bit_register(&Cpu.HL, 'H');
}

void INC_C(){//0x0C
	increment_8bit_register(&Cpu.BC, 'L');
}

void INC_E(){//0x1C
	increment_8bit_register(&Cpu.DE, 'L');
}

void INC_L(){//0x2C
	increment_8bit_register(&Cpu.HL, 'L');
}

void INC_A(){//0x3C
	increment_8bit_register(&Cpu.AF, 'H');
}