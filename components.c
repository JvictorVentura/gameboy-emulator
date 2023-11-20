//#define WIDTH 160
//#define HEIGHT 144
//#define RAM_SIZE 8192
#include <stdint.h>
#include "gameboy.h"

//typedef struct {
//	uint16_t AF;
//	uint16_t BC;
//	uint16_t DE;
//	uint16_t HL;

//	uint16_t stack_pointer;
//	uint16_t PC;

//} CPU;

//CPU cpu;
//uint8_t ram[RAM_SIZE];
//uint8_t screen[HEIGHT][WIDTH];
//enum{HIGHER, LOWER};

uint8_t fetch(){
	return ram[cpu.PC++];
}

