#include "punto_paso_gestor.h"


PuntoPasoGestor::PuntoPasoGestor()
{
}


void PuntoPasoGestor::anidarPuntoPaso(Objeto *obj, PuntoPaso *pp)
{
  objPuntos[obj].push_back(pp);
}

void PuntoPasoGestor::anidarPuntoPaso(Objeto *obj, Uint32 x, Uint32 y, Uint32 dist_aleja, Uint32 dist_acerca)
{
  objPuntos[obj].push_back(new PuntoPaso(x, y , dist_aleja, dist_acerca));
}

PuntoPaso* PuntoPasoGestor::primerPuntoPaso(Objeto *obj)
{
  return objPuntos[obj].at(0);
}

PuntoPaso* PuntoPasoGestor::ultimoPuntoPaso(Objeto *obj)
{
  return objPuntos[obj].at(objPuntos[obj].size());
}

PuntoPaso* PuntoPasoGestor::puntoPasoA(Objeto *obj, Uint32 pos)
{
  return objPuntos[obj].at(pos);
}

Uint32 PuntoPasoGestor::tamano(Objeto *obj)
{
  return objPuntos[obj].size();
}
