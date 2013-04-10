#include <iostream>
#include <cmath>
#include "compositor.h"
#include "escenario_carrera.h"
#include "objeto.h"
#include "punto_paso.h"
#include "control_teclado.h"
#include "control_mando.h"

#define DATA_DIR "./data"

EscenarioCarrera::EscenarioCarrera() : Escenario(1) {
  
  fondo = Compositor::obRecurso()->cargarImagen(DATA_DIR "/map1.png");
  //vehiculo = new Vehiculo(2);
  //Jugador *jg = new Jugador("1", new ControlTeclado(SDLK_t, SDLK_n, SDLK_a, SDLK_o), vehiculo);
  //agregarJugador(jg);
  vehiculo = new Vehiculo(2, 100, 200, 45);
  Jugador *jg = new Jugador("2", new ControlMando(0), vehiculo);
  agregarJugador(jg);

  Compositor::obCamara()->ancho = Compositor::obVideo()->obAncho(); //@todo debe ser de la pantalla
  Compositor::obCamara()->alto = Compositor::obVideo()->obAlto();
  Compositor::obCamara()->asignarLimites(fondo->w, fondo->h);
  objetos.push_back(Objeto::desdeImagen(DATA_DIR "/obj1.png",3, 700, 700));

  puntos_de_paso.anidarPuntoPaso(180, 200, 200, 50);
  puntos_de_paso.anidarPuntoPaso(1240, 200, 200, 50);
  puntos_de_paso.anidarPuntoPaso(1700, 400, 200, 50);
  puntos_de_paso.anidarPuntoPaso(950, 700, 200, 50);
  puntos_de_paso.anidarPuntoPaso(180, 680, 200, 50);
  puntos_de_paso.anidarPuntoPaso(180, 1280, 200, 50);
  puntos_de_paso.anidarPuntoPaso(310, 1680, 200, 50);
  puntos_de_paso.anidarPuntoPaso(1580, 1850, 200, 50);
  Uint32 pi = 0;
  PuntoPaso* pp = NULL;
  
  //depurar
  for( pp = puntos_de_paso.primerPuntoPaso(); pi < puntos_de_paso.tamano(); ++pi) {
    pp = puntos_de_paso.puntoPasoA(pi);
    objetos.push_back(pp->obObjeto());
    }

  std::cerr << "Creado escenario carrera" << std::endl;
}

EscenarioCarrera::~EscenarioCarrera() {
  for(std::vector<Objeto*>::iterator it = objetos.begin(); it != objetos.end(); ++it){
    if((*it)->obData() != NULL)
      delete (*it)->obData();

    delete (*it);
  }


  for(std::vector<Vehiculo*>::iterator it = vehiculos.begin(); it != vehiculos.end(); ++it) {
    delete (*it);
  }

  for(std::vector<Jugador*>::iterator it = jugadores.begin(); it != jugadores.end(); ++it) {
    delete (*it)->obControlTipo();
    delete (*it);
  }
}

void EscenarioCarrera::actualizar() {
  Objeto camara(99);
  int xMin, xMax, yMin, yMax;

  xMin = xMax = yMin = yMax = 0;
  for(std::vector<Jugador*>::iterator it = jugadores.begin(); it != jugadores.end(); ++it) {
    (*it)->actualizar();
    if(Compositor::obColision()->limitePantalla((*it)->obVehiculo()))
      std::cout << "colision con limite de pantalla:" << (*it)->nombre << std::endl;
  }

  for(std::vector<Vehiculo*>::iterator it = vehiculos.begin(); it != vehiculos.end(); ++it) {
    (*it)->actualizar();
    if((*it)->obX() < xMin || xMin == 0)
      xMin = (*it)->obX();
    if((*it)->obX() > xMax || xMax == 0)
      xMax = (*it)->obX();
    if((*it)->obY() < yMin || yMin == 0)
      yMin = (*it)->obY();
    if((*it)->obY() > yMax || yMax == 0)
      yMax = (*it)->obY();

    //lleva continudad de puntos
    Objeto *cv = static_cast<Objeto*>(*it);
    //devuelve el vehiculo al punto de paso que seguia
    //si se salta alguno
    if(!puntos_de_paso.continuadoPuntoPasoA(cv)) {
      std::cout << "hey tramposx..." << std::endl;
      PuntoPaso *pp = puntos_de_paso.obPuntoPasoActual(cv);
      cv->moverXY(pp->obX(), pp->obY());
    }
    PuntoPaso *ptf = puntos_de_paso.puntoPasoA(cv);
    PuntoPaso *ptff =  puntos_de_paso.ultimoPuntoPaso();
    if( ptf && ptff && ptf  == ptff)
      std::cout << "bien termino correctamente.." << std::endl;
  }
  //propuesta de movimiento de la camara:
  //medir distancia entre los 2 vehiculos y ubicar la camara
  //en el centro de esta distancia..para mas vehiculos
  //tomo sus posiciones minimas y maximas y calculo medios
  camara.moverXY(xMin + abs(xMin - xMax)/2, abs(yMin - yMax)/2 + yMax);
  Compositor::obCamara()->seguir(vehiculos.at(0));

  /*for(std::vector<Objeto*>::iterator it = objetos.begin(); it != objetos.end(); ++it){
    if(Compositor::obColision()->entreObjetos(static_cast<Objeto *>(vehiculo), (*it)))
      {
	//colision
      }
    else
    (*it)->actualizar();
    }*/
  

  
  
}

void EscenarioCarrera::dibujar() {
  SDL_Rect sr;
  sr = Compositor::obCamara()->obRect();
  Compositor::obVideo()->blit(fondo, &sr, NULL);

  
  for(std::vector<Objeto*>::iterator it = objetos.begin(); it != objetos.end(); ++it){
    (*it)->dibujar();
  }

  for(std::vector<Vehiculo*>::iterator it = vehiculos.begin(); it != vehiculos.end(); ++it) {
    (*it)->dibujar();
  }

}


void EscenarioCarrera::agregarJugador(Jugador *jg)
{
  jugadores.push_back(jg);
  vehiculos.push_back(jg->obVehiculo());
}
