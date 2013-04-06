#include "punto_paso.h"
#include <cmath>


PuntoPaso::PuntoPaso(Uint32 x, Uint32 y, Uint32 distAleja, Uint32 distAcerca) :
  escenario_x(x), escenario_y(y),
  dist_alejamiento(distAleja), dist_acercamiento(distAcerca)
{
}


bool PuntoPaso::distanciaPermitida(Objeto *obj)
{
  double dist = sqrt( (obj->obX() - escenario_x) * (obj->obX() - escenario_x)
		      +
		      (obj->obY() - escenario_y) * (obj->obY() - escenario_y));
  if(dist > dist_alejamiento)
    return false;
  return true;
}

bool PuntoPaso::estaCerca(Objeto *obj)
{
 double dist = sqrt( (obj->obX() - escenario_x) * (obj->obX() - escenario_x)
		     +
		     (obj->obY() - escenario_y) * (obj->obY() - escenario_y));
 if(dist <= dist_acercamiento)
   return true;
 return false;
}
