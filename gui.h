#ifndef GUI_H
#define GUI_H

#include <SDL/SDL.h>
#include "exportar_script.h"
#include "graficador.h"
#include <string>
#include <mruby.h>


class RWidget : public ExportarScript
{
 public:
  static void bindingScript(mrb_state *);
  RWidget(int x, int y, int, int);
  ~RWidget();
  int x;
  int y;
  void actualizar();
  void actualizarActivo();
  void dibujar();
  void asignarRObjeto(mrb_value v) { robj = v;}
  Graficador* obGraficador() { return graficador;}
  int obAncho() { return ancho;}
  int obAlto() { return alto;}
 protected:

  
  int ancho;
  int alto;
  mrb_value robj;
  Graficador* graficador;
  SDL_Surface* s;
};



#endif
