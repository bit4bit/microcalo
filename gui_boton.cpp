#include "gui_boton.h"

#include <mrubybind.h>

GuiBoton::GuiBoton(Graficador* graficador, int _x, int _y, std::string _texto): Widget(graficador, _x, _y),
									 texto(_texto)
{
}

void GuiBoton::actualizar() {
}

void GuiBoton::dibujar() {
}

