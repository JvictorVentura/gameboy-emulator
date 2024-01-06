#include "gameboy.h"
#include <stdlib.h>
#include "ppu.h"

void ppu_execute(GameBoy *gb){
	//	render one line
}

sprite *fetch_sprite(uint16_t index, GameBoy *gb){
	if(index >= 0xFE00 && index < 0xFE9F){		//	check if the index is pointing to OAM
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

uint8_t is_sprite_on_current_line(uint8_t screen_Y, uint8_t sprite_Y){
	if( screen_Y == sprite_Y )
		return TRUE;
	else
		return FALSE;

}

void copy_sprite_to_array(sprite *buffer_sprite, sprite *sprite_array[10], uint8_t sprite_count){
	sprite_array[sprite_count]->y_pos = buffer_sprite->y_pos;	
	sprite_array[sprite_count]->x_pos = buffer_sprite->x_pos;	
	sprite_array[sprite_count]->sprite_location = buffer_sprite->sprite_location;	
	sprite_array[sprite_count]->attributes = buffer_sprite->attributes;	
}

void search_OAM(uint8_t screen_Y, sprite *current_line_sprites[], GameBoy *gb){
	sprite sprite_array[10];
	uint8_t sprite_count = 0;
	sprite *buffer_sprite;
	for(uint16_t index = 0xFE00; index < 0xFE9F; index += 4){
		if(is_sprite_on_current_line(screen_Y, gb->memory_address[index]) ){
			buffer_sprite = fetch_sprite(index, gb);	
			copy_sprite_to_array(buffer_sprite, sprite_array, sprite_count);
			free(buffer_sprite);
			sprite_count++;
		}

	}

}
