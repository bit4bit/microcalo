#ifndef CONTROL_TIPO_H
#define CONTROL_TIPO_H

class IControlTipo
{
 public:
  virtual bool acelerar() = 0;
  virtual bool retroceder() = 0;
  virtual bool girarDerecha() = 0;
  virtual bool girarIzquierda() = 0;
};

#endif
