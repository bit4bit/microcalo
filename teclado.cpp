#include "teclado.h"

Teclado* Teclado::_self = 0;

Teclado::Teclado() {
}

Teclado* Teclado::instancia() {
  if(_self == 0) {
    _self = new Teclado;
  }
  return _self;
}


void Teclado::actualizar(Uint8* nteclas) {
  teclas = nteclas;
}

bool Teclado::presionado(Uint8 tecla) {
  return teclas[tecla] ? true : false;
}

void Teclado::presionar(Uint8 tecla) {
  teclas[tecla] = 1;
}

void Teclado::soltar(Uint8 tecla) {
  teclas[tecla] = 0;
}
