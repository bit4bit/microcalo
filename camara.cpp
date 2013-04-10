#include "cspa.h"
#include "camara.h"
#include <iostream>

Camara* Camara::_self = 0;

Camara::Camara() {
  x = y = ancho = alto = 0;
  lx = ly = -1;
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

  si(lx && ly) {
    si(x > lx - ancho) x = lx - ancho - 1;
    si(y > ly - alto) y = ly - alto - 1;
  }
}

void Camara::seguir(Objeto *obj) {
  x = obj->obX() - ancho/2;
  y = obj->obY() - alto/2;

  si(x < 0) x = 0;
  si(y < 0) y = 0;

  si(lx >0 && ly > 0) {
    si(x > lx - ancho) x = lx - ancho - 1;
    si(y > ly - alto) y = ly - alto - 1;
  }
}

SDL_Rect Camara::obRect() {
  SDL_Rect r;
  r.x = x; r.y = y; r.w = ancho; r.h = alto;

  return r;
}

void Camara::asignarLimites(Uint32 _x, Uint32 _y) {
  lx = _x; ly = _y;
}
