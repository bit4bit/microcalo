#include "gestor_escenario.h"
#include "escenario_guion.h"
#include <iostream>
#include <typeinfo>

#include "bindingscript.h"
#include <mrubybind.h>

GestorEscenario* GestorEscenario::_self = 0;

GestorEscenario::GestorEscenario() {
  _actual = NULL;
}

GestorEscenario::~GestorEscenario() {
  for(iter_escenarios = escenarios.begin(); iter_escenarios != escenarios.end(); ++iter_escenarios) {
    if(iter_escenarios->second && iter_escenarios->second->esObjetoRuby() == false){
      delete iter_escenarios->second;
    }

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


void GestorEscenario::agregar( Escenario* esc) {
  if(escenarios.count(esc->obNombre()))
    delete escenarios[esc->obNombre()];
  escenarios[esc->obNombre()] = esc;
}

void GestorEscenario::activar(std::string nombre) {
  if(escenarios.count(nombre))
    _actual = escenarios[nombre];
}

Escenario* GestorEscenario::actual() {
  return _actual;
}


//BINDING MRUBY

static void gestor_escenario_free(mrb_state *mrb, void* data) {
}
static struct mrb_data_type gestor_escenario_type  = {"GestorEscenario", gestor_escenario_free};


static mrb_value gestor_escenario_new(mrb_state *mrb, mrb_value self) {
  DATA_TYPE(self) = &gestor_escenario_type;
  DATA_PTR(self) = GestorEscenario::instancia();
  return self;
}


static mrb_value gestor_escenario_agregar(mrb_state *mrb, mrb_value self) {
  std::cout << "agregando escenario........" << std::endl;    
  mrb_value obj;

  GestorEscenario* ge = DATA_GET_PTR(mrb, self, &gestor_escenario_type, GestorEscenario);
  mrb_get_args(mrb, "o", &obj);

  Escenario* e = static_cast<Escenario*>(DATA_PTR(obj));
  e->comoObjetoRuby();

  ge->agregar(e);
  return self;
}




void GestorEscenario::bindingScript(mrb_state *mrb) {
  
  //se crea clase heradada de Object
  RClass *c_gestor_escenario =  mrb_define_class(mrb, "GestorEscenario", mrb->object_class);
  MRB_SET_INSTANCE_TT(c_gestor_escenario, MRB_TT_DATA);
  mrb_define_method(mrb, c_gestor_escenario, "initialize", gestor_escenario_new, MRB_ARGS_NONE());
  mrb_define_method(mrb, c_gestor_escenario, "agregar", gestor_escenario_agregar, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, c_gestor_escenario, "<<", gestor_escenario_agregar, MRB_ARGS_REQ(1));
}
