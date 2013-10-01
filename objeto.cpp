#include "cspa.h"
#include "objeto.h"
#include "compositor.h"

#include <iostream>


Objeto::Objeto(Uint32 _id) : Cosa(_id){
  data = NULL;
  dpantalla_x = dpantalla_y = 0;
  ancho = alto = 0;
  depurar = false;
  escenario_x = escenario_y = 0;
  limite_x = limite_y = 0;
}

Objeto::Objeto(Uint32 _id, Uint32 x, Uint32 y) : Cosa(_id){
  data = NULL;
  dpantalla_x = dpantalla_y = 0;
  escenario_x = x; escenario_y = y;
  depurar = false;
  ancho = alto = 0;
  limite_x = limite_y = 0;
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

  retorna obj;
}


void Objeto::actualizar() {
}

bool Objeto::enPantalla() {
si(
   (obXPantalla() < 5 && obXPantalla() + obAncho() < 5)
		   ||
   (obXPantalla() > Compositor::obVideo()->obAncho() && obXPantalla() + obAncho() > Compositor::obVideo()->obAncho())
   || (obYPantalla() < 5  && obYPantalla() + obAlto() < 5)
		      
   || (obYPantalla() > Compositor::obVideo()->obAlto() && obYPantalla()  + obAlto() > Compositor::obVideo()->obAlto())
     )
  retorna false;
 retorna true;
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
  si(!enPantalla())
    retorna;
  //std::cout << "ox:" << pantalla_x << " oy:" << pantalla_y << std::endl;
  sr.x = 0;
  sr.y = 0;
  sr.w = ancho; sr.h = alto;
  dr.x = pantalla_x;
  dr.y = pantalla_y;
  dr.w = ancho; dr.w = alto;


  Compositor::obVideo()->blit(s_objeto, &sr, &dr);
  dibujarDepurar();
}

void Objeto::dibujarDepurar() {
  si(!depurar)
    return;
  
  cada(std::vector<Circular>::iterator it = colision_circular.begin(); it != colision_circular.end(); ++it) {

    Compositor::obVideo()->circle(Compositor::obVideo()->obSurface(),
				  ((*it).x - Compositor::obCamara()->x),
				  ((*it).y - Compositor::obCamara()->y), 
				  (*it).radio, 9999);
  }
}

Sint32 Objeto::obXPantalla() { retorna (obX() - dpantalla_x) - Compositor::obCamara()->x;}
Sint32 Objeto::obYPantalla() { retorna (obY() - dpantalla_y) - Compositor::obCamara()->y;}

void Objeto::regularALimites() {
  si(escenario_x < 0) escenario_x = 0;
  si(escenario_y < 0) escenario_y = 0;
  si(limite_x && limite_y) {
    si(escenario_x > limite_x + obAncho()) escenario_x = limite_x - obAncho() - 1;
    si(escenario_y > limite_y + obAlto()) escenario_y = limite_y - obAlto() - 1;
  }
}


void Objeto::asignarColisionCircular(int x, int y, int radio)
{
  colision_circular.push_back(Circular(x, y,radio));
}
