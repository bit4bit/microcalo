#include "cspa.h"
#include "colision.h"
#include <cassert>
#include <iostream>

Colision* Colision::_self = 0;

Colision::Colision() {
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


bool Colision::entreObjetos(Objeto *obja, Objeto *objb){
  si(
       (obja->obX() >= objb->obX() && obja->obX() <= objb->obX() + objb->obAncho())
       &&
       (obja->obX() + obja->obAncho() >= objb->obX() && obja->obX() + obja->obAncho() <= objb->obX() + objb->obAncho())
       &&
       (obja->obY() >= objb->obY() && obja->obY() <= objb->obY() + objb->obAlto())
       &&
       (obja->obY() + obja->obAlto() >= objb->obY() && obja->obY() + obja->obAlto() <= objb->obY() + objb->obAlto())
       )
      {
	retorna true;
      }
  retorna false;
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

  bool v = sge_cmcheck(colision_map[obja], obja->obX(), obja->obY(), colision_map[objb], objb->obX(), objb->obY()) == 1 ? true : false;
  std::cout << "colmap.x:" << sge_get_cx() << " colmap.y: " << sge_get_cy() << std::endl;
  retorna v;
}
