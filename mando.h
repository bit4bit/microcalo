#ifndef MANDO_H
#define MANDO_H

#include <SDL/SDL.h>

class Mando
{
 protected:
  Mando();
 private:
  static Mando* _self;
 public:
  static Mando* instancia();
  void actualizar();
};

#endif
