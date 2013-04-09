#ifndef PUNTO_PASO_GESTOR_H
#define PUNTO_PASO_GESTOR_H

#include <map>
#include <vector>

#include "objeto.h"
#include "punto_paso.h"
#include <SDL/SDL.h>

/**
 *Lleva puntos de paso para objetos
 *la idea es facilitar la ruta que deben
 *seguir los objetos (vehiculo).
 */
class PuntoPasoGestor
{

 private:
  std::map<Objeto*, std::vector<PuntoPaso*> > objPuntos;
  std::map<Objeto*, Uint32> objPuntosPos;
 public:
  PuntoPasoGestor();

  void anidarPuntoPaso(Objeto *, PuntoPaso *);
  void anidarPuntoPaso(Objeto *, Uint32, Uint32, Uint32, Uint32);
  PuntoPaso* puntoPasoA(Objeto *, Uint32);
  PuntoPaso* primerPuntoPaso(Objeto *);
  PuntoPaso* ultimoPuntoPaso(Objeto *);
  Uint32 tamano(Objeto *);
};

#endif
