#include "mando.h"

Mando* Mando::_self = 0;

Mando::Mando()
{
  SDL_InitSubSystem(SDL_INIT_JOYSTICK);
  SDL_JoystickEventState(SDL_IGNORE);
}

Mando* Mando::instancia() {
  if(_self == 0) {
    _self = new Mando();
  }
  return _self;
}

void Mando::actualizar() {
  SDL_JoystickUpdate();
}
