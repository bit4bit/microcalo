#include "punto_paso.h"
#include <cmath>

#include <SDL/SDL_gfxPrimitives.h>
#include "compositor.h"

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


Objeto* PuntoPaso::obObjeto()
{
  //@todo crear unico id
  Objeto *obj = new Objeto(4, escenario_x, escenario_y);
 
  SDL_Surface *tmp = Compositor::obVideo()->createSurface(dist_alejamiento * 2, dist_alejamiento * 2);
  SDL_Rect pos;
  obj->asignarSurface(tmp);

  obj->asignarDPantallaX(obj->obAncho()/2);
  obj->asignarDPantallaY(obj->obAlto()/2);
  circleColor(tmp, tmp->w / 2, tmp->h / 2, dist_alejamiento, SDL_MapRGBA(tmp->format, 255, 0, 0, 255));
  circleColor(tmp, tmp->w / 2, tmp->h / 2, dist_acercamiento, SDL_MapRGBA(tmp->format, 255, 255, 255, 255));
  return obj;
}
