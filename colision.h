#ifndef COLISION_H
#define COLISION_H

#include <SDL/sge.h>
#include <SDL/SDL.h>
#include "objeto.h"
#include <map>

class Colision
{
 protected:
  Colision();
  ~Colision();
  
 private:
  static Colision* _self;
  std::map<Objeto*, sge_cdata*> colision_map; //colision por pixel usando SGE

 public:
  static Colision* instancia();
  
  bool entreObjetos(Objeto *obja, Objeto *objb);
  bool limitePantalla(Objeto *obj);
  void crearMapaColision(Objeto *obj);
  void crearMapaColisionImagen(Objeto *obj, SDL_Surface *s);
  bool entreObjetosPorMapa(Objeto *obja, Objeto *objb);
};

#endif
