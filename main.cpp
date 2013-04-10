/**
 *MicroCalo es un videojuego al mejor estilo de MicroMachines
 */
#include <iostream>
#include "cspa.h"
#include "compositor.h"
#include "escenario.h"
#include "escenario_carrera.h"
#include "vehiculo.h"

int main(int argc, char **argv)
{
  SDL_Event ev;
  bool salir = false;

  Video* video = Compositor::obVideo(); //se inicializa vide
  Compositor::obMando();
  EscenarioCarrera escenario = EscenarioCarrera();

  hacer {
    Compositor::obReloj()->actualizar();
    SDL_PumpEvents();

    Compositor::obMando()->actualizar();
    Compositor::obTeclado()->actualizar(SDL_GetKeyState(NULL));
    if(Compositor::obTeclado()->presionado(SDLK_q))
      salir = true;
    if(Compositor::obTeclado()->presionado(SDLK_f))
      Compositor::obVideo()->toggleFullScreen();

    escenario.actualizar();
    Compositor::obVideo()->actualizar();

    escenario.dibujar();
    video->dibujar();
  }mientras(salir == false);
  return 0;
}
