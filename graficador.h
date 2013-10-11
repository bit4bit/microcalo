#ifndef GRAFICADOR_H
#define GRAFICADOR_H

#include <SDL/SDL.h>
#include <string>
#include "exportar_script.h"

/**
 *Herramientas para el dibujado
 */
class Graficador
{
 public:
  static void bindingScript(mrb_state*);
  Graficador(SDL_Surface*);

  void imprimirImagen(int x, int y, std::string ruta);
  void imprimirTexto(int x, int y, std::string, int tamano, SDL_Color);
  void imprimirRecuadro(int x, int y, int ancho, int alto, SDL_Color);
  void imprimirBorde(int x, int y, int ancho, int alto, int grosor, SDL_Color);

  SDL_Surface* obSurface() { return s; }
 private:
  SDL_Surface *s;
};

#endif
