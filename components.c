#define WIDTH 160
#define HEIGHT 144
#define RAM_SIZE 8192
#include "util.h"


struct {
	int16b AF;
	int16b BC;
	int16b DE;
	int16b HL;

	int16b stack_pointer;
	int16b PC;

} Cpu;


byte RAM[RAM_SIZE];
byte Screen[HEIGHT][WIDTH];
enum{HIGHER, LOWER};

byte fetch(){
	return RAM[Cpu.PC++];
}


void set_flag(char flag, byte value){
	switch(flag){
		case 'Z':
			if(value == 0)
				Cpu.AF = Cpu.AF & ~(1<<8);
			else
				Cpu.AF = Cpu.AF | (1<<8);
		break;

		case 'N':
			if(value == 0)
				Cpu.AF = Cpu.AF & ~(1<<7);
			else
				Cpu.AF = Cpu.AF | (1<<7);
		break;


		case 'H':
			if(value == 0)
				Cpu.AF = Cpu.AF & ~(1<<6);
			else
				Cpu.AF = Cpu.AF | (1<<6);
		break;


		case 'C':
			if(value == 0)
				Cpu.AF = Cpu.AF & ~(1<<5);
			else
				Cpu.AF = Cpu.AF | (1<<5);
		break;
	}
}


void clean_higher_bits(int16b *Register){
	*Register = *Register & 0x00FF;
}

void clean_lower_bits(int16b *Register){
	*Register = *Register & 0xFF00;
}



byte get_higher_bits(int16b *Register){
	return *Register >> 8;
}

void set_higher_bits( byte value, int16b *Register ){
	//clean the register
	clean_higher_bits(Register);
	*Register += value << 8;
}




byte get_lower_bits(int16b *Register){
	return *Register & 0x00FF;
}

void set_lower_bits( byte value, int16b *Register ){
	//clean the register
	clean_lower_bits(Register);
	*Register += value >> 8;
}




void set_16bit_register( int16b  value, int16b *Register ){
	*Register = value ;
}



void increment_16bit_register( int16b *Register ){
	(*Register)++;
}

void increment_8bit_register( int16b *Register, char higher_or_lower){
	
	if(higher_or_lower == 'H'){
		byte temp = *Register >> 8;
		if( (temp & 0x0F) == 0x0F)
			set_flag('H', 1);
		++temp;

		if(temp == 0)
			//flag Z = 1
			set_flag('Z', 1);
		else
			//flag Z = 0
			set_flag('Z', 0);

		set_higher_bits(temp, Register);
	}

	if(higher_or_lower == 'L'){
		byte temp = *Register & 0x00FF;
		if( (temp & 0x0F) == 0x0F)
			set_flag('H', 1);
		++temp;

		if(temp == 0)
			//flag Z = 1
			set_flag('Z', 1);
		else
			//flag Z = 0
			set_flag('Z', 0);

		set_lower_bits(temp, Register);
	}
	//set flag N = 0
	set_flag('N', 0);
	
}






//-----------------------------------------------------------------------------
/*
struct {
	int16b AF;
	int16b BC;
	int16b DE;
	int16b HL;

	byte A;
	byte B;
	byte C;
	byte D;
	byte E;
	byte H;
	byte L;


	int16b stack_pointer;
	int16b PC;
	byte Flags;

} Cpu;

byte RAM[RAM_SIZE];

byte Screen[HEIGHT][WIDTH];

enum{HIGHER, LOWER};

void set_higher_bits(int16b *Register, byte value){
	int16b temporary;
	temporary = *Register &  0x00FF;		//clean higher bits
	temporary = temporary | (value << 8);	//add value to the higher bits

	*Register = temporary;
}

void set_lower_bits(int16b *Register, byte value){
	int16b temporary;
	temporary = *Register &  0xFF00;		//clean lower bits
	temporary = temporary | value;			//add value to the lower bits

	*Register = temporary;
}

void set8b(byte *Register, byte value, byte higher_or_lower, int16b *Register_16b){
	*Register = value;
	//*Register_16b = higher_or_lower == HIGHER ? *Register_16b & (0x00FF | (value << 8)) : *Register_16b & (0xFF00 | value);
	if(higher_or_lower == HIGHER ){
		//*Register_16b = *Register_16b & (0x00FF | (value << 8));
		set_higher_bits(Register)
	}else{
		*Register_16b = *Register_16b & (0xFF00 | value);
	}
}

void set16b(byte value, int16b *Register, byte *H_bits, byte *L_bits){
	*Register = value;
	*H_bits = value & 0xFF00;
	*L_bits = value & 0x00FF;
}

int16b get16b(int16b *Register){
	return *Register;
}

void increment_XX_register(byte opcode){

	switch(opcode){
		case 0x03:	//BC
			set16b(Cpu.BC + 1, &Cpu.BC, &Cpu.B, &Cpu.C);
		break;

		case 0x13:	//DE
			set16b(Cpu.DE + 1, &Cpu.DE, &Cpu.D, &Cpu.E);
		break;

		case 0x23:	//HL
			set16b(Cpu.HL + 1, &Cpu.HL, &Cpu.H, &Cpu.L);
		break;

		case 0x33:	//SP
			Cpu.stack_pointer += 1;
		break;
	}
}




*/