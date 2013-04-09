#include "cspa.h"
#include "camara.h"

Camara* Camara::_self = 0;

Camara::Camara() {
  x = y = ancho = alto = 0;
}

Camara* Camara::instancia() {
  si(_self == 0) {
    _self = new Camara();
  }
  retorna _self;
}

void Camara::seguir(Uint32 sx, Uint32 sy) {
  
  x = sx - ancho/2;
  y = sy - alto/2;
  si(x < 0) x = 0;
  si(y < 0) y = 0;
}

void Camara::seguir(Objeto *obj) {
  x = obj->obX() - ancho/2;
  y = obj->obY() - alto/2;
  if(x < 0) x = 0;
  if(y < 0) y = 0;
}

SDL_Rect Camara::obRect() {
  SDL_Rect r;
  r.x = x; r.y = y; r.w = ancho; r.h = alto;
  return r;
}
