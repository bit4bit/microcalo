#include "cspa.h"
#include "escenario.h"

Escenario::Escenario(Uint32 _id) : Cosa(_id) {
  _nombre = "sinnombre";
  es_objeto_ruby = false;
}

Escenario::~Escenario() {
  //@todo llamar pariente?
}

void Escenario::agregar(Cosa* cosa){
  cosas.push_front(cosa);
}

void Escenario::remover(Cosa* cosa){
  cosas.remove(cosa);
}

void Escenario::actualizar() {
  cada(std::list<Cosa*>::iterator it = cosas.begin(); it != cosas.end(); ++it) {
    (*it)->dibujar();
  }
}

void Escenario::dibujar() {
  cada(std::list<Cosa*>::iterator it = cosas.begin(); it != cosas.end(); ++it) {
    (*it)->dibujar();
  }
}

void Escenario::asignarNombre(std::string nombre) {
  _nombre = nombre;
}

const std::string& Escenario::obNombre() {
  return _nombre;
}
