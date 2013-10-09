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
static EscenarioGuion* escenario_guion_new(std::string nombre) {
  EscenarioGuion* e = new EscenarioGuion();
  e->asignarNombre(nombre);
  e->comoObjetoRuby();
  return e;
}

void EscenarioGuion::bindingScript(mrb_state *mrb) {
  //RClass* c_escenario_guion = mrb_define_class(mrb, "EscenarioGuion", mrb->object_class);
  // MRB_SET_INSTANCE_TT(c_escenario_guion, MRB_TT_DATA);
  // mrb_define_method(mrb, c_escenario_guion, "initialize", escenario_guion_new, MRB_ARGS_REQ(1));
  // mrb_define_method(mrb, c_escenario_guion, "agregarComando", escenario_guion_agregar_comando, MRB_ARGS_REQ(2));
  mrubybind::MrubyBind b(mrb);
  b.bind_class("EscenarioGuion", escenario_guion_new);
  b.bind_instance_method("EscenarioGuion", "agregarComando", &EscenarioGuion::agregarComandoS);
  b.bind_instance_method("EscenarioGuion", "obtenerNombre", &EscenarioGuion::obNombre);
  b.bind_instance_method("EscenarioGuion", "asignarNombre", &EscenarioGuion::asignarNombre);
}
