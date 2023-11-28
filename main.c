#include <stdio.h>
#include "gameboy.h"
#include <stdlib.h>

//int load_rom(FILE *rom);
uint8_t *rom;
uint16_t PC;
uint8_t fetch_temp(){
		return rom[PC++];
}

uint8_t load_rom(FILE *rom_file, uint8_t *rom){
	uint16_t rom_size;
	fseek(rom_file, 0, SEEK_END);
	rom_size = ftell(rom_file);
	rewind(rom_file);
	//printf("%d\n\n", rom_size);
	rom = (uint8_t *) malloc(rom_size);		// +1?
	if(rom == NULL)
		return 1;
	
	fread(rom, sizeof(uint8_t), rom_size, rom_file);

	return 0;
}

int main(int argc, char *argv[]){

	if(argc > 1){
		FILE *rom_file = fopen(argv[1], "r");
		if(rom == NULL){
			printf("Error opening rom\n");
		}else{
			
			uint8_t error = load_rom(rom_file, rom);	
			if(error == 1){
				printf("Error loading rom\n");
				return 0;
			}


			fclose(rom_file);			
			free(rom);
		}
	}	

	return 0;
}
