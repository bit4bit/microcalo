#ifndef RELOJ_H
#define RELOJ_H

#include <SDL/SDL.h>

/**
 *Lleva los tiempos del juego
 *esto es usado para controlar el movimiento,
 *el graficado, la actualizacion etc..
 */
class Reloj
{
 protected:
  Reloj();
  
 private:
  static Reloj* _self;
  Uint32 inicia;
  Uint32 actual;
  
 public:
  static Reloj* instancia();

  void actualizar();
  double escala();
};

#endif
