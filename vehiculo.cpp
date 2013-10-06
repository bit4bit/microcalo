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

#include <vmath.h>
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

  //
  carLocation.x = escenario_x;
  carLocation.y = escenario_y;
  carSpeed = 0;
  carHeading = 0;
  carDriftHeading = 0;
}

Vehiculo::~Vehiculo(){
}

void Vehiculo::actualizar(std::vector<Objeto*>& objetos) {
  
  //basado en: http://engineeringdotnet.blogspot.com/2010/04/simple-2d-car-physics-in-games.html
  float steerAngle = 0;
  float wheelBase = 2;

  double reloj_escala = Compositor::obReloj()->escala();
  float giro = tipo->obDefGiro();
  float accel = 0;
  
  si(acelerarP) {
    carSpeed += tipo->obDefAccel();;
    si(carSpeed > tipo->obMaxVel()) carSpeed = tipo->obMaxVel();
  }aunque si(retrocederP) {
    carSpeed += tipo->obDefRetro();
    si(carSpeed < tipo->obMinVel()) carSpeed = tipo->obMinVel();
  }
  aunque si(!retrocederP && choqueP == false )
  {
    carSpeed -= tipo->obDefAccel() * reloj_escala;
    si(carSpeed < 0) carSpeed = 0;
  }

  si(izquierdaP)
    steerAngle = -giro * M_PI/180;
  si(derechaP)
    steerAngle = giro * M_PI/180;


  Vector2f tcarLocation = carLocation;
  Vector2f vt =  Vector2f(cos(carHeading), sin(carHeading));
  Vector2f vtt =  Vector2f(cos(carHeading+steerAngle), sin(carHeading+steerAngle));
  Vector2f frontWheel = tcarLocation + vt * (wheelBase/2);
  frontWheel += vtt * carSpeed * reloj_escala;
  Vector2f backWheel = tcarLocation - vt * (wheelBase/2);
  backWheel +=  vt * carSpeed * reloj_escala ;

  tcarLocation = (frontWheel + backWheel) / 2;
  carHeading = atan2(frontWheel.y - backWheel.y, frontWheel.x - backWheel.x);
  carDriftHeading = carHeading + (steerAngle * (carSpeed/tipo->obMaxVel())) * 15;

  si(Compositor::obColision()->entreObjetos(this, tcarLocation.x, tcarLocation.y, objetos)) {
    choqueRetroceder();
  }aunque{
    
    if(Compositor::obColision()->conBloque(this, tcarLocation.x, tcarLocation.y)) {
      if(!retrocederP)
	choqueRetroceder();
    }else{
      carLocation = tcarLocation;
      escenario_x = carLocation.x;
      escenario_y = carLocation.y;
    }

  }

  if(carHeading > M_PI/4 && carHeading < M_PI/4) {
    angulo = -carHeading * 180/M_PI;
  }else{
    angulo = -carDriftHeading * 180/M_PI;
  }


  choqueP = acelerarP = retrocederP = izquierdaP = derechaP = false;
  regularALimites();
}




void Vehiculo::dibujar() {
  SDL_Rect sr, dr;				       
  SDL_Surface *tmp = NULL;
  pantalla_x = escenario_x - Compositor::obCamara()->x;
  pantalla_y = escenario_y - Compositor::obCamara()->y;
  
  //int nangulo = angulo;
  int nangulo = angulo;
  si(nangulo < 0)  angulo = 360;
  

  dr.w = tipo->obAncho(); dr.w = tipo->obAlto();
  SDL_Surface *tmp2 = rotozoomSurface(s_objeto, nangulo, 1, 0);
  tmp = SDL_DisplayFormatAlpha(tmp2);
  SDL_FreeSurface(tmp2);

  dr.x = pantalla_x - tmp->w/2;
  dr.y = pantalla_y - tmp->h/2;
  Compositor::obVideo()->blit(tmp, NULL, &dr);
  SDL_FreeSurface(tmp);
  dibujarDepurar();
}

void Vehiculo::choque() {
  //std::cout << "efecto choque" << std::endl;
  choqueRetroceder();
}

void Vehiculo::choqueRetroceder() {
  double reloj_escala = Compositor::obReloj()->escala();
  bool enReversa = false;
  si(carSpeed < 0)
    enReversa = true;
  si(!choqueP)
  {
    carSpeed = abs(carSpeed) * -0.7;
  }

  choqueP = true;
}

