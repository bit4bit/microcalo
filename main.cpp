/**
 *MicroCalo es un videojuego al mejor estilo de MicroMachines
 */

#include <iostream>
#include "cspa.h"
#include "compositor.h"
#include "escenario.h"
#include "escenario_intro.h"
#include "escenario_carrera.h"
#include "vehiculo.h"
#include "tmx_render.h"

#define DEFAULT_SCRIPT "data/default.scm"

int main(int argc, char **argv)
{
  SDL_Event ev;
  bool salir = false;

  Video* video = Compositor::obVideo(); //se inicializa vide
  Compositor::obMando();
  Compositor::obTexto();
  Compositor::obConfiguracion();
  Compositor::obScript();
  Configuracion::bindingScript(Compositor::obScript()->obState());

  Compositor::obScript()->leerScript("data/util.rb");
  Compositor::obScript()->leerScript("data/configuracion.rb");

  Compositor::cerrar();
  return 0;
  EscenarioIntro escenario_intro= EscenarioIntro();
  //Escenario *escenario = (Escenario*)&escenario_intro;
  //script_cargar_escenario_intro(&escenario_intro, "escenario-intro");
  EscenarioCarrera escenarioC = EscenarioCarrera("data/mapa1.tmx");
  Escenario *escenario = (Escenario*)&escenarioC;

  Colision *colision = Compositor::obColision();


  //TmxRender *tmxRender = new TmxRender();
  //tmxRender->CargarDesdeArchivo("data/mapa1.tmx");
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
    colision->dibujar();
       
    /*SDL_Rect srect;
    srect.x = 10;
    srect.y = 0;
    srect.w = 640;
    srect.h = 480;
    tmxRender->blit("fondo", &srect, Compositor::obVideo()->obSurface(), NULL);
    */
    video->dibujar();
    
  }mientras(salir == false);
  return 0;
}
