#include <iostream>
#include "compositor.h"
#include "escenario_carrera.h"
#include "objeto.h"

#define DATA_DIR "./data"

EscenarioCarrera::EscenarioCarrera() : Escenario(1) {
  
  fondo = Compositor::obRecurso()->cargarImagen(DATA_DIR "/map1.png");
  vehiculo = new Vehiculo(2);
  Compositor::obCamara()->ancho = Compositor::obVideo()->obAncho(); //@todo debe ser de la pantalla
  Compositor::obCamara()->alto = Compositor::obVideo()->obAlto();
  objetos.push_back(Objeto::desdeImagen(DATA_DIR "/obj1.png",3, 700, 700));

  std::cerr << "Creado escenario carrera" << std::endl;
}

EscenarioCarrera::~EscenarioCarrera() {
  for(std::vector<Objeto*>::iterator it = objetos.begin(); it != objetos.end(); ++it){
    delete (*it);
  }
  delete vehiculo;
}

void EscenarioCarrera::actualizar() {
  Objeto *cv = vehiculo;
  vehiculo->actualizar();
  Compositor::obCamara()->seguir(cv);

  for(std::vector<Objeto*>::iterator it = objetos.begin(); it != objetos.end(); ++it){
    if(Compositor::obColision()->entreObjetos((Objeto *)vehiculo, (*it)))
      {
	std::cout << "Colisiando..." << std::endl;
      }
    else
      std::cout << "nada.." << std::endl;
    (*it)->actualizar();
  }
}

void EscenarioCarrera::dibujar() {
  SDL_Rect sr;
  sr = Compositor::obCamara()->obRect();
  Compositor::obVideo()->blit(fondo, &sr, NULL);
  vehiculo->dibujar();

  for(std::vector<Objeto*>::iterator it = objetos.begin(); it != objetos.end(); ++it){
    (*it)->dibujar();
  }
}
