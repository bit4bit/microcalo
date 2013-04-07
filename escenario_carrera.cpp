#include <iostream>
#include "compositor.h"
#include "escenario_carrera.h"
#include "objeto.h"
#include "punto_paso.h"

#define DATA_DIR "./data"

EscenarioCarrera::EscenarioCarrera() : Escenario(1) {
  
  fondo = Compositor::obRecurso()->cargarImagen(DATA_DIR "/map1.png");
  vehiculo = new Vehiculo(2);
  Compositor::obCamara()->ancho = Compositor::obVideo()->obAncho(); //@todo debe ser de la pantalla
  Compositor::obCamara()->alto = Compositor::obVideo()->obAlto();
  objetos.push_back(Objeto::desdeImagen(DATA_DIR "/obj1.png",3, 700, 700));

  PuntoPaso *ptpaso = new PuntoPaso(300, 100, 200, 50);
  puntos_de_paso.push_back(ptpaso);
  objetos.push_back(ptpaso->obObjeto());
  std::cerr << "Creado escenario carrera" << std::endl;
}

EscenarioCarrera::~EscenarioCarrera() {
  for(std::vector<Objeto*>::iterator it = objetos.begin(); it != objetos.end(); ++it){
    if((*it)->obData() != NULL)
      delete (*it)->obData();

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
	//colision
      }
    else
    (*it)->actualizar();
  }

}

void EscenarioCarrera::dibujar() {
  SDL_Rect sr;
  sr = Compositor::obCamara()->obRect();
  Compositor::obVideo()->blit(fondo, &sr, NULL);


  for(std::vector<Objeto*>::iterator it = objetos.begin(); it != objetos.end(); ++it){
    (*it)->dibujar();
  }

  vehiculo->dibujar();
}
