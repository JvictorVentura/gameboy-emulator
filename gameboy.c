#include <stdint.h>
#include "gameboy.h"

uint8_t fetch(GameBoy *gb){
	return gb->ram[gb->PC++];
}

void decode(GameBoy *gb, uint8_t opcode){
	

}
