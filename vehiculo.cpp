#include <iostream>
#include <cmath>

#include <SDL/SDL.h>

#include "compositor.h"
#include "vehiculo.h"


Vehiculo::Vehiculo(Uint32 id): Cosa(id){
  ancho = 50;
  alto = 50;
  max_vel = 15;
  min_vel = -10;
  def_accel = 1;
  def_retro = -1;
  def_giro = 10;
  def_giro_frenando = 7;
  s_andando = Compositor::obRecurso()->cargarImagen("./data/car1.png");
  s_cayendo = Compositor::obRecurso()->cargarImagen("./data/car1.png");
  s_saltando = Compositor::obRecurso()->cargarImagen("./data/car1.png");
  s_actual = s_andando;

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

void Vehiculo::desdeDirectorio(const char* ruta){
}


void Vehiculo::actualizar() {
  double reloj_escala = Compositor::obReloj()->escala();
  float giro = def_giro;
  accel = 0;

  if(Compositor::obTeclado()->presionado(t_accelerar) == true)
    accel = def_accel;
  

  if(accel) 
    {
      vel += accel * reloj_escala;
    }
  else
    {
      vel -= def_accel * reloj_escala;
      giro = def_giro_frenando;
      if(vel < 0) vel = 0;
    }
  //std::cerr << "accel:" << accel << " vel:" << vel << std::endl;
  
  if(vel) 
    {
      if(Compositor::obTeclado()->presionado(t_izquierda))
	angulo += giro  * reloj_escala;
      if(Compositor::obTeclado()->presionado(t_derecha))
	angulo -= giro * reloj_escala;
      if(angulo < 0) angulo += 360;
      if(angulo >= 360) angulo -= 360;
    }

  if(Compositor::obTeclado()->presionado(t_retroceder))
    vel *= 0.1;
  
  if(vel > max_vel) vel = max_vel;
  
  escenario_x += vel * cos(angulo * M_PI/180.0) * Compositor::obReloj()->escala();
  escenario_y += vel * -sin(angulo * M_PI/180.0) * Compositor::obReloj()->escala();
  //std::cerr << "escenario x: " << escenario_x << " escenario_y:" << escenario_y << std::endl;
  if(escenario_x < 0) escenario_x = 0;
  //@todo detener ancho escenario
  if(escenario_y < 0) escenario_y = 0;
  //@todo detener alto escenario
}


void Vehiculo::dibujar() {
  SDL_Rect sr, dr;
  pantalla_x = escenario_x - Compositor::obCamara()->x;
  pantalla_y = escenario_y - Compositor::obCamara()->y;
  
  int nangulo = angulo;
  if(nangulo < 0)  angulo = 360;
  sr.x = ancho * (nangulo / 4);
  sr.y = 0;
  sr.w = ancho; sr.h = alto;
  dr.x = pantalla_x - ancho/2;
  dr.y = pantalla_y - alto/2;
  dr.w = ancho; dr.w = alto;

  Compositor::obVideo()->blit(s_actual, &sr, &dr);
}
