#ifndef CONTROL_TECLADO_H
#define CONTROL_TECLADO_H

#include <SDL/SDL.h>
#include "control_tipo.h"

class ControlTeclado : public IControlTipo
{
 public:
  ControlTeclado(Uint8, Uint8, Uint8, Uint8);
  virtual bool acelerar();
  virtual bool retroceder();
  virtual bool girarIzquierda();
  virtual bool girarDerecha();

 private:
  Uint8 t_acelerar;
  Uint8 t_retroceder;
  Uint8 t_izquierda;
  Uint8 t_derecha;
};

#endif
