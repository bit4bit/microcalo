#ifndef ESCENARIO_MENU_H
#define ESCENARIO_MENU_H

#include <SDL/SDL.h>
#include <map>
#include <string>
#include <vector>
#include <utility>
#include "exportar_script.h"
#include "compositor.h"
#include "escenario.h"
#include "gui.h"
#include "graficador.h"



/**
 *Permite graficar botones, cajas de texto
 *ventanas emergentes..etc
 * desde Ruby principalmente
 */
class EscenarioMenu : public Escenario
{
 public:
  static void bindingScript(mrb_state *);
  EscenarioMenu();
  ~EscenarioMenu();

  virtual void actualizar();
  virtual void dibujar();

  void agregarWidget(RWidget*); 
  Graficador* obGraficador();
  
 private:
  std::vector<RWidget*> widgets;
  std::vector<RWidget*>::iterator iter_widgets;
  SDL_Surface* s_fondo;
  SDL_Surface* imagen;
  Graficador* graficador;
  RWidget* widget_activo;
};

#endif
