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
  Objeto defObjeto;
  std::map<Objeto*, std::vector<PuntoPaso*> > objPuntos;
  std::map<Objeto*, Uint32> objPuntosPos;
  std::map<Objeto*, PuntoPaso*> objPuntoActual;
  std::map<Objeto*, PuntoPaso*> objPuntoSiguiente;
 public:
  PuntoPasoGestor();

  void anidarPuntoPaso(Objeto *, PuntoPaso *);
  void anidarPuntoPaso(Objeto *, Uint32, Uint32, Uint32, Uint32);
  void anidarPuntoPaso(Uint32 x, Uint32 y, Uint32 dist_aleja, Uint32 dist_acerca);
  PuntoPaso* puntoPasoA(Objeto *, Uint32);
  PuntoPaso* puntoPasoA(Objeto *);
  PuntoPaso* puntoPasoA(Uint32);
  bool continuadoPuntoPasoA(Objeto *);
  PuntoPaso* primerPuntoPaso(Objeto *);
  PuntoPaso* primerPuntoPaso();
  PuntoPaso* ultimoPuntoPaso(Objeto *);
  PuntoPaso* ultimoPuntoPaso();
  Uint32 tamano(Objeto *);
  Uint32 tamano();
};

#endif
