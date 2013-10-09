#ifndef GESTOR_ESCENA_H
#define GESTOR_ESCENA_H

#include "escenario.h"
#include <map>
#include <string>
#include <mruby.h>

/**
 *Maneja las escenas del video juego
 *tambien permite a las escenas pasarse entre si
 */
class GestorEscenario
{
 public:
  static void bindingScript(mrb_state*);
  static GestorEscenario* instancia();
  static void cerrar();
  
  void agregar(Escenario*);
  void activar(std::string);
  Escenario* actual();

 protected:
  GestorEscenario();
  ~GestorEscenario();

  
 private:
  Escenario* _actual;
  static GestorEscenario* _self;
  std::map<std::string, Escenario*> escenarios;
  std::map<std::string, Escenario*>::iterator iter_escenarios;
};

#endif
