#include <stdint.h>
#include "gameboy.h"

uint8_t fetch(GameBoy *gb){
	return gb->ram[gb->PC++];
}

