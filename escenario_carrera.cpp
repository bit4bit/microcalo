#include <iostream>
#include <cmath>
#include <string>
#include <map>
#include "compositor.h"
#include "escenario_carrera.h"
#include "objeto.h"
#include "punto_paso.h"
#include "control_teclado.h"
#include "control_mando.h"
#include "vehiculo.h"
#include <SDL/sge.h>


#include "util.h"

#define DATA_DIR "./data"

/**
 *Carga el escenario desde un script(guile)
 */
EscenarioCarrera* EscenarioCarrera::cargarDesdeScript(std::string ruta) {
  return NULL;
}


EscenarioCarrera::EscenarioCarrera(const char *archivo_tmx) : Escenario(ID_ESCENARIO_CARRERA) {
  tmxRender = new TmxRender();
  tmxRender->CargarDesdeArchivo(archivo_tmx);

  //se crea mapa de colision con bloques para facilitar
  //la colision en el escenario
  int bloques_mapa[255][255];
  for(int i=0; i < tmxRender->obMap()->GetNumLayers(); i++) {
    const Tmx::Layer *layer = tmxRender->obMap()->GetLayer(i);
    if(layer->GetName() != "colision") continue;
    for(int y = 0; y < layer->GetHeight(); ++y) {
      for(int x = 0; x < layer->GetWidth(); ++x) {
	int CurTile = layer->GetTileId(x,y);
	if(CurTile == 0) continue;
	const Tmx::Tileset *tileset = tmxRender->obMap()->GetTileset(layer->GetTileTilesetIndex(x,y));
	if(!tileset) continue;
	const Tmx::Tile* tile = tileset->GetTile(CurTile);
	if(!tile) continue;
	if(tile->GetProperties().GetLiteralProperty("tipo") == "obstaculo")
	  bloques_mapa[x][y] = 1;
      }
    }
    break;
  }
  Compositor::obColision()->asignarBloqueMapa(bloques_mapa, tmxRender->obColumnas(), tmxRender->obFilas());


  Vehiculo *vehiculo = NULL;
  
  vehiculo = new Vehiculo(2, Compositor::obGestorVehiculoTipo()->encontrar(std::string("rapido")), 330, 300, 0);
  vehiculo->asignarColisionCircular(vehiculo->obAncho()/2, vehiculo->obAncho()/2, vehiculo->obAncho()/2);
  vehiculo->depurar = true;
  vehiculo->asignarLimites(tmxRender->obAncho(), tmxRender->obAlto());
  Jugador *jg1 = new Jugador("jugador 1", new ControlTeclado(SDLK_w, SDLK_m, SDLK_a, SDLK_o), vehiculo);
  agregarJugador(jg1);

  /*
  vehiculo = new Vehiculo(2, 100,  300, 0);
  vehiculo->asignarColisionCircular(vehiculo->obXCentro(), vehiculo->obYCentro(), vehiculo->obAncho()/2);
  vehiculo->depurar = true;
  Jugador *jg = new Jugador("jugador 2", new ControlMando(0), vehiculo);
  agregarJugador(jg);
  */

  Compositor::obCamara()->ancho = Compositor::obVideo()->obAncho(); //@todo debe ser de la pantalla
  Compositor::obCamara()->alto = Compositor::obVideo()->obAlto();
  Compositor::obCamara()->asignarLimites(tmxRender->obAncho(), tmxRender->obAlto());
  /* Objeto *obj = Objeto::desdeImagen(DATA_DIR "/obj1.png",3, 700, 700);
  obj->asignarColisionCircular(obj->obAncho()/2, obj->obAncho()/2, obj->obAncho()/2);
  obj->depurar = true;
  objetos.push_back(obj);
  */
  puntos_de_paso.anidarPuntoPaso(1280, 200, 200, 50);
  /*puntos_de_paso.anidarPuntoPaso(1240, 200, 200, 50);
  puntos_de_paso.anidarPuntoPaso(1700, 400, 200, 50);
  puntos_de_paso.anidarPuntoPaso(950, 700, 200, 50);
  puntos_de_paso.anidarPuntoPaso(180, 680, 200, 50);
  puntos_de_paso.anidarPuntoPaso(180, 1280, 200, 50);
  puntos_de_paso.anidarPuntoPaso(310, 1680, 200, 50);
  puntos_de_paso.anidarPuntoPaso(1580, 1850, 200, 50);*/
  Uint32 pi = 0;
  PuntoPaso* pp = NULL;
  
  //depurar
  /*for( pp = puntos_de_paso.primerPuntoPaso(); pi < puntos_de_paso.tamano(); ++pi) {
    pp = puntos_de_paso.puntoPasoA(pi);
    objetos.push_back(pp->obObjeto());
    }
  */
  std::cerr << "Creado escenario carrera" << std::endl;
}

