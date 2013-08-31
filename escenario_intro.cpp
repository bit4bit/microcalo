#include <string>
#include <iostream>
#include <libguile.h>
#include <SDL/SDL_ttf.h>
#include <SDL/SDL_image.h>
#include <unistd.h>
#include "escenario_intro.h"
#include "compositor.h"

EscenarioIntroComando::EscenarioIntroComando(std::string _tipo,
					     std::string _data) {
  tipo = _tipo;
  data = _data;

}


EscenarioIntro::EscenarioIntro() : Escenario(ID_ESCENARIO_INTRO) {
  pausar = 0;
  pausar_cont = 0;
}

EscenarioIntro::~EscenarioIntro() {
}

void EscenarioIntro::dibujar() {
}

void EscenarioIntro::actualizar() {

  if(comandos.empty()) 
    return;

  EscenarioIntroComando *comando = comandos.front();
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

  comandos.pop();

}

void EscenarioIntro::agregarComando(EscenarioIntroComando *comando) {	
  comandos.push(comando);
}
