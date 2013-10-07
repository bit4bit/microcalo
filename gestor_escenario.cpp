#include "gestor_escenario.h"

GestorEscenario* GestorEscenario::_self = 0;

GestorEscenario::GestorEscenario() {
  _actual = NULL;
}

GestorEscenario::~GestorEscenario() {
  for(iter_escenarios = escenarios.begin(); iter_escenarios != escenarios.end(); ++iter_escenarios) {
    if(iter_escenarios->second)
      delete iter_escenarios->second;
  }
}

GestorEscenario* GestorEscenario::instancia() {
  if(_self == 0)
    _self = new GestorEscenario;
  return _self;
}

void GestorEscenario::cerrar() {
  if(_self) {
    delete _self;
    _self = 0;
  }
}


void GestorEscenario::agregar(std::string nombre, Escenario* esc) {
  if(escenarios.count(nombre))
    delete escenarios[nombre];
  escenarios[nombre] = esc;
}

void GestorEscenario::activar(std::string nombre) {
  if(escenarios.count(nombre))
    _actual = escenarios[nombre];
}

Escenario* GestorEscenario::actual() {
  return _actual;
}
