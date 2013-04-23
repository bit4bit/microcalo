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
  Vehiculo(Uint32 id, Uint32, Uint32, Uint32);
  virtual ~Vehiculo();
  virtual void actualizar();
  virtual void dibujar();

  float obVel() { return vel; }
  float obAccel() { return accel; }
  float obAngulo() { return angulo; }
  VehiculoTipo tipo; 
  //@todo separa entrada .. debe ser mas abstracto
  //llamar antes de actualizar
  void acelerar() {acelerarP = true;}
  void retroceder() {retrocederP = true;}
  void girarIzquierda() {izquierdaP = true;}
  void girarDerecha() {derechaP = true;}
  void choque(); //efecto de choque
  void choqueRetroceder();
 protected:
  bool acelerarP;
  bool retrocederP;
  bool izquierdaP;
  bool derechaP;
  bool choqueP;				       
  float vel;
  float accel;
  float angulo;
  

};
#endif
