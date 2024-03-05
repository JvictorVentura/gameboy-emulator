#include "gameboy.h"
#include <stdbool.h>
#include <stdint.h>

#define BANK_SIZE 16000

#define	INTERRUPT_FLAG 			0xFF0F 
//#define	INTERRUPT_ENABLE 		0xFFFF 
#define JOYPAD 							0xFF00

uint8_t rom_bank00[BANK_SIZE];
uint8_t rom_bank01[BANK_SIZE];

bool load_boot_rom(FILE *file){
  fseek(file, 0, SEEK_END);
	uint16_t size = ftell(file);
	rewind(file);
  
  if(size > BANK_SIZE)
    return false;

	fread(rom_bank00, sizeof(uint8_t), size, file);

  return true;
}

uint8_t fetch(GameBoy *gb){
	return gb->memory_address[gb->PC++];
}

void jump(GameBoy *gb, const uint16_t address){
	gb->PC = address;
}

void load_16b_register(uint8_t *high_reg, uint8_t *low_reg, uint16_t value){
	*high_reg = (value >> 8);
	*low_reg = value & 0x00FF;
}

void load_8b_register(uint8_t *reg, uint8_t value){
	*reg = value;
}

void stack_push_n16(GameBoy *gb, const uint16_t value){

	gb->stack_pointer--;
	gb->memory_address[gb->stack_pointer] = value >> 8;
		
	gb->stack_pointer--;
	gb->memory_address[gb->stack_pointer] = value & 0x00FF;
}


uint16_t stack_pop_n16(GameBoy *gb){
	
	uint8_t lower_byte = gb->memory_address[gb->stack_pointer];
	gb->stack_pointer++;

	uint8_t upper_byte = gb->memory_address[gb->stack_pointer];
	gb->stack_pointer++;

	return join_two_bytes(upper_byte, lower_byte);

}

uint16_t get_next_two_bytes(GameBoy *gb){
	uint8_t byte_low = fetch(gb);
	uint8_t byte_high = fetch(gb);
	return join_two_bytes(byte_high, byte_low);
}

void handle_interrupts(GameBoy *gb){
	// TO DO
}

bool write_to_address(const uint16_t address){
  
  if(address >= 0x8000 && address < 0xA000){
    //  Write to Video RAM (VRAM)
    return true;
  }

  if(address >= 0xA000 && address < 0xC000){
    //  Write to External RAM 
    return true;
  }

  if(address >= 0xC000 && address < 0xD000){
    //  Write to Work RAM (WRAM)
    return true;
  }

  if(address >= 0xE000 && address <= 0xFDFF){
    // Mirror of C000~DDFF (ECHO RAM)
    return true;
  }

  if(address >= 0xFE00 && address <= 0xFE9F){
    //  Write to OAM
    return true;
  }

  if(address >= 0xFF00 && address <= 0xFF7F){
    //  Write to I/O Registers 
    return true;
  }

  if(address >= 0xFF80 && address <= 0xFFFE){
    //  Write to High RAM (HRAM)
    return true;
  }

  if(address == 0xFFFF){
    //  Interrupts Enable Register (IE)
    return true;
  }



  if(address >= 0x0000 && address < 0x4000){
    //  ROM bank 00
    return false;
  }

  if(address >= 0x4000 && address < 0x8000){
    //  ROM bank 00
    return false;
  }

  if(address >= 0xFEA0 && address <= 0xFEFF){
    // Not usable 
    return false;
  }

  return false;
}
