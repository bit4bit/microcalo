#include <string>
#include <iostream>
#include <libguile.h>
#include "escenario_intro.h"

EscenarioIntroComando::EscenarioIntroComando(std::string _tipo,
					     std::string _data) {
  tipo = _tipo;
  data = _data;
}


EscenarioIntro::EscenarioIntro() : Escenario(ID_ESCENARIO_INTRO) {
}

EscenarioIntro::~EscenarioIntro() {
}

void EscenarioIntro::dibujar() {
}

void EscenarioIntro::actualizar() {
  while(!comandos.empty()) {
    EscenarioIntroComando *comando = comandos.front();
    
    comandos.pop();
  }
}

void EscenarioIntro::agregarComando(EscenarioIntroComando *comando) {	
  comandos.push(comando);
}
