#include "objeto.h"
#include "compositor.h"

#include <iostream>


Objeto::Objeto(Uint32 _id) : Cosa(_id){
}

Objeto::~Objeto(){
}

Objeto* Objeto::desdeImagen(const char *ruta, Uint32 _id, Uint32 x, Uint32 y)
{
  Objeto *obj;

  obj = new Objeto(_id);
  obj->s_objeto = Compositor::obRecurso()->cargarImagen(ruta);
  obj->escenario_x = x;
  obj->escenario_y = y;
  obj->ancho = obj->s_objeto->w;
  obj->alto = obj->s_objeto->h;
  return obj;
}


void Objeto::actualizar() {
}

/**
 *Dibuja objeto desde el centro
 */
void Objeto::dibujar() {
  SDL_Rect sr, dr;


  pantalla_x = obXCentro() - Compositor::obCamara()->x;
  pantalla_y = obYCentro() - Compositor::obCamara()->y;

  //solo se dibuja cuando este en pantalla
  if(
     (pantalla_x < 5 && pantalla_x + ancho < 5)
		   ||
		   (pantalla_x > Compositor::obVideo()->obAncho() && pantalla_x + ancho > Compositor::obVideo()->obAncho())
     || (pantalla_y < 5  && pantalla_y + alto < 5)
		      
           || (pantalla_y > Compositor::obVideo()->obAlto() && pantalla_y  + alto > Compositor::obVideo()->obAlto())
     )
    return;
  //std::cout << "ox:" << pantalla_x << " oy:" << pantalla_y << std::endl;
  sr.x = 0;
  sr.y = 0;
  sr.w = ancho; sr.h = alto;
  dr.x = pantalla_x;
  dr.y = pantalla_y;
  dr.w = ancho; dr.w = alto;

  Compositor::obVideo()->blit(s_objeto, &sr, &dr);
}


Uint32 Objeto::obXPantalla() { return obX() - Compositor::obCamara()->x;}
Uint32 Objeto::obYPantalla() { return obY() - Compositor::obCamara()->y;}
