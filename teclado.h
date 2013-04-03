#ifndef TECLADO_H
#define TECLADO_H

#include <SDL/SDL.h>

class Teclado
{
 protected:
  Teclado();

 private:
  static Teclado* _self;
  Uint8 *teclas;

 public:
  static Teclado* instancia();

  void actualizar(Uint8 *_nteclas);
  bool presionado(Uint8 tecla);
  void presionar(Uint8 tecla);
  void soltar(Uint8 tecla);
};

#endif
