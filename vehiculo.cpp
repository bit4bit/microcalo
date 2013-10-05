/**
 *
 *@date 23 ABRIL 2013
 *he tenido muchos problemas con el sistema de colision y el vehiculo
 *he cambiado el sistema de colision para trabjar con circunferencias
 *ya que con cajas no me daba la colision muy bien.
 */
#include "cspa.h"
#include <iostream>
#include <cmath>
#include <vector>

#include <SDL/SDL.h>

#include "compositor.h"
#include "vehiculo.h"
#include <SDL/SDL_rotozoom.h>


Vehiculo::Vehiculo(Uint32 id, VehiculoTipo *_tipo): Objeto(id){

  tipo = _tipo;
  if(!tipo) {
    Compositor::obGestorVehiculoTipo()->encontrar("generico");
  }
  s_objeto = tipo->obSVehiculo();
  ancho = tipo->obAncho();
  alto = tipo->obAlto();

  angulo = accel = vel = 0;
  acelerarP = retrocederP = izquierdaP = derechaP = false;
  choqueP = false;
  escenario_x = escenario_y = 100;
  pantalla_x = pantalla_y = 0;
}

Vehiculo::Vehiculo(Uint32 id, VehiculoTipo *_tipo, Uint32 x, Uint32 y, Uint32 _angulo): Objeto(id){
  
  tipo = _tipo;
  if(!tipo) {
    Compositor::obGestorVehiculoTipo()->encontrar("generico");
  }
  s_objeto = tipo->obSVehiculo();
  ancho = tipo->obAncho();
  alto = tipo->obAlto();


  angulo = accel = vel = 0;
  angulo = _angulo;
  acelerarP = retrocederP = izquierdaP = derechaP = false;

  escenario_x = x;
  escenario_y = y;
  pantalla_x = pantalla_y = 0;
}

Vehiculo::~Vehiculo(){
}


void Vehiculo::actualizar(std::vector<Objeto*>&objetos) {
  double reloj_escala = Compositor::obReloj()->escala();
  float giro = tipo->obDefGiro();
  accel = 0;

  si(choqueP)
  {
    //se permite dar reversa cuando colisione
    si(!retrocederP)
    {
      choqueP = acelerarP = retrocederP = izquierdaP = derechaP = false;
      return;
    }

  }

  si(acelerarP == true)
    accel = tipo->obDefAccel();
 

  si(accel) 
    {
      vel += accel * reloj_escala;
    }
  //desacelera si no esta acelerando
  aunque si(!retrocederP && choqueP == false )
    {
      vel -= tipo->obDefAccel() * reloj_escala;
      //giro = tipo->def_giro_frenando;
      si(vel < 0) vel = 0;
    }


  si(vel != 0) 
    {
      si(izquierdaP)
	angulo += giro  * reloj_escala;
      si(derechaP)
	angulo -= giro * reloj_escala;
      si(angulo < 0) angulo += 360;
      si(angulo >= 360) angulo -= 360;
    }

  //frena.. como retroceder??
  //si(retrocederP)
  //vel *= 0.9;
  si(retrocederP)
  {
    vel = -abs(tipo->obDefRetro());
  }
  si(vel > tipo->obMaxVel()) vel = tipo->obMaxVel();


  //antes de mover verifica colisiocn
  int tx=0, ty=0;
  calcularPosicion(tx, ty);
  int nx = obX() + tx;
  int ny = obY() + ty;
  si(Compositor::obColision()->entreObjetos(this, nx, ny, objetos)) {
    choqueRetroceder();
  }aunque{
    calcularPosicionFuturo(tx, ty, vel, angulo);
    nx = obXCentro() + tx;
    ny = obYCentro() + ty;
    if(Compositor::obColision()->conBloque(this, nx, ny)) {
      std::cout << "Con bloque escenario" << std::endl;
      choqueRetroceder();
    }else{
      actualizarPosicion();
    }
  }

  choqueP = acelerarP = retrocederP = izquierdaP = derechaP = false;
  regularALimites();
}



void Vehiculo::dibujar() {
  SDL_Rect sr, dr;				       
  SDL_Surface *tmp = NULL;
  pantalla_x = escenario_x - Compositor::obCamara()->x;
  pantalla_y = escenario_y - Compositor::obCamara()->y;
  
  int nangulo = angulo;
  si(nangulo < 0)  angulo = 360;
  
  //antiguo metodo de renderizado
  //sr.x = tipo->ancho * (nangulo / 4);
  //sr.y = 0;
  //sr.w = tipo->ancho; sr.h = tipo->alto;
  //dr.x = pantalla_x - tipo->ancho/2; //se centra
  //dr.y = pantalla_y - tipo->alto/2; //se centra

  dr.w = tipo->obAncho(); dr.w = tipo->obAlto();
  SDL_Surface *tmp2 = rotozoomSurface(s_objeto, angulo, 1, 0);
  tmp = SDL_DisplayFormatAlpha(tmp2);
  SDL_FreeSurface(tmp2);

  dr.x = pantalla_x - ((tmp->w/2) - (s_objeto->w/2));
  dr.y = pantalla_y - ((tmp->h/2) - (s_objeto->h/2));
  Compositor::obVideo()->blit(tmp, NULL, &dr);
  SDL_FreeSurface(tmp);
  //Compositor::obVideo()->blit(s_objeto, &sr, &dr);
  dibujarDepurar();
}

void Vehiculo::choque() {
  //std::cout << "efecto choque" << std::endl;
  choqueRetroceder();
}

void Vehiculo::choqueRetroceder() {
  double reloj_escala = Compositor::obReloj()->escala();
  bool enReversa = false;
  si(vel < 0)
    enReversa = true;
  si(!choqueP)
  {
    vel = abs(vel) * -0.3;
  }

  actualizarPosicion();
  choqueP = true;
}

void Vehiculo::actualizarPosicion() {
  int ix, iy;
  calcularPosicion(ix, iy);
  escenario_x += ix;
  escenario_y += iy;
}

void Vehiculo::calcularPosicion(int &x, int &y) {
  x = vel * cos(angulo * M_PI/180.0) * Compositor::obReloj()->escala();
  y = vel * -sin(angulo * M_PI/180.0) * Compositor::obReloj()->escala();
}

void Vehiculo::calcularPosicionFuturo(int &x, int &y, float& vel, float& angulo)
{
 x = vel * cos(angulo * M_PI/180.0) * Compositor::obReloj()->escala();
 y = vel * -sin(angulo * M_PI/180.0) * Compositor::obReloj()->escala();
}
