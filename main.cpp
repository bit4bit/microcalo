/**
 *MicroCalo es un videojuego al mejor estilo de MicroMachines
 */

#include <iostream>
#include <libguile.h>
#include "cspa.h"
#include "compositor.h"
#include "escenario.h"
#include "escenario_intro.h"
#include "escenario_carrera.h"
#include "vehiculo.h"
#include "script.h"

#define DEFAULT_SCRIPT "data/default.scm"

int main(int argc, char **argv)
{
  SDL_Event ev;
  bool salir = false;
  scm_with_guile(iniciar_script, (void*)DEFAULT_SCRIPT);

  Video* video = Compositor::obVideo(); //se inicializa vide
  Compositor::obMando();
  Compositor::obTexto();
  EscenarioIntro escenario_intro= EscenarioIntro();
  //Escenario *escenario = (Escenario*)&escenario_intro;
  //script_cargar_escenario_intro(&escenario_intro, "escenario-intro");
  EscenarioCarrera escenarioC = EscenarioCarrera();
  Escenario *escenario = (Escenario*)&escenarioC;

  Colision *colision = Compositor::obColision();
  Compositor::obRecurso();
  hacer {
    Compositor::obReloj()->actualizar();
    SDL_PumpEvents();

    Compositor::obMando()->actualizar();
    Compositor::obTeclado()->actualizar(SDL_GetKeyState(NULL));
    if(Compositor::obTeclado()->presionado(SDLK_q))
      salir = true;
    if(Compositor::obTeclado()->presionado(SDLK_f))
      Compositor::obVideo()->toggleFullScreen();

    escenario->actualizar();
    Compositor::obVideo()->actualizar();

    escenario->dibujar();
    video->dibujar();
    colision->dibujar();
  }mientras(salir == false);
  return 0;
}
