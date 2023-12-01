#include <stdio.h>
#include "gameboy.h"
#include <stdlib.h>
#include <string.h>

//int load_rom(FILE *rom);
uint8_t *rom;
uint16_t PC;
uint8_t fetch_temp(){
		return rom[PC++];
}

uint8_t load_rom(FILE *rom_file, GameBoy *gb){
	//uint16_t rom_size;
	fseek(rom_file, 0, SEEK_END);
	gb->rom_size = ftell(rom_file);
	rewind(rom_file);
	//printf("%d\n\n", rom_size);
	gb->rom = (uint8_t *) malloc(gb->rom_size);		// +1?
	if(gb->rom == NULL)
		return 1;
	
	fread(gb->rom, sizeof(uint8_t), gb->rom_size, rom_file);

	return 0;
}

void load_rom_memory_address(GameBoy *gb){
	const uint16_t end_section = 0x7FFF;
	for(uint16_t i = 0; i <= end_section; ++i){
		if(i >= gb->rom_size)
			break;
		gb->memory_address[i] = gb->rom[i];
	}

}

void initialize_gameboy(GameBoy *gb){
	gb->PC = 0;
	gb->stop_execution = FALSE;
	gb->opcode = 0;
	gb->frequency = 4190000;

}

int main(int argc, char *argv[]){

	if(argc > 1){
		FILE *rom_file = fopen(argv[1], "r");
		if(rom_file == NULL){
			printf("Error opening rom\n");
		}else{
			GameBoy gb;
			uint8_t error = load_rom(rom_file, &gb);	
			if(error == 1){
				printf("Error loading rom\n");
				return 0;
			}
			initialize_gameboy(&gb);
			load_rom_memory_address(&gb);

			//printf(" result = %.4x\n", join_two_bytes(0xAB, 0xCD));

			while(gb.stop_execution == FALSE){
				//printf("PC = %.4x\n", gb.PC);
				//printf("OPCODE = %.4x\n", gb.opcode);

				//printf("C = %.2x\n", gb.C);
				//printf("H = %.2x\n", gb.H);
				gb.opcode = fetch(&gb);
				execute(&gb);
			}

			fclose(rom_file);			
			free(rom);
		}
	}	

	return 0;
}
