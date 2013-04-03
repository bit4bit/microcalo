#ifndef CAMARA_H
#define CAMARA_H

#include <SDL/SDL.h>
#include "objeto.h"
class Camara
{
 protected:
  Camara();

 private:
  static Camara* _self;


 public:
  static Camara* instancia();

  void seguir(Uint32, Uint32);
  void seguir(Objeto *cosa);
  SDL_Rect obRect();

  Uint32 x;
  Uint32 y;
  Uint32 ancho;
  Uint32 alto;
};

#endif
