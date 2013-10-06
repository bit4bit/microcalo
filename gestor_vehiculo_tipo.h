#ifndef GESTOR_VEHICULO_TIPO_H
#define GESTOR_VEHICULO_TIPO_H

#include <map>
#include <string>
#include "vehiculo_tipo.h"
#include <mruby.h>

class GestorVehiculoTipo
{
 private:
  static GestorVehiculoTipo* _self;

  std::map <std::string, VehiculoTipo*> vehiculos;
  std::map <std::string, VehiculoTipo*>::iterator iter_vehiculos;
 protected:
  GestorVehiculoTipo();
  ~GestorVehiculoTipo();

 public:
  static GestorVehiculoTipo* instancia();
  static void cerrar();

  VehiculoTipo* crear(std::string);
  VehiculoTipo* encontrar(std::string);
  void agregar(VehiculoTipo*);
};

#endif
