#include <stdio.h>
#include "gameboy.h"
#include <stdlib.h>
#include <string.h>
#include <SDL2/SDL.h>

SDL_Window *window;
//int load_rom(FILE *rom);
uint8_t *rom;
uint16_t PC;
uint8_t fetch_temp(){
		return rom[PC++];
}

uint8_t get_rom(FILE *rom_file, GameBoy *gb){
	fseek(rom_file, 0, SEEK_END);
	gb->rom_size = ftell(rom_file);
	rewind(rom_file);

	gb->rom = (uint8_t *) malloc(gb->rom_size);		// +1?
	if(gb->rom == NULL)
		return 1;
	
	fread(gb->rom, sizeof(uint8_t), gb->rom_size, rom_file);

	return 0;
}

uint8_t get_boot_rom(FILE *file, GameBoy *gb){
	fseek(file, 0, SEEK_END);
	gb->boot_rom_size = ftell(file);
	rewind(file);

	gb->boot_rom = (uint8_t *) malloc(gb->boot_rom_size);		// +1?
	if(gb->boot_rom == NULL)
		return 1;
	
	fread(gb->boot_rom, sizeof(uint8_t), gb->boot_rom_size, file);

	return 0;
}

/*void load_boot_rom_into_memory(GameBoy *gb){
	const uint16_t end_section = 0xFF;
	for(uint16_t i = 0; i <= end_section; ++i){
		if(i >= gb->boot_rom_size)
			break;
		gb->memory_address[i] = gb->boot_rom[i];
	}

}*/

void load_cartridge_into_memory(GameBoy *gb){
	const uint16_t end_section = 0x3FFF;

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
	gb->interrupt_status = ON;
	gb->stack_pointer = 0xFFFE;

}

void init(){
	SDL_Init(SDL_INIT_VIDEO);
  window = SDL_CreateWindow("GameBoy", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
}

void cleanup(){
	SDL_DestroyWindow(window);
  SDL_Quit();
}


int main(int argc, char *argv[]){

	init();
	SDL_Event event;
	GameBoy gb;

	if(argc > 1){
		uint8_t error;
		//------------------loading cartridge-----------------//
		FILE *rom_file = fopen(argv[1], "r");
		
		if(rom_file == NULL){
			printf("Error opening cartridge rom\n");
		}else{
			
			error = get_rom(rom_file, &gb);	
			
			if(error == 1){
				printf("Error loading cartridge rom\n");
				return 0;
			}
			
			load_cartridge_into_memory(&gb);
			
			initialize_gameboy(&gb);	

			// start execution
			while(gb.stop_execution == FALSE){
				SDL_PollEvent(&event); 
  			if (event.type == SDL_QUIT) {
  				gb.stop_execution = TRUE;
  			}			
				//printf("PC = %.4x\n", gb.PC);
				//printf("OPCODE = %.4x\n", gb.opcode);

				//printf("C = %.2x\n", gb.C);
				//printf("H = %.2x\n", gb.H);
				if (gb.interrupt_status == ON){
					handle_interrupts(&gb);
				}
				gb.opcode = fetch(&gb);
				execute(&gb);
			}
			cleanup();
			fclose(rom_file);			
			free(rom);
		}
	}	

	return 0;
}
