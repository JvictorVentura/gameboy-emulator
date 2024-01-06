#include "gameboy.h"
#include <stdlib.h>
#include "ppu.h"

void ppu_execute(GameBoy *gb){
	//	render one line
}

sprite *fetch_sprite(uint16_t index, GameBoy *gb){
	if(index >= 0xFE00 && index <= 0xFE9F){		//	check if the index is pointing to OAM
		sprite *s = (sprite *) malloc(sizeof(sprite)); 	
		s->y_pos = gb->memory_address[index++];
		s->x_pos = gb->memory_address[index++];
		s->sprite_location= gb->memory_address[index++];
		s->attributes = gb->memory_address[index++];

		return s;
	}else{
		return NULL;
	}
}
