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
}
