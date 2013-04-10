#ifndef ESCENARIO_CARRERA_H
#define ESCENARIO_CARRERA_H

/**
 *Escenario Principal donde se desarrollan las carreras
 *de los jugadores.
 */

#include <SDL/SDL.h>
#include <vector>
#include "escenario.h"
#include "vehiculo.h"
#include "punto_paso_gestor.h"
#include "jugador.h"

class EscenarioCarrera : public Escenario
{
 public:
  EscenarioCarrera();
  virtual ~EscenarioCarrera();
  virtual void actualizar();
  virtual void dibujar();
  
 private:
  std::vector<Objeto*> objetos;
  PuntoPasoGestor puntos_de_paso;
  
  SDL_Surface *fondo; //imagen de fondo por defecto, se usa para redibujados
  Vehiculo* vehiculo;
  std::vector<Vehiculo*> vehiculos;
  std::vector<Jugador*> jugadores;
};

#endif
