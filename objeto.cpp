#include "objeto.h"
#include "compositor.h"

#include <iostream>


Objeto::Objeto(Uint32 _id) : Cosa(_id){
  data = NULL;
  dpantalla_x = dpantalla_y = 0;
}

Objeto::Objeto(Uint32 _id, Uint32 x, Uint32 y) : Cosa(_id){
  data = NULL;
  dpantalla_x = dpantalla_y = 0;
  escenario_x = x; escenario_y = y;
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

bool Objeto::enPantalla() {
if(
   (obXPantalla() < 5 && obXPantalla() + obAncho() < 5)
		   ||
   (obXPantalla() > Compositor::obVideo()->obAncho() && obXPantalla() + obAncho() > Compositor::obVideo()->obAncho())
   || (obYPantalla() < 5  && obYPantalla() + obAlto() < 5)
		      
   || (obYPantalla() > Compositor::obVideo()->obAlto() && obYPantalla()  + obAlto() > Compositor::obVideo()->obAlto())
     )
  return false;
 return true;
}
/**
 *Dibuja objeto desde el centro
 */
void Objeto::dibujar() {
  SDL_Rect sr, dr;


  pantalla_x = obX() - Compositor::obCamara()->x;
  pantalla_y = obY() - Compositor::obCamara()->y;
  pantalla_x -= dpantalla_x; pantalla_y -= dpantalla_y;
  

  //solo se dibuja cuando este en pantalla
  if(!enPantalla())
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


Uint32 Objeto::obXPantalla() { return (obX() - dpantalla_x) - Compositor::obCamara()->x;}
Uint32 Objeto::obYPantalla() { return (obY() - dpantalla_y) - Compositor::obCamara()->y;}
