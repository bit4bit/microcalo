#ifndef SCRIPT_H
#define SCRIPT_H

#include "escenario_intro.h"

extern "C" {
  void* iniciar_script(void *data);
  void script_cargar_escenario_intro(EscenarioIntro *escenario_intro);
}

#endif
