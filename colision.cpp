#include "cspa.h"
#include "colision.h"
#include <cassert>
#include <iostream>
#include <cmath>

Colision* Colision::_self = 0;

Colision::Colision() {
  memset(bloques_mapa, 0, sizeof(bloques_mapa));
  bloque_tamano = 0;
}

Colision::~Colision() {
  std::cout << "Destruyendo compositor::colision" << std::endl;
  for(std::map<Objeto*,sge_cdata*>::iterator iter = colision_map.begin(); iter != colision_map.end(); ++iter) {
    sge_destroy_cmap(iter->second);
  }
}

Colision* Colision::instancia() {
  si(_self == 0) {
    _self = new Colision;
  }
  retorna _self;
}

bool Colision::entreObjetosCircular(Objeto *obja, Objeto *objb)
{
  double distAB = 0;
  //no compruebo..ya que se supone que si se llama
  //es por que ya esta la info circular para detectar colision

  cada(std::vector<Circular>::iterator iter = obja->colision_circular.begin(); iter != obja->colision_circular.end(); ++iter) 
    {
      cada(std::vector<Circular>::iterator iterB = objb->colision_circular.begin(); iterB != objb->colision_circular.end(); ++iterB) 
	{
	  distAB = sqrt(
			pow((*iter).x - (*iterB).x, 2) +
			pow((*iter).y - (*iterB).y, 2)
			);
	  si(distAB <= (*iter).radio + (*iterB).radio)
	    retorna true;
	}
    }
  retorna false;
}

/**
 *Verifica si hay colisicion de un Objeto con algun objeto
 *desde una nueva posicion.
 */
bool Colision::entreObjetos(Objeto *obja, int nx, int ny, std::vector<Objeto*>& objs) {	
  double distAB = 0;
  cada(std::vector<Objeto*>::const_iterator itObjs = objs.begin(); itObjs != objs.end(); ++itObjs) {
    Objeto *objb = *itObjs;
    cada(std::vector<Circular>::iterator iter = obja->colision_circular.begin(); iter != obja->colision_circular.end(); ++iter) 
      {
	cada(std::vector<Circular>::iterator iterB = objb->colision_circular.begin(); iterB != objb->colision_circular.end(); ++iterB) 
	{
	  int xb = objb->obX();
	  int yb = objb->obY();
	  distAB = sqrt(
			pow((nx + (*iter).x) - (xb + (*iterB).x), 2) +
			pow((ny + (*iter).y) - (yb + (*iterB).y), 2)
			);
	  si(distAB <= (*iter).radio + (*iterB).radio)
	    retorna true;
	}
    }
  }
  return false;
}

bool Colision::entreObjetos(Objeto *obja, Objeto *objb){
  double distAB = sqrt(
		       pow(obja->obXCentro() - objb->obXCentro(), 2) +
		       pow(obja->obYCentro() - objb->obYCentro(), 2)
		       );
  si(distAB <=  obja->obAncho()/ 2 + objb->obAncho()/2)
    retorna true;
  retorna false;
}

bool Colision::entreObjetos(Objeto *obja, std::vector<Objeto*>& objs) {
  if(!obja->enPantalla()) retorna false;
  for(std::vector<Objeto*>::const_iterator it = objs.begin(); it != objs.end(); ++it) {
    if(entreObjetos(obja, (*it)))
      return true;
  }
  return false;

}


bool Colision::entreObjetosCircular(Objeto *obja, std::vector<Objeto*>& objs) {
  if(!obja->enPantalla()) retorna false;
  for(std::vector<Objeto*>::const_iterator it = objs.begin(); it != objs.end(); ++it) {
    if(entreObjetosCircular(obja, (*it)))
      return true;
  }
  return false;

}

bool Colision::limitePantalla(Objeto *obj) {
  return !obj->enPantalla();
}

void Colision::crearMapaColision(Objeto *obj) {
  colision_map[obj] = sge_make_cmap(obj->obSurface());
}


void Colision::crearMapaColisionImagen(Objeto *obj, SDL_Surface *s)
{
  colision_map[obj] = sge_make_cmap(s);
  si(colision_map[obj] == NULL)
    std::cerr << "fallo crear mapa colision a superficie." << std::endl;
  aunque
    std::cerr << "creado mapa de colision a superficie." << std::endl;
}

bool Colision::entreObjetosPorMapa(Objeto *obja, Objeto *objb)
{
  si(!colision_map[obja]) retorna false; 
  si(!colision_map[objb]) retorna false;

  bool v = sge_cmcheck(colision_map[obja], obja->obXCentro(), obja->obYCentro(), colision_map[objb], objb->obX(), objb->obY()) == 1 ? true : false;
  std::cout << "colmap.x:" << sge_get_cx() << " colmap.y: " << sge_get_cy() << std::endl;
  retorna v;
}


void Colision::dibujar()
{
}


void Colision::asignarBloqueMapa(unsigned char col[MAX_MAPA_COLISION][MAX_MAPA_COLISION], int ancho, int alto, int btamano)
{
  assert(ancho < MAX_MAPA_COLISION && alto < MAX_MAPA_COLISION);
  for(int i=0; i < ancho; i++)
    for(int j=0; j < alto; j++)
      bloques_mapa[i][j] = col[i][j];
  bloque_tamano = btamano;
}

bool Colision::conBloque(Objeto *obja) 
{
  int x = obja->obX() / bloque_tamano;
  int y = obja->obY() / bloque_tamano;
  if(bloques_mapa[x][y])
    return true;
  return false;
}

bool Colision::conBloque(Objeto *obja, int nx, int ny) 
{
  int x = nx / bloque_tamano;
  int y = ny / bloque_tamano;
  if(bloques_mapa[x][y])
    return true;
  return false;
}
