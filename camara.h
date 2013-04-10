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
  Sint32 lx,ly;

 public:
  static Camara* instancia();

  void seguir(Uint32, Uint32);
  void seguir(Objeto *cosa);
  void asignarLimites(Uint32, Uint32);
  SDL_Rect obRect();

  Sint32 x;
  Sint32 y;
  Uint32 ancho;
  Uint32 alto;

};

#endif
