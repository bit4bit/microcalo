#ifndef COLISION_H
#define COLISION_H

#include <SDL/sge.h>
#include <SDL/SDL.h>
#include "objeto.h"
#include <map>
#include <vector>
#include "colision_util.h"

#define MAX_MAPA_COLISION 1001

class Colision
{
 protected:
  Colision();
  ~Colision();
  
 private:
  static Colision* _self;
  std::map<Objeto*, sge_cdata*> colision_map; //colision por pixel usando SGE
  unsigned char bloques_mapa[MAX_MAPA_COLISION][MAX_MAPA_COLISION];
 public:
  static Colision* instancia();
  
  bool entreObjetos(Objeto *obja, Objeto *objb);
  bool entreObjetos(Objeto *obja, std::vector<Objeto*>& objs);
  bool entreObjetos(Objeto *obja, int nx, int ny, std::vector<Objeto*>& objs);
  bool entreObjetosPorMapa(Objeto *obja, Objeto *objb);
  bool entreObjetosCircular(Objeto *obja, Objeto *objb);
  bool entreObjetosCircular(Objeto *obja, std::vector<Objeto*>& objs);
  bool limitePantalla(Objeto *obj);
  void crearMapaColision(Objeto *obj);
  void crearMapaColisionImagen(Objeto *obj, SDL_Surface *s);

  void asignarBloqueMapa(unsigned char [MAX_MAPA_COLISION][MAX_MAPA_COLISION], int, int);
  bool conBloque(Objeto *obja); 
  bool conBloque(Objeto *obja, int nx, int ny); 

  //para depurar..ver en pantalla
  void dibujar();

  
};

#endif
