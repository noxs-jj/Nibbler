#include <string.h>
#include <stdio.h>
#include <openGL/gl.h>
#include <openGL/gl.h>
#include <iostream>
//#include <SDL/SDL.h>
//#include "../../.brew/Cellar/sdl/1.2.15/include/SDL/SDL.h"
#include "../../.brew/Cellar/sdl2/2.0.3/include/SDL2/SDL.h"



//g++ -L ~/.brew/Cellar/sdl/1.2.15/lib -lSDL -lpthread sdl_test.cpp -o sdl_run

//g++ ~/.brew/Cellar/sdl/1.2.15/lib/libSDL.a ~/.brew/Cellar/sdl/1.2.15/lib/libSDLmain.a -lpthread sdl_test.cpp -o sdl_run
//g++ -L ~/.brew/Cellar/sdl/1.2.15/lib/ -lSDLmain -L ~/.brew/Cellar/sdl/1.2.15/lib/-lSDL -framework Cocoa -lpthread sdl_test.cpp -o sdl_run

//clang++ `sdl2-config --libs` `sdl2-config --cflags` -lpthread sdl_test.cpp -o sdl_run
//clang++ `sdl-config --libs` `sdl-config --cflags` -lpthread sdl_test.cpp -o sdl_run


int main(int argc, char** argv)
{
    /* Initialisation simple */
    if (SDL_Init(SDL_INIT_VIDEO) != 0 )
    {
        fprintf(stdout,"Échec de l'initialisation de la SDL (%s)\n",SDL_GetError());
        return -1;
    }

    {
        /* Création de la fenêtre */
        SDL_Window* pWindow = NULL;
        pWindow = SDL_CreateWindow("Ma première application SDL2",SDL_WINDOWPOS_UNDEFINED,
                                                                  SDL_WINDOWPOS_UNDEFINED,
                                                                  640,
                                                                  480,
                                                                  SDL_WINDOW_SHOWN);

        if( pWindow )
        {
            SDL_Delay(3000); /* Attendre trois secondes, que l'utilisateur voie la fenêtre */

            SDL_DestroyWindow(pWindow);
        }
        else
        {
            fprintf(stderr,"Erreur de création de la fenêtre: %s\n",SDL_GetError());
        }
    }

    SDL_Quit();

    return 0;
}