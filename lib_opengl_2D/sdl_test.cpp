#include <string.h>
//#include <SDL/SDL.h>
#include "../../.brew/Cellar/sdl/1.2.15/include/SDL/SDL.h"

#include <openGL/gl.h>
#include <iostream>

//g++ -L ~/.brew/Cellar/sdl/1.2.15/lib -lSDL -lpthread sdl_test.cpp -o sdl_run

//g++ ~/.brew/Cellar/sdl/1.2.15/lib/libSDL.a ~/.brew/Cellar/sdl/1.2.15/lib/libSDLmain.a -lpthread sdl_test.cpp -o sdl_run
//g++ -L ~/.brew/Cellar/sdl/1.2.15/lib/ -lSDLmain -L ~/.brew/Cellar/sdl/1.2.15/lib/-lSDL -framework Cocoa -lpthread sdl_test.cpp -o sdl_run

//clang++ `sdl2-config --libs` `sdl2-config --cflags` -lpthread sdl_test.cpp -o sdl_run
//clang++ `sdl-config --libs` `sdl-config --cflags` -lpthread sdl_test.cpp -o sdl_run
using namespace std;
 
int main(int argc, char *argv[]) {
 
  SDL_Surface *screen;
 
  if(SDL_Init(SDL_INIT_VIDEO)<0) {
    cout << "Failed SDL_Init " << SDL_GetError() << endl;
    return 1;
  }
 
  screen=SDL_SetVideoMode(800,600,32,SDL_ANYFORMAT);
  if(screen==NULL) {
    cout << "Failed SDL_SetVideoMode: " << SDL_GetError() << endl;
    SDL_Quit();
    return 1;
  }
 
  for(;;) {
    SDL_Flip(screen);
    SDL_LockSurface(screen);
    for(int n=0;n<1000;n++) {
      int x=rand()%800;
      int y=rand()%600;
      int pixel=rand()*100000;
      int bpp = screen->format->BytesPerPixel;
      Uint8 *p = (Uint8 *)screen->pixels + y * screen->pitch + x * bpp;
      if((x>screen->w)||(y>screen->h)||(x<0)||(y<0)) return 0;
      *(Uint32 *)p = pixel;
    }
 
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
      if(event.key.keysym.sym == SDLK_c     ) { SDL_FillRect(screen,NULL,0); }
    }
 
    SDL_UnlockSurface(screen);
  }
  SDL_Quit();
 
  return 0;
}