#include "punto_paso_gestor.h"
#include <iostream>

PuntoPasoGestor::PuntoPasoGestor()
{
}


void PuntoPasoGestor::anidarPuntoPaso(Objeto *obj, PuntoPaso *pp)
{
  objPuntos[obj].push_back(pp);
}

void PuntoPasoGestor::anidarPuntoPaso(Objeto *obj, Uint32 x, Uint32 y, Uint32 dist_aleja, Uint32 dist_acerca)
{
  PuntoPaso *pt = new PuntoPaso(x, y , dist_aleja, dist_acerca);
   if(objPuntos[obj].size() > 0)
     objPuntos[obj].at(objPuntos[obj].size() - 1)->siguiente = pt;


  objPuntos[obj].push_back(pt);
}

/**
 *lleva continuidad entre puntos para el objeto dado
 *y retorna true mientres este siguiendo los puntos
 *en el momento que toque un punto de paso no correspondiente
 *retorna falso.
 *@todo hay veces que no lleva la continudad con circulos solapados??
 */
bool PuntoPasoGestor::continuadoPuntoPasoA(Objeto *obj)
{
  PuntoPaso *pp = puntoPasoA(obj);
  if(!objPuntoActual[obj]) {
    objPuntoActual[obj] = primerPuntoPaso(obj);
    objPuntoSiguiente[obj] = NULL;
  }
  //se pasa al siguiente punto al salir del actual
  if(objPuntoSiguiente[obj] != NULL && !objPuntoActual[obj]->distanciaPermitida(obj)) {
    objPuntoActual[obj] = objPuntoSiguiente[obj];
    objPuntoSiguiente[obj] = NULL;
    return true;
  }else if(pp) {
    if(pp == objPuntoActual[obj]) {
      //se actualiza el punto a seguir
      if(objPuntoSiguiente[obj] == NULL){
	objPuntoSiguiente[obj] = pp->siguiente;
      }

      return true;
    }if(pp != objPuntoActual[obj]) {
      return false;
    }

  }


  return true;
}

PuntoPaso* PuntoPasoGestor::primerPuntoPaso(Objeto *obj)
{
  return objPuntos[obj].at(0);
}

PuntoPaso* PuntoPasoGestor::ultimoPuntoPaso(Objeto *obj)
{
  return objPuntos[obj].at(objPuntos[obj].size() - 1);
}

PuntoPaso* PuntoPasoGestor::puntoPasoA(Objeto *obj, Uint32 pos)
{
  return objPuntos[obj].at(pos);
}

PuntoPaso* PuntoPasoGestor::puntoPasoA(Objeto *obj)
{
  int pi = 0;
  PuntoPaso *pp = NULL;
  if(objPuntos[obj].size() < 1) return NULL;
  for(pi = 0; pi < objPuntos[obj].size(); ++pi)
    {
      pp = objPuntos[obj].at(pi);
      if(pp->distanciaPermitida(obj))
	return pp;
    }
  return NULL;
}

Uint32 PuntoPasoGestor::tamano(Objeto *obj)
{
  return objPuntos[obj].size();
}
