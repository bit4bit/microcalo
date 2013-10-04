#include "configuracion.h"
#include <iostream>
#include <cassert>
#include <mrubybind.h>

Configuracion *Configuracion::_self = 0;

Configuracion::Configuracion() {
}

Configuracion *Configuracion::instancia() {
  if(_self == 0) {
    _self = new Configuracion;
  }
  return _self;
}

void Configuracion::asignarLiteral(std::string n, std::string v)
{
  confLiteral[n] = v;
}

void Configuracion::asignarEntero(std::string n, int v)
{
  confEntero[n] = v;
}

void Configuracion::asignarFlotante(std::string n, float v)
{
  confFlotante[n] = v;
}

const char *Configuracion::obtenerLiteral(std::string n)
{
  assert(confLiteral.count(n) > 0);
  return confLiteral[n].c_str();;
}

int Configuracion::obtenerEntero(std::string n)
{
  assert(confEntero.count(n) > 0);
  return confEntero[n];
}

float Configuracion::obtenerFlotante(std::string n)
{
  assert(confFlotante.count(n) > 0);
  return confFlotante[n];
}

Configuracion *configuracion_initialize() {
  return Configuracion::instancia();
}


void Configuracion::bindingScript(mrb_state *mrb) {
  mrubybind::MrubyBind b(mrb);
  b.bind_class("Configuracion", configuracion_initialize);
  b.bind_instance_method("Configuracion", "asignarLiteral", &Configuracion::asignarLiteral);
  b.bind_instance_method("Configuracion", "asignarEntero", &Configuracion::asignarEntero);
  b.bind_instance_method("Configuracion", "asignarFlotante", &Configuracion::asignarFlotante);
  b.bind_instance_method("Configuracion", "obtenerLiteral", &Configuracion::obtenerLiteral);
  b.bind_instance_method("Configuracion", "obtenerEntero", &Configuracion::obtenerEntero);
  b.bind_instance_method("Configuracion", "obtenerFlotante", &Configuracion::obtenerFlotante);
}
