#ifndef VEHICULO_H
#define VEHICULO_H

#include <SDL/SDL.h>
#include "objeto.h"
#include "vehiculo_tipo.h"

/**
 *El vehiculo para el jugador
 *hay diferentes tipos de vehiculos:
 * - 
 *Para los vehiculo se usar el patron de diseno Prototype
 *para facilitar la creacion de los vehiculos
 */


class Vehiculo : public Objeto
{
 public:
  Vehiculo(Uint32 id);
  virtual ~Vehiculo();
  virtual void actualizar();
  virtual void dibujar();

  float obVel() { return vel; }
  float obAccel() { return accel; }
  float obAngulo() { return angulo; }
  VehiculoTipo tipo; 
  //@todo separa entrada .. debe ser mas abstracto
  Uint8 t_accelerar;
  Uint8 t_retroceder;
  Uint8 t_izquierda;
  Uint8 t_derecha;
 protected:


  float vel;
  float accel;
  float angulo;
  

};
#endif
