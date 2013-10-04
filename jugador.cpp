#include "jugador.h"
#include <vector>

Jugador::Jugador(const char *_nombre, IControlTipo *_ctipo, Vehiculo *_veh) {
  nombre.assign(_nombre);
  ctipo = _ctipo;
  vehiculo = _veh;
}


void Jugador::actualizar(std::vector<Objeto*> &objetos) {
  if(ctipo->acelerar())
    vehiculo->acelerar();
  
  if(ctipo->retroceder())
    vehiculo->retroceder();
  
  if(ctipo->girarIzquierda())
    vehiculo->girarIzquierda();

  if(ctipo->girarDerecha())
    vehiculo->girarDerecha();

  vehiculo->actualizar(objetos);
}

void Jugador::dibujar()
{
  vehiculo->dibujar();
}
