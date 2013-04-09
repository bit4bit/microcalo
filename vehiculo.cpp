#include "cspa.h"
#include <iostream>
#include <cmath>

#include <SDL/SDL.h>

#include "compositor.h"
#include "vehiculo.h"


Vehiculo::Vehiculo(Uint32 id): Objeto(id){
  //@todo se debe inicializar un tipo de vehiculo

  s_objeto = tipo.s_andando;
  ancho = tipo.ancho;
  alto = tipo.alto;

  angulo = accel = vel = 0;
  t_accelerar = SDLK_t;
  t_retroceder = SDLK_n;
  t_izquierda = SDLK_a;
  t_derecha = SDLK_o;

  escenario_x = escenario_y = 100;
  pantalla_x = pantalla_y = 0;
}

Vehiculo::~Vehiculo(){
}


void Vehiculo::actualizar() {
  double reloj_escala = Compositor::obReloj()->escala();
  float giro = tipo.def_giro;
  accel = 0;

  si(Compositor::obTeclado()->presionado(t_accelerar) == true)
    accel = tipo.def_accel;
  

  si(accel) 
    {
      vel += accel * reloj_escala;
    }
  aunque
    {
      vel -= tipo.def_accel * reloj_escala;
      giro = tipo.def_giro_frenando;
      si(vel < 0) vel = 0;
    }
  //std::cerr << "accel:" << accel << " vel:" << vel << std::endl;
  
  si(vel) 
    {
      si(Compositor::obTeclado()->presionado(t_izquierda))
	angulo += giro  * reloj_escala;
      si(Compositor::obTeclado()->presionado(t_derecha))
	angulo -= giro * reloj_escala;
      si(angulo < 0) angulo += 360;
      si(angulo >= 360) angulo -= 360;
    }

  si(Compositor::obTeclado()->presionado(t_retroceder))
    vel *= 0.1;
  
  si(vel > tipo.max_vel) vel = tipo.max_vel;
  
  escenario_x += vel * cos(angulo * M_PI/180.0) * Compositor::obReloj()->escala();
  escenario_y += vel * -sin(angulo * M_PI/180.0) * Compositor::obReloj()->escala();
  //std::cerr << "escenario x: " << escenario_x << " escenario_y:" << escenario_y << std::endl;
  si(escenario_x < 0) escenario_x = 0;
  //@todo detener ancho escenario
  si(escenario_y < 0) escenario_y = 0;
  //@todo detener alto escenario
}


void Vehiculo::dibujar() {
  SDL_Rect sr, dr;
  pantalla_x = escenario_x - Compositor::obCamara()->x;
  pantalla_y = escenario_y - Compositor::obCamara()->y;
  
  int nangulo = angulo;
  si(nangulo < 0)  angulo = 360;
  sr.x = tipo.ancho * (nangulo / 4);
  sr.y = 0;
  sr.w = tipo.ancho; sr.h = tipo.alto;
  dr.x = pantalla_x - tipo.ancho/2; //se centra
  dr.y = pantalla_y - tipo.alto/2; //se centra
  dr.w = tipo.ancho; dr.w = tipo.alto;

  Compositor::obVideo()->blit(s_objeto, &sr, &dr);
}
