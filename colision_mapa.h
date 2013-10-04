#ifndef COLISION_MAPA_H
#define COLISION_MAPA_H

#define BLOQUEO_NINGUNO 0 //no colision
#define BLOQUEO_TODO 1 //colision no paso

#include "TmxParser/Tmx.h"
#include <map>
class ColisionMapa
{
 public:
  ColisionMapa();
  ~ColisionMapa();
  void asignarMapaDesdeCapaTmx(const char *capa, Tmx::Map *tmx,const std::map<int,std::string> *mapeo);
  void asignarMapa(int _colmapa[255][255], int ancho, int alto);
  bool moverVehiculo(int &x, int &y, double vel, double angle);
  bool mover(int &x, int &y, int paso_x, int paso_y);

 private:
  int colmapa[255][255];
};

#endif
