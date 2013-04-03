/**
 *MicroCalo es un videojuego al mejor estilo de MicroMachines
 */
#include <iostream>

#include "compositor.h"
#include "escenario.h"
#include "escenario_carrera.h"
#include "vehiculo.h"

int main(int argc, char **argv)
{
  SDL_Event ev;
  bool salir = false;

  Video* video = Compositor::obVideo(); //se inicializa vide

  EscenarioCarrera escenario = EscenarioCarrera();

  do {
    Compositor::obReloj()->actualizar();
    SDL_PumpEvents();

    
    Compositor::obTeclado()->actualizar(SDL_GetKeyState(NULL));
    if(Compositor::obTeclado()->presionado(SDLK_q))
      salir = true;

    escenario.actualizar();
    Compositor::obVideo()->actualizar();

    escenario.dibujar();
    video->dibujar();
  }while(salir == false);
  return 0;
}
