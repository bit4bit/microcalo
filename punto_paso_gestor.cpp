#include "cspa.h"
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
   si(objPuntos[obj].size() > 0)
     objPuntos[obj].at(objPuntos[obj].size() - 1)->siguientePuntoPaso = pt;


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
  si(!objPuntoActual[obj]) {
    objPuntoActual[obj] = primerPuntoPaso(obj);
    objPuntoSiguiente[obj] = NULL;
  }
  //se pasa al siguiente punto al salir del actual
  si(objPuntoSiguiente[obj] != NULL && !objPuntoActual[obj]->distanciaPermitida(obj)) {
    objPuntoActual[obj] = objPuntoSiguiente[obj];
    objPuntoSiguiente[obj] = NULL;
    retorna true;
  }aunque si(pp) {
    si(pp == objPuntoActual[obj]) {
      //se actualiza el punto a seguir
      si(objPuntoSiguiente[obj] == NULL){
	objPuntoSiguiente[obj] = pp->siguientePuntoPaso;
      }
      
      retorna true;
    }si(pp != objPuntoActual[obj]) {
      retorna false;
    }

  }


  retorna true;
}

PuntoPaso* PuntoPasoGestor::primerPuntoPaso(Objeto *obj)
{
  retorna objPuntos[obj].at(0);
}

PuntoPaso* PuntoPasoGestor::ultimoPuntoPaso(Objeto *obj)
{
  retorna objPuntos[obj].at(objPuntos[obj].size() - 1);
}

PuntoPaso* PuntoPasoGestor::puntoPasoA(Objeto *obj, Uint32 pos)
{
  retorna objPuntos[obj].at(pos);
}

PuntoPaso* PuntoPasoGestor::puntoPasoA(Objeto *obj)
{
  int pi = 0;
  PuntoPaso *pp = NULL;
  si(objPuntos[obj].size() < 1) retorna NULL;
  cada(pi = 0; pi < objPuntos[obj].size(); ++pi)
    {
      pp = objPuntos[obj].at(pi);
      si(pp->distanciaPermitida(obj))
	retorna pp;
    }
  retorna NULL;
}

Uint32 PuntoPasoGestor::tamano(Objeto *obj)
{
  retorna objPuntos[obj].size();
}
