#include <iostream>
#include <cstdlib>
#include "video.h"


Video* Video::_self = 0;

Video::Video() {
  if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0) {
    std::cerr << "Fallo iniciar SDL:" << SDL_GetError() << std::endl;
    exit(EXIT_FAILURE);
  }
  //@todo lo ideal es poder usar la resolucion de 320x240
  //y reescalar imagenes
  ancho = 640;
  alto = 480;
  atexit(SDL_Quit); //@todo terminar todo el programa
  s_pantalla = SDL_SetVideoMode(ancho, alto, 16, SDL_DOUBLEBUF|SDL_HWSURFACE); //@todo ??como se libera al destr objeto
  if(s_pantalla == NULL) {
    std::cerr << "Fallo asignar video: " << SDL_GetError() << std::endl;
    exit(EXIT_FAILURE);
  }
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
