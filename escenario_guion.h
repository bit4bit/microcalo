#ifndef ESCENARIO_INTRO_H
#define ESCENARIO_INTRO_H

#include <SDL/SDL.h>
#include <string>
#include <list>
#include <vector>
#include <queue>
#include "escenario.h"
#include <mruby.h>
#include <mruby/data.h>


class EscenarioGuionComando
{
 public:
  EscenarioGuionComando(std::string tipo, std::string data);
  
  std::string tipo;
  std::string data;
};

/**
 *Escenario donde se muestra escenas de animacion al video juego
 *o bien de presentacion.
 *@todo musica y soundfx
 */
class EscenarioGuion : public Escenario
{
 public:
  static void bindingScript(mrb_state*);
  EscenarioGuion();
  virtual ~EscenarioGuion();
  virtual void actualizar();
  virtual void dibujar();

  void agregarComando(EscenarioGuionComando *comando);
  void agregarComandoS(std::string, std::string);
 private:
  std::queue<EscenarioGuionComando*> comandos;
  int pausar;
  int pausar_cont;
};

#endif
