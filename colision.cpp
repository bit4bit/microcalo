#include "cspa.h"
#include "colision.h"
#include <cassert>
#include <iostream>
#include <cmath>

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
  //debo agregar que cuando no este en direccion del objeto de colision
  //no colisione
  double distAB = sqrt(
		       pow(obja->obX() - objb->obX(), 2) +
		       pow(obja->obY() - objb->obY(), 2)
		       );
  std::cout << "B.x:" << objb->obX() << "\tB.y:" << objb->obY() << std::endl;
  std::cout << "A.x:" << obja->obX() << "\tA.y:" << obja->obY() << std::endl;
  std::cout << "DistAB:" << distAB << std::endl;
  si(distAB <=  obja->obAncho()/ 2 + objb->obAncho()/2)
    return true;
  return false;
  //http://lazyfoo.net/SDL_tutorials/lesson17/index.php
  int leftA, leftB; int rightA, rightB; int topA, topB; int bottomA, bottomB;
  //Calculate the sides of rect A 
  leftA = obja->obX(); rightA = obja->obX()  + obja->obAncho(); 
  topA = obja->obY(); bottomA = obja->obY() + obja->obAlto(); 


  //Calculate the sides of rect B 
  leftB = objb->obX(); rightB = objb->obX() + objb->obAncho(); 
  topB = objb->obY(); bottomB = objb->obY() + objb->obAlto();

  std::cout << "objA.left:" << leftA << " objA.right:" << rightA << " objA.top:" << topA << " objA.bottom:" << bottomA << std::endl;
    std::cout << "objB.left:" << leftB << " objB.right:" << rightB << " objB.top:" << topB << " objB.bottom:" << bottomB << std::endl;
  //If any of the sides from A are outside of B 
  if( bottomA < topB ) { return false; } 
  if( topA > bottomB ) { return false; } 
  if( rightA < leftB ) { return false; } 
  if( leftA > rightB ) { return false; } 
  //If none of the sides from A are outside B return true;
  std::cout << "colision" << std::endl;
  retorna true;
}

bool Colision::entreObjetos(Objeto *obja, std::vector<Objeto*>& objs) {
  if(!obja->enPantalla()) retorna false;
  for(std::vector<Objeto*>::const_iterator it = objs.begin(); it != objs.end(); ++it) {
    if(entreObjetos(obja, (*it)))
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
