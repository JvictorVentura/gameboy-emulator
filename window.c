#include "window.h"

SDL_Window *window;
SDL_Event event;
void init(){
	SDL_Init(SDL_INIT_VIDEO);
  window = SDL_CreateWindow("GameBoy", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 800, 600, SDL_WINDOW_SHOWN);
}

void cleanup(){
	SDL_DestroyWindow(window);
  SDL_Quit();
}

void get_event(){
	SDL_PollEvent(&event); 
}

uint8_t is_event_quit(){
	if (event.type == SDL_QUIT){
		printf("%d\n",event.type);
		return true;
	}else{
		return false;
	}
}
