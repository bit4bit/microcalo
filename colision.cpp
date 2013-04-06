#include "colision.h"

Colision* Colision::_self = 0;

Colision::Colision() {
}

Colision* Colision::instancia() {
  if(_self == 0) {
    _self = new Colision;
  }
  return _self;
}


bool Colision::entreObjetos(Objeto *obja, Objeto *objb){
  if(
       (obja->obX() >= objb->obX() && obja->obX() <= objb->obX() + objb->obAncho())
       &&
       (obja->obX() + obja->obAncho() >= objb->obX() && obja->obX() + obja->obAncho() <= objb->obX() + objb->obAncho())
       &&
       (obja->obY() >= objb->obY() && obja->obY() <= objb->obY() + objb->obAlto())
       &&
       (obja->obY() + obja->obAlto() >= objb->obY() && obja->obY() + obja->obAlto() <= objb->obY() + objb->obAlto())
       )
      {
	return true;
      }
  return false;
}
