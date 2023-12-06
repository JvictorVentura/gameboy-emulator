#include <stdint.h>
#include "gameboy.h"
#include <stdio.h>

uint8_t fetch(GameBoy *gb){
	return gb->memory_address[gb->PC++];
}

void not_impl(GameBoy *gb){
	//printf("Instruction not implemented\n");
	print_opcode(gb->opcode);
	gb->stop_execution = TRUE;
}

void jump(GameBoy *gb, uint16_t address){
	gb->PC = address;
}

uint16_t join_two_bytes(uint8_t byte_A, uint8_t byte_B){
	return (byte_A << 8) + byte_B;
}

void reg_to_reg_8b(uint8_t *reg_A, uint8_t *reg_B){
	*reg_A = *reg_B;
}

void load_16b_register(uint8_t *high_reg, uint8_t *low_reg, uint16_t value){
	*high_reg = (value >> 8);
	*low_reg = value & 0x00FF;
}

void load_8b_register(uint8_t *reg, uint8_t value){
	*reg = value;
}

void set_flag(uint8_t *flag_register, uint8_t flag, uint8_t set_flag_to){
	if (set_flag_to == ON){
		*flag_register = *flag_register | flag;
	}else{
		*flag_register = *flag_register & (~flag);
	}

}

uint8_t check_upper_half_carry(uint8_t value_a, uint8_t value_b){
	value_a = value_a & 0xF;	//  get 4 lower bits
	value_b = value_b & 0xF;	//  get 4 lower bits
	uint8_t result = value_a + value_b;
	if (result >= 0x10){
		return TRUE;
	}else{
		return FALSE;
	}
}

uint8_t check_lower_half_carry(int8_t value_a, int8_t value_b){		// WRONG FIX LATER
	value_a = value_a & 0xF;	//  get 4 lower bits
	value_b = value_b & 0xF;	//  get 4 lower bits
	int8_t result = value_a - value_b;
	if (result < 0){		//	borrow
		return TRUE;
	}else{
		return FALSE;
	}

}

uint8_t check_flag(uint8_t *flag_register, uint8_t flag){
	if ( (*flag_register & flag) == 0x0)
		return OFF;
	else
		return ON;
}





