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
  RWidget(Graficador*, int x, int y);
  int x;
  int y;
  void actualizar();
  void dibujar();
  void asignarRObjeto(mrb_value v) { robj = v;}
  Graficador* obGraficador() { return graficador;}
 protected:

  
  int ancho;
  int alto;
  mrb_value robj;
  Graficador* graficador;
};



#endif
