#include "ppu.h"

void ppu_execute(GameBoy *gb){
	sprite sprites[10];
	for( uint8_t line = 0; line < SCREEN_HEIGHT; ++ line){
		search_OAM(line, &sprites, gb);

	}
	//	render one line
}

sprite *fetch_sprite(uint16_t index, GameBoy *gb){
	if(index >= 0xFE00 && index < 0xFE9F){		//	check if the index is pointing to OAM
		sprite *s = (sprite *) malloc(sizeof(sprite)); 	
		s->y_pos = gb->memory_address[index++];
		s->x_pos = gb->memory_address[index++];
		s->tile_index= gb->memory_address[index++];
		s->attributes = gb->memory_address[index++];

		return s;
	}else{
		return NULL;
	}
}

uint8_t is_sprite_on_current_line(uint8_t screen_Y, uint8_t sprite_Y, uint8_t sprite_height){
	if((screen_Y + 16) < sprite_Y)		
		return FALSE;		// is above the top of the sprite

	if((screen_Y + 16) >= (sprite_Y + sprite_height))		
		return FALSE;		// is below the bottom of the sprite
	

	return TRUE;
}

void copy_sprite(sprite *receiver, sprite *source){
	receiver->y_pos = source->y_pos;	
	receiver->x_pos = source->x_pos;	
	receiver->tile_index = source->tile_index;	
	receiver->attributes = source->attributes;	
}

void sort_sprite(sprite *sprite_array, uint8_t sprite_count){
	sprite buffer;
	uint8_t ordered = FALSE;
	while(!ordered){
		ordered = TRUE;
		for( uint8_t index = 0; index < sprite_count - 1; ++index){
			if(sprite_array[index].x_pos > sprite_array[index + 1].x_pos ){	//	swap
				copy_sprite(&buffer, &sprite_array[index]);
				copy_sprite(&sprite_array[index], &sprite_array[index + 1]);
				copy_sprite(&sprite_array[index] ,&buffer);
				ordered = FALSE;
			}
		}
	}

}

uint8_t get_sprite_height(uint8_t tile_index){
	uint8_t bit_2 = 0b00000100;
	
	if((tile_index & bit_2)  == 0)
		return NORMAL_SPRITE;
	else
		return LARGE_SPRITE;
}

void search_OAM(uint8_t screen_Y, sprite (*current_line_sprites)[10], GameBoy *gb){
	sprite sprite_array[40];
	uint8_t sprite_count = 0;
	sprite *buffer_sprite;
	for(uint16_t index = 0xFE00; index < 0xFE9F; index += 4){

		buffer_sprite = fetch_sprite(index, gb);	
		
		if(is_sprite_on_current_line(screen_Y, buffer_sprite->y_pos, get_sprite_height(buffer_sprite->tile_index) )){
				copy_sprite(&sprite_array[sprite_count], buffer_sprite);
				sprite_count++;
		}
			free(buffer_sprite);
	}

	
	for( uint8_t i = 0; i < 10; ++i ){
		copy_sprite(current_line_sprites[i], &sprite_array[i]);
	}

}


void horizontal_flip_sprite(uint8_t (*sprite)[8][8]){
	uint8_t pixel_buffer;	
	const uint8_t size = 7;
	
	for(uint8_t i = 0; i <= size; ++i){
		for(uint8_t j = 0; j <= size; ++j){
			pixel_buffer = *sprite[i][j];
			*sprite[i][j] = *sprite[i][size - j];
			*sprite[i][size - j] = pixel_buffer;
		}
	}

}

void vertical_flip_sprite(uint8_t (*sprite)[8][8]){
	uint8_t pixel_buffer;	
	const uint8_t size = 7;
	
	for(uint8_t i = 0; i <= size; ++i){
		for(uint8_t j = 0; j <= size; ++j){
			pixel_buffer = *sprite[j][i];
			*sprite[j][i] = *sprite[size - j][i];
			*sprite[size - j][i] = pixel_buffer;
		}
	}

}
