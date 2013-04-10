#ifndef COLISION_H
#define COLISION_H

#include "objeto.h"

class Colision
{
 protected:
  Colision();

 private:
  static Colision* _self;

 public:
  static Colision* instancia();
  
  bool entreObjetos(Objeto *obja, Objeto *objb);
  bool limitePantalla(Objeto *obj);
};

#endif
