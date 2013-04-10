#include "compositor.h"
#include "control_teclado.h"

ControlTeclado::ControlTeclado(Uint8 _t_acelerar, Uint8 _t_retroceder, Uint8 _t_izquierda, Uint8 _t_derecha) :
  t_acelerar(_t_acelerar), t_retroceder(_t_retroceder), t_izquierda(_t_izquierda), t_derecha(_t_derecha)
{
}


bool ControlTeclado::acelerar() {
  return Compositor::obTeclado()->presionado(t_acelerar);
}

bool ControlTeclado::retroceder() {
  return Compositor::obTeclado()->presionado(t_retroceder);
}

bool ControlTeclado::girarIzquierda() {
  return Compositor::obTeclado()->presionado(t_izquierda);
}

bool ControlTeclado::girarDerecha() {
  return Compositor::obTeclado()->presionado(t_derecha);
}
 
