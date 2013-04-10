#ifndef VEHICULO_TIPO_H
#define VEHICULO_TIPO_H

#include <SDL/SDL.h>
#include <string>

/**
 *Representa un tipo de vehiculo
 *carro, camiones, volquetas
 *sus propiedas y representacion en imaganes.
 *@todo hacer que el tipo pueda agregar efectos
 *al vehiculo..
 */
class VehiculoTipo
{
 public:
  VehiculoTipo();
  std::string nombre;
  int ancho;
  int alto;

  float max_vel;
  float min_vel;
  float def_accel;
  float def_retro;
  float def_giro;
  float def_giro_frenando;

  /**
   *son 90 columnas de 50x50  desde 0 horizonal mirando derecha
   *girando en el sentido contrario a las agujas del reloj
   */
  SDL_Surface *s_actual;
  SDL_Surface *s_andando;
  SDL_Surface *s_cayendo;
  SDL_Surface *s_saltando;
};

#endif
