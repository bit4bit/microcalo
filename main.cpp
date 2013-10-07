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
#include "carray.h"
#include <string>

int main(int argc, char **argv)
{
  SDL_Event ev;
  bool salir = false;

  Video* video = Compositor::obVideo(); //se inicializa vide
  Compositor::obAudio();
  Compositor::obMando();
  Compositor::obTexto();
  Compositor::obConfiguracion();
  Compositor::obScript();
  Compositor::obGestorVehiculoTipo();
  Compositor::obGestorEscenario();
  Compositor::obColision();
  //inicializa enlaces a VM
  Configuracion::bindingScript(Compositor::obScript()->obState());
  VehiculoTipo::bindingScript(Compositor::obScript()->obState());
  CArray<std::string>::bindingScript(Compositor::obScript()->obState());
  Compositor::obScript()->leerScript("data/util.rb");
  Compositor::obScript()->leerScript("data/configuracion.rb");
  Compositor::obScript()->leerScript("data/vehiculos.rb");

  CArrayString* ar = Compositor::obConfiguracion()->obtenerArregloCadena("mapas");
  for(CArrayString::iterator it = ar->begin(); it != ar->end(); ++it) {
    std::cout << "Mapas desde configuracion:" << (*it) << std::endl;
  }

  //EscenarioIntro escenario_intro=EscenarioIntro();
  //Escenario *escenario = (Escenario*)&escenario_intro;
  //script_cargar_escenario_intro(&escenario_intro, "escenario-intro");
  EscenarioCarrera* escenarioC = new EscenarioCarrera(Compositor::obConfiguracion()->obtenerLiteral("data_path").append("/").append(ar->front()).c_str());
  
  Compositor::obGestorEscenario()->agregar("carrera", (Escenario*)escenarioC);
  Compositor::obGestorEscenario()->activar("carrera");

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

    Compositor::obGestorEscenario()->actual()->actualizar();
    Compositor::obVideo()->actualizar();
    

    Compositor::obGestorEscenario()->actual()->dibujar();
       
    /*SDL_Rect srect;
    srect.x = 10;
    srect.y = 0;
    srect.w = 640;
    srect.h = 480;
    tmxRender->blit("fondo", &srect, Compositor::obVideo()->obSurface(), NULL);
    */
    video->dibujar();
    
  }mientras(salir == false);


  Compositor::cerrar();

  return 0;
}
