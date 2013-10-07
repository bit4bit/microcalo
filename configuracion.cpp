#include "configuracion.h"
#include <iostream>
#include <cassert>
#include <mrubybind.h>
#include "carray.h"
#include "carray.cpp"
Configuracion *Configuracion::_self = 0;

Configuracion::Configuracion() {
}

Configuracion::~Configuracion() {
  for(iter_confArreglo = confArreglo.begin(); iter_confArreglo != confArreglo.end(); ++iter_confArreglo) {
    //delete (*iter_confArreglo);
  }
}

Configuracion *Configuracion::instancia() {
  if(_self == 0) {
    _self = new Configuracion;
  }
  return _self;
}

void Configuracion::cerrar() {
  delete _self;
  _self = 0;
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

void Configuracion::asignarArregloCadena(std::string n, std::string v) {
  if(!confArreglo.count(n)){
    confArreglo[n] = new CArrayString();
  }

  confArreglo[n]->push_back(v);
}

std::string Configuracion::obtenerLiteral(std::string n)
{
  assert(confLiteral.count(n) > 0);
  return confLiteral[n];
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
CArrayString* Configuracion::obtenerArregloCadena(std::string n) {
  if(confArreglo.count(n)){
    return confArreglo[n];
  }
  return NULL;
}

/**
 *Retorna el arreglo en cadena texto donde los valores son separados por ,
 *y en util.rb se hace la conversion de texto a Array.
 */
std::string Configuracion::obtenerArregloCadenaR(std::string n) {
  
  if(confArreglo.count(n)){
    std::string res;
    CArrayString* ar = confArreglo[n];
    bool primero = false;
    for(CArrayString::iterator iter = ar->begin(); iter != ar->end(); ++iter) {
      if(primero) {
	res.append(",");
      }
      res.append((*iter));
      primero = true;
    }
    return res;
  }
  return std::string("");
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
  b.bind_instance_method("Configuracion", "asignarArregloCadena", &Configuracion::asignarArregloCadena);
  b.bind_instance_method("Configuracion", "obtenerArregloCadena", &Configuracion::obtenerArregloCadenaR);
  b.bind_instance_method("Configuracion", "obtenerLiteral", &Configuracion::obtenerLiteral);
  b.bind_instance_method("Configuracion", "obtenerEntero", &Configuracion::obtenerEntero);
  b.bind_instance_method("Configuracion", "obtenerFlotante", &Configuracion::obtenerFlotante);

}
