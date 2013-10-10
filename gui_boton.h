#ifndef GUI_BOTON_H
#define GUI_BOTON_H

#include "gui.h"
#include "graficador.h"
#include "exportar_script.h"
#include <string>

class GuiBoton : public Widget
{
 public:

  Boton(Graficador*, int x, int y, std::string texto);
  virtual void actualizar();
  virtual void dibujar();
  
 private:
  std::string texto;
};


#endif
