/**
 *MicroCalo es un videojuego al mejor estilo de MicroMachines
 */

#include <iostream>
#include "cspa.h"
#include "compositor.h"
#include "escenario.h"
#include "escenario_guion.h"
#include "escenario_carrera.h"
#include "escenario_menu.h"

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
  GestorEscenario::bindingScript(Compositor::obScript()->obState());
  Configuracion::bindingScript(Compositor::obScript()->obState());
  VehiculoTipo::bindingScript(Compositor::obScript()->obState());
  CArray<std::string>::bindingScript(Compositor::obScript()->obState());
  Graficador::bindingScript(Compositor::obScript()->obState());
  EscenarioGuion::bindingScript(Compositor::obScript()->obState());
  EscenarioMenu::bindingScript(Compositor::obScript()->obState());
  RWidget::bindingScript(Compositor::obScript()->obState());

  Compositor::obScript()->leerScript("data/util.rb");
  Compositor::obScript()->leerScript("data/configuracion.rb");
  Compositor::obScript()->leerScript("data/vehiculos.rb");

  CArrayString* ar = Compositor::obConfiguracion()->obtenerArregloCadena("mapas");
  for(CArrayString::iterator it = ar->begin(); it != ar->end(); ++it) {
    std::cout << "Mapas desde configuracion:" << (*it) << std::endl;
  }

  EscenarioCarrera* escenarioC = new EscenarioCarrera(Compositor::obConfiguracion()->obtenerLiteral("data_path").append("/").append(ar->front()).c_str());
  
  escenarioC->asignarNombre("carrera");
  Compositor::obGestorEscenario()->agregar((Escenario*)escenarioC);
  Compositor::obGestorEscenario()->activar("intro");

  Compositor::obRecurso();
  hacer {
    Compositor::obReloj()->actualizar();
    SDL_PumpEvents();

    int ai = mrb_gc_arena_save(Compositor::obScript()->obState());
    Compositor::obMando()->actualizar();
    Compositor::obTeclado()->actualizar(SDL_GetKeyState(NULL));
    if(Compositor::obTeclado()->presionado(SDLK_q))
      salir = true;
    if(Compositor::obTeclado()->presionado(SDLK_f))
      Compositor::obVideo()->toggleFullScreen();

    Compositor::obGestorEscenario()->actual()->actualizar();
    Compositor::obVideo()->actualizar();
    

    Compositor::obGestorEscenario()->actual()->dibujar();
       
    video->dibujar();
    mrb_gc_arena_restore(Compositor::obScript()->obState(), ai);
  }mientras(salir == false);


  Compositor::cerrar();

  return 0;
}
