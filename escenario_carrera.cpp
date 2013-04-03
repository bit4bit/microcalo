#include <iostream>
#include "compositor.h"
#include "escenario_carrera.h"

#define DATA_DIR "./data"

EscenarioCarrera::EscenarioCarrera() : Escenario(1) {
  
  fondo = Compositor::obRecurso()->cargarImagen(DATA_DIR "/map1.png");
  vehiculo = new Vehiculo(2);
  Compositor::obCamara()->ancho = 640; //@todo debe ser de la pantalla
  Compositor::obCamara()->alto = 480;
  std::cerr << "Creado escenario carrera" << std::endl;
}

EscenarioCarrera::~EscenarioCarrera() {
  delete vehiculo;
}

void EscenarioCarrera::actualizar() {
  Cosa *cv = vehiculo;
  vehiculo->actualizar();
  Compositor::obCamara()->seguir(cv);
}

void EscenarioCarrera::dibujar() {
  SDL_Rect sr;
  sr = Compositor::obCamara()->obRect();
  Compositor::obVideo()->blit(fondo, &sr, NULL);
  vehiculo->dibujar();
}
