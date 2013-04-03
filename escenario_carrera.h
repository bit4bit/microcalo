#ifndef ESCENARIO_CARRERA_H
#define ESCENARIO_CARRERA_H

/**
 *Escenario Principal donde se desarrollan las carreras
 *de los jugadores.
 */

#include "escenario.h"
#include "vehiculo.h"

class EscenarioCarrera : public Escenario
{
 public:
  EscenarioCarrera();
  virtual ~EscenarioCarrera();
  virtual void actualizar();
  virtual void dibujar();
  
 private:
  SDL_Surface *fondo; //imagen de fondo por defecto, se usa para redibujados
  Vehiculo* vehiculo;
};

#endif
