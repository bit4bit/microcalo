#ifndef ESCENARIO_INTRO_H
#define ESCENARIO_INTRO_H

#include <SDL/SDL.h>
#include <list>
#include "escenario.h"

/**
 *Escenario donde se muestra introduccion al video juego
 *o bien presentacion.
 */
class EscenarioIntro : public Escenario
{
 public:
  EscenarioIntro();
  virtual ~EscenarioIntro();
  virtual void actualizar();
  virtual void dibujar();

};

#endif
