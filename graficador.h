#ifndef GRAFICADOR_H
#define GRAFICADOR_H

#include <SDL/SDL.h>
#include <string>
#include <vector>
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
  int imprimirCuadro(int x, int y, int ancho, int alto, SDL_Color, int);
  int imprimirCuadroRedondo(int x, int y, int ancho, int alto, int rad,  SDL_Color color, int grosor, int alpha);
  int imprimirBorde(int x, int y, int ancho, int alto, SDL_Color, int,  int);
  int imprimirLinea(int x, int y, int x2, int y2, SDL_Color color, int ancho, int alpha);
  int imprimirPoligono(std::vector<std::pair<int, int> >& puntos, SDL_Color color, bool rellenar, int alpha);
  SDL_Surface* obSurface() { return s; }
 private:
  SDL_Surface *s;
};

#endif
