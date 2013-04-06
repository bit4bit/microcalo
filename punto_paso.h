#ifndef PUNTO_PASO_H
#define PUNTO_PASO_H

#include <SDL/SDL.h>
#include "objeto.h"

/**
 *Esta clase es el punto al cual
 *se debe acercar el vehiculo.
 *La idea inicial para estos son para indicar
 *la ruta hacer en la carrera. Pero la imagacion.
 *
 */
class PuntoPaso
{
 public:
  PuntoPaso(Uint32 x, Uint32 y, Uint32 distAlejamiento, Uint32 distAcerca);
  
  bool distanciaPermitida(Objeto *);
  bool estaCerca(Objeto *);

 private:
  Uint32 escenario_x;
  Uint32 escenario_y;
  Uint32 dist_alejamiento; //maxima distancia que se puede alejar
  Uint32 dist_acercamiento; //distancia maxima a la que se debe acercar
};

#endif
