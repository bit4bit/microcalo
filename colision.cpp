#include "cspa.h"
#include "colision.h"

Colision* Colision::_self = 0;

Colision::Colision() {
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
