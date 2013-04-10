#include "control_mando.h"

ControlMando::ControlMando(Uint8 mando)
{
  //@todo generar excepcion cuando no hay mando?
  joy = SDL_JoystickOpen(mando);
  
}

ControlMando::~ControlMando()
{
  SDL_JoystickClose(joy);
}


bool ControlMando::acelerar()
{
  return SDL_JoystickGetButton(joy, 0) == 1 ? true : false;
}

bool ControlMando::retroceder()
{
  return SDL_JoystickGetButton(joy, 1) == 1 ? true : false;
}

bool ControlMando::girarDerecha()
{
  return SDL_JoystickGetAxis(joy, 0) > 0 ? true : false;
}

bool ControlMando::girarIzquierda()
{
  return SDL_JoystickGetAxis(joy, 0) < 0 ? true : false;
}