void print_opcode(uint8_t opcode){
	//	for debug purposes
	char *instruction_name[] = {"NOP", "LD BC,n16", "LD BC,A", "INC BC", "INC B", "DEC B", "LD B,n8", "RLCA", "LD a16,SP", "ADD HL,BC", "LD A,BC", "DEC BC", "INC C", "DEC C", "LD C,n8", "RRCA", 
											 "STOP n8", "LD DE,n16", "LD DE,A", "INC DE", "INC D", "DEC D", "LD D,n8", "RLA", "JR e8", "ADD HL,DE", "LD A,DE", "DEC DE", "INC E", "DEC E", "LD E,n8", "RRA", 
											 "JR NZ,e8", "LD HL,n16", "LD HL,A", "INC HL", "INC H", "DEC H", "LD H,n8", "DAA", "JR Z,e8", "ADD HL,HL", "LD A,HL", "DEC HL", "INC L", "DEC L", "LD L,n8", "CPL", 
											 "JR NC,e8", "LD SP,n16", "LD HL,A", "INC SP", "INC HL", "DEC HL", "LD HL,n8", "SCF", "JR C,e8", "ADD HL,SP", "LD A,HL", "DEC SP", "INC A", "DEC A", "LD A,n8", "CCF", 
											 "LD B,B", "LD B,C", "LD B,D", "LD B,E", "LD B,H", "LD B,L", "LD B,HL", "LD B,A", "LD C,B", "LD C,C", "LD C,D", "LD C,E", "LD C,H", "LD C,L", "LD C,HL", "LD C,A", 
                       "LD D,B", "LD D,C", "LD D,D", "LD D,E", "LD D,H", "LD D,L", "LD D,HL", "LD D,A", "LD E,B", "LD E,C", "LD E,D", "LD E,E", "LD E,H", "LD E,L", "LD E,HL", "LD E,A", 
											 "LD H,B", "LD H,C", "LD H,D", "LD H,E", "LD H,H", "LD H,L", "LD H,HL", "LD H,A", "LD L,B", "LD L,C", "LD L,D", "LD L,E", "LD L,H", "LD L,L", "LD L,HL", "LD L,A", 
											 "LD HL,B", "LD HL,C", "LD HL,D", "LD HL,E", "LD HL,H", "LD HL,L", "HALT", "LD HL,A", "LD A,B", "LD A,C", "LD A,D", "LD A,E", "LD A,H", "LD A,L", "LD A,HL", "LD A,A", 
											 "ADD A,B", "ADD A,C", "ADD A,D", "ADD A,E", "ADD A,H", "ADD A,L", "ADD A,HL", "ADD A,A", "ADC A,B", "ADC A,C", "ADC A,D", "ADC A,E", "ADC A,H", "ADC A,L", "ADC A,HL", "ADC A,A", 
											 "SUB A,B", "SUB A,C", "SUB A,D", "SUB A,E", "SUB A,H", "SUB A,L", "SUB A,HL", "SUB A,A", "SBC A,B", "SBC A,C", "SBC A,D", "SBC A,E", "SBC A,H", "SBC A,L", "SBC A,HL", "SBC A,A", 
											 "AND A,B", "AND A,C", "AND A,D", "AND A,E", "AND A,H", "AND A,L", "AND A,HL", "AND A,A", "XOR A,B", "XOR A,C", "XOR A,D", "XOR A,E", "XOR A,H", "XOR A,L", "XOR A,HL", "XOR A,A", 
											 "OR A,B", "OR A,C", "OR A,D", "OR A,E", "OR A,H", "OR A,L", "OR A,HL", "OR A,A", "CP A,B", "CP A,C", "CP A,D", "CP A,E", "CP A,H", "CP A,L", "CP A,HL", "CP A,A", 
											 "RET NZ", "POP BC", "JP NZ,a16", "JP a16", "CALL NZ,a16", "PUSH BC", "ADD A,n8", "RST $00", "RET Z", "RET", "JP Z,a16", "PREFIX", "CALL Z,a16", "CALL a16", "ADC A,n8", "RST $08", 
											 "RET NC", "POP DE", "JP NC,a16", "ILLEGAL_D3", "CALL NC,a16", "PUSH DE", "SUB A,n8", "RST $10", "RET C", "RETI", "JP C,a16", "ILLEGAL_DB", "CALL C,a16", "ILLEGAL_DD", "SBC A,n8", "RST $18", 
											 "LDH a8,A", "POP HL", "LD C,A", "ILLEGAL_E3", "ILLEGAL_E4", "PUSH HL", "AND A,n8", "RST $20", "ADD SP,e8", "JP HL", "LD a16,A", "ILLEGAL_EB", "ILLEGAL_EC", "ILLEGAL_ED", "XOR A,n8", "RST $28", 
											 "LDH A,a8", "POP AF", "LD A,C", "DI", "ILLEGAL_F4", "PUSH AF", "OR A,n8", "RST $30", "LD HL,SP,e8", "LD SP,HL", "LD A,a16", "EI", "ILLEGAL_FC", "ILLEGAL_FD", "CP A,n8", "RST $38"}; 

	printf("Instruction to implement: %s opcode: %.2x \n", instruction_name[opcode], opcode);

}

void execute(GameBoy *gb){
	void (*instruction[]) (GameBoy *) =
{ NOP, not_impl, not_impl, not_impl, not_impl, DEC_B, LD_B_n8, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, DEC_C, LD_C_n8, not_impl, 
not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, 
JR_NZ_e8, LD_HL_n16, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, 
not_impl, not_impl, LD_address_HLminus_A, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, LD_A_n8, not_impl, 
not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, 
not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, 
not_impl, LD_HC, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, 
not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, 
not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, 
not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, 
not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, XOR_A, 
not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, 
not_impl, not_impl, not_impl, JP_a16, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, 
not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, 
LDH_a8_A, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, 
not_impl, not_impl, not_impl, DI, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl, not_impl };


	instruction[gb->opcode](gb);

}

void handle_interrupts(GameBoy *gb){
	// TO DO
}

/*void decode(GameBoy *gb){
	
}*/
