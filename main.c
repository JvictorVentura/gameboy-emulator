#include <stdio.h>
#include "gameboy.h"

//int load_rom(FILE *rom);

int main(int argc, char *argv[]){

	if(argc > 1){
		FILE *rom = fopen(argv[1], "r");
		if(rom == NULL){
			printf("Error opening rom\n");
		}else{
			
			


			fclose(rom);			
		}
	}	

	return 0;
}
