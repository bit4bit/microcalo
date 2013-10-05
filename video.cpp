#include <iostream>
#include <cstdlib>
#include "video.h"


Video* Video::_self = 0;


Video::Video(): BPP(32) {

  if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0) {
    std::cerr << "Fallo iniciar SDL:" << SDL_GetError() << std::endl;
    exit(EXIT_FAILURE);
  }
  //@todo lo ideal es poder usar la resolucion de 320x240
  //y reescalar imagenes
  ancho = 640;
  alto = 480;
  atexit(SDL_Quit); //@todo terminar todo el programa
  s_pantalla = SDL_SetVideoMode(ancho, alto, BPP, SDL_DOUBLEBUF|SDL_HWSURFACE); //@todo ??como se libera al destr objeto
  if(s_pantalla == NULL) {
    std::cerr << "Fallo asignar video: " << SDL_GetError() << std::endl;
    exit(EXIT_FAILURE);
  }

  SDL_WM_SetCaption("Microcalo 2013",NULL);
}

Video* Video::instancia() {
  if(_self == 0) {
    _self = new Video;			       
  }
  return _self;
}


void Video::actualizar() {
}

void Video::dibujar() {
  SDL_Flip(s_pantalla);
}


/**SDL**/
SDL_Surface* Video::createSurface(Uint32 w, Uint32 h) {
    /* Create a 32-bit surface with the bytes of each pixel in R,G,B,A order,
       as expected by OpenGL for textures */
    SDL_Surface *surface;
    Uint32 rmask, gmask, bmask, amask;

    /* SDL interprets each pixel as a 32-bit number, so our masks must depend
       on the endianness (byte order) of the machine */
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
#else
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0x00000000;
#endif

    surface = SDL_CreateRGBSurface(SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_SRCALPHA, w, h, BPP,
                                   rmask, gmask, bmask, amask);
    if(surface == NULL) {
      return NULL;
      //fprintf(stderr, "CreateRGBSurface failed: %s\n", SDL_GetError());
      //exit(1);
    }
    //SDL_Surface* tmp = displayFormat(surface);
    //SDL_FreeSurface(surface);
    //return tmp;
    return surface;
  }

