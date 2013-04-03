#include <iostream>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "compositor.h"
#include "recurso.h"



Recurso* Recurso::_self = 0;

Recurso::Recurso(){
}

Recurso* Recurso::instancia() {
  if(_self == 0) {
    _self = new Recurso;
  }
  return _self;
}

SDL_Surface* Recurso::cargarImagen(const char *ruta) {
  SDL_Surface *tmp, *ret;
  tmp = IMG_Load(ruta);
  if(tmp == NULL) {
    std::cerr << "Fallo cargar imagen: " << ruta << std::endl;
    return NULL;
  }
  ret = SDL_DisplayFormatAlpha(tmp);
  SDL_FreeSurface(tmp);
  return ret;
}
