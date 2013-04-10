#ifndef CONTROL_MANDO_H
#define CONTROL_MANDO_H

/**
 *Desde el joystick o mando
 */
#include <SDL/SDL.h>
#include "control_tipo.h"

class ControlMando : public IControlTipo
{
 public:
  ControlMando(Uint8 mando);
  ~ControlMando();
  virtual bool acelerar();
  virtual bool retroceder();
  virtual bool girarDerecha();
  virtual bool girarIzquierda();
 private:
  SDL_Joystick *joy;
};

#endif
