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
	int16b SP;
	int16b PC;

} Cpu;
