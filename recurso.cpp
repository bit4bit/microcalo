#include "cspa.h"
#include <iostream>

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include "compositor.h"
#include "recurso.h"
#include <SDL/sge.h>


Recurso* Recurso::_self = 0;

Recurso::Recurso(){
}

Recurso* Recurso::instancia() {
  si(_self == 0) {
    _self = new Recurso;
  }
  retorna _self;
}

SDL_Surface* Recurso::cargarImagen(const char *ruta, bool has_alpha) {
  SDL_Surface *tmp, *ret;
  tmp = IMG_Load(ruta);
  si(tmp == NULL) {
    std::cerr << "Fallo cargar imagen: " << ruta << std::endl;
    retorna NULL;
  }
  if(!has_alpha)
    ret = SDL_DisplayFormat(tmp);
  else
    ret = SDL_DisplayFormatAlpha(tmp);

  SDL_FreeSurface(tmp);
  retorna ret;
}

SDL_Surface* Recurso::cargarImagen(const char *ruta, Uint32 key) {
  SDL_Surface *tmp = IMG_Load(ruta);
  if(!tmp) return NULL;
  SDL_SetColorKey(tmp, SDL_SRCCOLORKEY, key);
  SDL_Surface *rtmp = SDL_DisplayFormat(tmp);
  SDL_FreeSurface(tmp);
  retorna rtmp;
}


SDL_Surface* Recurso::cargarImagen(const char *ruta, Uint32 x, Uint32 y) {
  SDL_Surface *tmp = IMG_Load(ruta);
  if(!tmp) return NULL;
  SDL_SetColorKey(tmp, SDL_SRCCOLORKEY, sge_GetPixel(tmp, x, y));
  SDL_Surface *rtmp = SDL_DisplayFormat(tmp);
  SDL_FreeSurface(tmp);
  retorna rtmp;
}
