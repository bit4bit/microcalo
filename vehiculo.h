#ifndef VEHICULO_H
#define VEHICULO_H

#include <SDL/SDL.h>
#include "objeto.h"

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
  
  int ancho;
  int alto;
  float max_vel;
  float min_vel;
  float def_accel;
  float def_retro;
  float def_giro;
  float def_giro_frenando;
  
 protected:
  SDL_Surface *s_actual;
  SDL_Surface *s_andando;
  SDL_Surface *s_cayendo;
  SDL_Surface *s_saltando;

  float vel;
  float accel;
  float angulo;
  
  Uint8 t_accelerar;
  Uint8 t_retroceder;
  Uint8 t_izquierda;
  Uint8 t_derecha;
};
#endif
