#ifndef JUGADOR_H
#define JUGADOR_H

#include <SDL/SDL.h>
#include <string>
#include "control_tipo.h"
#include "vehiculo.h"
#include <vector>
class Jugador
{
 public:
  Jugador(const char* nombre, IControlTipo *ctipo, Vehiculo *);
  void actualizar(std::vector<Objeto*>& );
  void dibujar();
  IControlTipo *obControlTipo() { return ctipo; }
  Vehiculo *obVehiculo() { return vehiculo;}

  std::string nombre;  
 private:
  IControlTipo *ctipo;
  Vehiculo *vehiculo;
};

#endif
