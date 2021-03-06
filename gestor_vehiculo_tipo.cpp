#include "gestor_vehiculo_tipo.h"
#include "compositor.h"
#include <mruby.h>
#include <mruby/compile.h>
#include <mrubybind.h>

GestorVehiculoTipo* GestorVehiculoTipo::_self = 0;

GestorVehiculoTipo* GestorVehiculoTipo::instancia() {
  if(_self == 0)
    _self = new GestorVehiculoTipo();

  return _self;
}


void GestorVehiculoTipo::cerrar() {
  delete _self;
  _self = 0;
}

GestorVehiculoTipo::GestorVehiculoTipo() {
}

GestorVehiculoTipo::~GestorVehiculoTipo() {
  for(iter_vehiculos = vehiculos.begin(); iter_vehiculos != vehiculos.end(); iter_vehiculos++){
    if(iter_vehiculos->second){
      //@todo COMO LIMPIAR LOS OBJETOS COMPARTIDOS CON MRUBY
      //MRBUBY lo elimina??
      //delete iter_vehiculos->second;
    }
  }
}

VehiculoTipo* GestorVehiculoTipo::crear(std::string nombre) {
  VehiculoTipo* vt = new VehiculoTipo();
  vt->asignarNombre(nombre);
  return vehiculos[nombre] = vt;
}

VehiculoTipo* GestorVehiculoTipo::encontrar(std::string nombre) {
  if(!vehiculos.size()) {
    VehiculoTipo* vt = new VehiculoTipo();
    vt->asignarNombre("generico");
    vt->asignarAncho(32);
    vt->asignarAlto(32);
    vt->asignarMaxVel(12);
    vt->asignarMinVel(-5);
    vt->asignarDefAccel(0.5);
    vt->asignarDefRetro(-0.1);
    vt->asignarDefGiro(1);
    vt->asignarDefGiroFrenando(5);
    vt->asignarSVehiculo(Compositor::obRecurso()->cargarImagen("./data/carro.xpm"));
    vehiculos[vt->obNombre()] = vt;
    return vt;
  }

  if(vehiculos.count(nombre))
    return vehiculos[nombre];
    return vehiculos[std::string("generico")];
}
