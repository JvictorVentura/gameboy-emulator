#define WIDTH 160
#define HEIGHT 144
#define RAM_SIZE 8192

typedef unsigned char byte;
typedef unsigned short int16b;

struct {
	int16b AF;
	int16b BC;
	int16b DE;
	int16b HL;

	int16b stack_pointer;
	int16b PC;

} Cpu;

byte RAM[RAM_SIZE];

byte Screen[HEIGHT][WIDTH];

byte get_higher_bits(int16b *Register){
	return *Register >> 8;
}

void set_higher_bits( byte value, int16b *Register ){
	//clean the register
	*Register += value << 8;
}

byte get_lower_bits(int16b *Register){
	return *Register << 8;
}

void set_lower_bits( byte value, int16b *Register ){
	//clean the register
	*Register += value >> 8;
}

void set_16bit_register( int16b  value, int16b *Register ){
	*Register = value ;
}

void increment_16bit_register( int16b *Register ){
	(*Register)++;	
}
