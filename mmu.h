#include "gameboy.h"

uint8_t fetch(GameBoy *gb);
void jump(GameBoy *gb, uint16_t address);
void load_16b_register(uint8_t *high_reg, uint8_t *low_reg, uint16_t value);
void load_8b_register(uint8_t *reg, uint8_t value);
void stack_push_n16(GameBoy *gb, uint16_t value);
uint16_t stack_pop_n16(GameBoy *gb);
uint16_t get_next_two_bytes(GameBoy *gb);

