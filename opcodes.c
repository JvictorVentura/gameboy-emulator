#include "components.c"

void LD_0x01( int16b value){
	//Cpu.BC = value;	
	set_16bit_register( value, &Cpu.BC );
}

void LD_0x02(){
	RAM[Cpu.BC] = get_higher_bits(&Cpu.AF);	
}

void increment_XX_register(char *register_name){
	switch(register_name){
		case "BC":
			increment_16bit_register(&Cpu.BC);
		break;

		case "DE":
			increment_16bit_register(&Cpu.DE);
		break;

		case "HL":
			increment_16bit_register(&Cpu.HL);
		break;

		case "SP":
			increment_16bit_register(&Cpu.stack_pointer);
		break;
	}
}

void increment_X_register(char *register_name){
	switch(register_name){
		case 'B':
			increment_8bit_register(&Cpu.BC, 'H');
		break;

		case 'C':
			increment_8bit_register(&Cpu.BC, 'L');
		break;

		case 'D':
			increment_8bit_register(&Cpu.DE, 'H');
		break;

		case 'E':
			increment_8bit_register(&Cpu.DE, 'L');
		break;

		case 'H':
			increment_8bit_register(&Cpu.HL, 'H');
		break;

		case 'L':
			increment_8bit_register(&Cpu.HL, 'L');
		break;

		case 'A':
			increment_8bit_register(&Cpu.AF, 'H');
		break;
	}
}

/*
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
*/




/*void INC_BC(){//0x03
	increment_16bit_register(&Cpu.BC);
}

void INC_DE(){//0x13
	increment_16bit_register(&Cpu.DE);
}

void INC_HL(){//0x23
	increment_16bit_register(&Cpu.HL);
}

void INC_SP(){//0x33
	increment_16bit_register(&Cpu.stack_pointer);
}*/
