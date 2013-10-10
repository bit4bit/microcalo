#include "escenario_guion.h"
#include <string>
#include <iostream>
#include <libguile.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>
#include <unistd.h>

#include "compositor.h"
#include <mrubybind.h>
#include <mruby.h>
#include <mruby/value.h>
#include <mruby/compile.h>
#include <mruby/data.h>
#include <mruby/class.h>


EscenarioGuionComando::EscenarioGuionComando(std::string _tipo,
					     std::string _data) {
  tipo = _tipo;
  data = _data;

}


EscenarioGuion::EscenarioGuion() : Escenario(ID_ESCENARIO_INTRO) {
  pausar = 0;
  pausar_cont = 0;
}

EscenarioGuion::~EscenarioGuion() {
}

void EscenarioGuion::dibujar() {
}

/**
 *Comandos:
 * +pausa+ : +int+ pausa n segundos
 * +imagen+ : +string+ muestra imagen
 * +texto+ : +string+ muestra texto
 */
void EscenarioGuion::actualizar() {

  if(comandos.empty()) 
    return;

  EscenarioGuionComando *comando = comandos.front();
  if(comando->tipo == "pausa"){
    pausar_cont += Compositor::obReloj()->diff();
    if(pausar < 1){
      pausar = atoi(comando->data.c_str());
      return;
    }
    else
      {
	if(pausar_cont > 1000) {
	  pausar -= 1;
	  pausar_cont = 0;
	  if (pausar > 0)
	    return;
	}else{
	  return;
	}
      }

  }


  if(comando->tipo == "texto") {
    Compositor::obVideo()->clearScreenColor(0);
    SDL_Surface *stxt = Compositor::obTexto()->renderTextSolid(comando->data.c_str(), (SDL_Color){255,255,255,0});
    Compositor::obVideo()->blit(stxt, NULL, NULL);
  }
  if(comando->tipo == "imagen") {
    Compositor::obVideo()->clearScreenColor(0);
    //@todo verificar existencia de imagen
    SDL_Surface *img = IMG_Load(comando->data.c_str());
    Compositor::obVideo()->blit(img, NULL, NULL);
  }
  if(comando->tipo == "cambiar") {
    Compositor::obVideo()->clearScreenColor(0);
    Compositor::obGestorEscenario()->activar(comando->data);
  }
  comandos.pop();

}

void EscenarioGuion::agregarComando(EscenarioGuionComando *comando) {	
  comandos.push(comando);
}

void EscenarioGuion::agregarComandoS(std::string tipo, std::string data) {
  comandos.push(new EscenarioGuionComando(tipo, data));
}


//BINDING
DEF_RFUNC(escenario_guion_new) {
  mrb_value key;
  mrb_get_args(mrb, "S", &key);
  EscenarioGuion* ptr = new EscenarioGuion();
  DATA_TYPE(self) = &escenario_guion_type;
  DATA_PTR(self) = ptr;
  ptr->asignarNombre(mrb_str_to_cstr(mrb, key));
  mrb_gc_protect(mrb, self);
  return self;
}

DEF_RFUNC(escenario_guion_agregar_comando) {
  mrb_value tipo;
  mrb_value data;
  mrb_get_args(mrb, "SS", &tipo, &data);
  EscenarioGuion* ptr = static_cast<EscenarioGuion*>(DATA_PTR(self));
  char *ctipo = mrb_str_to_cstr(mrb, tipo);
  char *cdata = mrb_str_to_cstr(mrb, data);
  ptr->agregarComandoS(ctipo, cdata);
  return self;
}

void EscenarioGuion::bindingScript(mrb_state *mrb) {
  c_escenario_guion = mrb_define_class(mrb, "EscenarioGuion", mrb->object_class);
  MRB_SET_INSTANCE_TT(c_escenario_guion, MRB_TT_DATA);
  mrb_define_method(mrb, c_escenario_guion, "initialize", escenario_guion_new, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, c_escenario_guion, "agregarComando", escenario_guion_agregar_comando, MRB_ARGS_REQ(2));

}
