#ifndef ESCENARIO_INTRO_H
#define ESCENARIO_INTRO_H

#include <SDL/SDL.h>
#include <string>
#include <list>
#include <vector>
#include <queue>
#include <libguile.h>
#include "escenario.h"

class EscenarioIntroComando
{
 public:
  EscenarioIntroComando(std::string tipo, std::string data);
  
  std::string tipo;
  std::string data;
};

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

  void agregarComando(EscenarioIntroComando *comando);
 private:
  std::queue<EscenarioIntroComando*> comandos;
};

#endif