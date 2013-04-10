#ifndef OBJETO_H
#define OBJETO_H

#include <SDL/SDL.h>
#include "cosa.h"


/**
 *El objeto representa
 *algo en el escenario con lo que se puede
 *colisionar, un taza, un balon, etc..
 */
class Objeto : public Cosa
{
 public:
  Objeto(Uint32 _id);
  Objeto(Uint32 _id, Uint32 x, Uint32 y);
  virtual ~Objeto();
  virtual void actualizar();
  virtual void dibujar();
  
  static Objeto* desdeImagen(const char *ruta, Uint32 _id, Uint32 x, Uint32 y);

  Uint32 obX() { return escenario_x; }
  Uint32 obY() { return escenario_y; }
  Uint32 obXCentro() { return escenario_x - ancho/2;}
  Uint32 obYCentro() { return escenario_y - alto/2;}
  Uint32 obXPantalla();
  Uint32 obYPantalla();
  Uint32 obAncho() { return ancho; }
  Uint32 obAlto() { return alto; }
  bool enPantalla();
  SDL_Surface *obSurface() { return s_objeto; }
  void *obData() { return data; }
  void asignarData(void *_data) { data = _data;}
  void asignarDPantallaX(Uint32 v) { dpantalla_x = v; }
  void asignarDPantallaY(Uint32 v) { dpantalla_y = v; }
  void asignarSurface(SDL_Surface *s) { s_objeto = s; ancho = s->w; alto = s->h; }
  void moverXY(Uint32 _x, Uint32 _y) { escenario_x = _x; escenario_y = _y; }
 protected:
  Uint32 ancho;
  Uint32 alto;

  Uint32 escenario_x; //ezquina arriba izquerda
  Uint32 escenario_y; //ezquina arriba izquierda
  Uint32 pantalla_x;
  Uint32 pantalla_y;
  Uint32 dpantalla_x; //desplaza spot para dibujado
  Uint32 dpantalla_y; //desplaza spat para dibujado
  //@todo lo ideal es que puedan haber algunos animados
  SDL_Surface *s_objeto; /*imagen del objeto*/
 private:
  void *data;
};

#endif
