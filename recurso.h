#ifndef RECURSO_H
#define RECURSO_H

#include <SDL/SDL.h>
#include <string>

/**
 *Carga imagenes, sonidos, etc..
 */
class Recurso
{
 protected:
  Recurso();

 private:
  static Recurso* _self;

 public:
  static Recurso* instancia();

  SDL_Surface* cargarImagen(const char* ruta);
};

#endif
