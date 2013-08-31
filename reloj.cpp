#include "reloj.h"

Reloj* Reloj::_self = 0;

Reloj::Reloj()
{
  inicia = 0;
  actual = 0;
}

Reloj* Reloj::instancia() {
  if(_self == 0) {
    _self = new Reloj;
  }
  return _self;
}

void Reloj::actualizar() {
  inicia = actual;
  actual = SDL_GetTicks();
}

double Reloj::escala() {
  return (double)(actual - inicia) / 30.0; //30.0 FPS
}

Uint32 Reloj::diff() {
  return (SDL_GetTicks() - inicia);
}