EscenarioCarrera::~EscenarioCarrera() {
  if(tmxRender)
    delete tmxRender;

  for(std::vector<Objeto*>::iterator it = objetos.begin(); it != objetos.end(); ++it){
    if((*it)->obData() != NULL)
      delete (*it)->obData();
    
    delete (*it);
  }

  for(std::vector<Jugador*>::iterator it = jugadores.begin(); it != jugadores.end(); ++it) {
    delete (*it)->obControlTipo();
    delete (*it)->obVehiculo();
    delete (*it);
  }
}

void EscenarioCarrera::actualizar() {
  Objeto camara(99);
  int xMin, xMax, yMin, yMax;
  Vehiculo *vehiculo = NULL;

  //desplazamiento de la camar en base a los jugadores
  xMin = xMax = yMin = yMax = 0;


  for(std::vector<Jugador*>::iterator it = jugadores.begin(); it != jugadores.end(); ++it) {
    (*it)->actualizar(objetos);
    //cuando toca limites de pantalla o camara
    if(Compositor::obColision()->limitePantalla((*it)->obVehiculo()))
      std::cout << "colision con limite de pantalla:" << (*it)->nombre << std::endl;
    vehiculo = (*it)->obVehiculo();
    if(vehiculo->obX() < xMin || xMin == 0)
      xMin = vehiculo->obX();
    if(vehiculo->obX() > xMax || xMax == 0)
      xMax = vehiculo->obX();
    if(vehiculo->obY() < yMin || yMin == 0)
      yMin = vehiculo->obY();
    if(vehiculo->obY() > yMax || yMax == 0)
      yMax = vehiculo->obY();


    //lleva continudad de puntos
    Objeto *cv = static_cast<Objeto*>(vehiculo);
    //devuelve el vehiculo al punto de paso que seguia
    //si se salta alguno
    if(!puntos_de_paso.continuadoPuntoPasoA(cv)) {
      std::cout << "hey tramposx..." << std::endl;
      PuntoPaso *pp = puntos_de_paso.obPuntoPasoActual(cv);
      cv->moverXY(pp->obX(), pp->obY());
    }
    PuntoPaso *ptf = puntos_de_paso.puntoPasoA(cv);
    PuntoPaso *ptff =  puntos_de_paso.ultimoPuntoPaso();
    /*if( ptf && ptff && ptf  == ptff)
      std::cout << "bien termino correctamente.." << std::endl;*/

    //@todo esto es demasiado lento
    //ya que hay objetos que son muro
    //y por la cantidad jala mucho
    //if(Compositor::obColision()->entreObjetosCircular(vehiculo, objetos)) {
    //  vehiculo->choqueRetroceder();
    //}
  }


  //propuesta de movimiento de la camara:
  //medir distancia entre los 2 vehiculos y ubicar la camara
  //en el centro de esta distancia..para mas vehiculos
  //tomo sus posiciones minimas y maximas y calculo medios
  camara.moverXY(xMin + abs(xMin - xMax)/2, abs(yMin - yMax)/2 + yMax);
  //Compositor::obCamara()->seguir(xMin + abs(xMin - xMax)/2, abs(yMin - yMax)/2 + yMax);
  Compositor::obCamara()->seguir(&camara);

  /*for(std::vector<Objeto*>::iterator it = objetos.begin(); it != objetos.end(); ++it){
    if(Compositor::obColision()->entreObjetos(static_cast<Objeto *>(vehiculo), (*it)))
      {
	//colision
      }
    else
    (*it)->actualizar();
    }*/
  
  /*
  if(Compositor::obColision()->entreObjetosPorMapa(vehiculos.at(0), fondo)) {
    while(Compositor::obColision()->entreObjetosPorMapa(vehiculos.at(0), fondo)) {
      vehiculos.at(0)->choqueRetroceder();
    }
    }*/
}

void EscenarioCarrera::dibujar() {
  SDL_Rect sr;
  sr = Compositor::obCamara()->obRect();

  //Compositor::obVideo()->blit(fondo, &sr, NULL);
  // tmxRender->blit("fondo", &sr, Compositor::obVideo()->obSurface(), NULL);
  tmxRender->blit("fondo", &sr, Compositor::obVideo()->obSurface(), NULL, SDL_ALPHA_OPAQUE);
  tmxRender->blit("objetos", &sr, Compositor::obVideo()->obSurface(), NULL, SDL_ALPHA_OPAQUE);

  for(std::vector<Objeto*>::iterator it = objetos.begin(); it != objetos.end(); ++it){
    (*it)->dibujar();
  }

  for(std::vector<Jugador*>::iterator it = jugadores.begin(); it != jugadores.end(); ++it) {
    (*it)->dibujar();
  }

  tmxRender->blit("techo", &sr, Compositor::obVideo()->obSurface(), NULL, 125);

}


void EscenarioCarrera::agregarJugador(Jugador *jg)
{
  jugadores.push_back(jg);
}
