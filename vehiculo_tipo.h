#ifndef VEHICULO_TIPO_H
#define VEHICULO_TIPO_H

#include <SDL/SDL.h>
#include <string>
#include <map>
#include <mruby.h>
/**
 *Representa un tipo de vehiculo
 *carro, camiones, volquetas
 *sus propiedas y representacion en imaganes.
 *@todo hacer que el tipo pueda agregar efectos
 *al vehiculo..
 */
class VehiculoTipo
{
 private:
  std::string nombre;
  
  int ancho;
  int alto;
  

  float max_vel;
  float min_vel;
  float def_accel;
  float def_retro;
  float def_giro;
  float def_giro_frenando;

  SDL_Surface* s_vehiculo;
  
 public:
  VehiculoTipo();
  static void bindingScript(mrb_state *mrb);
  const std::string& obNombre() { return nombre;}
  void asignarNombre(std::string n) { nombre = n;}

  int obAncho() { return ancho;}
  int obAlto() { return alto;}
  void asignarAncho(int v){ ancho = v;}
  void asignarAlto(int v){ alto = v;}
  float obMaxVel() { return max_vel;}
  void asignarMaxVel(float v) { max_vel = v;}
  
  float obMinVel() { return min_vel;}
  void asignarMinVel(float v) {  min_vel = v;}
  
  float obDefAccel() { return def_accel;}
  void asignarDefAccel(float v){  def_accel = v;}

  float obDefRetro() { return def_retro;}
  void asignarDefRetro(float v) {  def_retro = v;}
  
  float obDefGiro() { return def_giro;}				
  void asignarDefGiro(float v) {  def_giro = v;}
  
  float obDefGiroFrenando() { return def_giro_frenando;}
  void asignarDefGiroFrenando(float v) {  def_giro_frenando = v;}

  SDL_Surface* obSVehiculo() { return s_vehiculo;}
  void asignarSVehiculo(SDL_Surface *t){ s_vehiculo = t;}
  void asignarSVehiculoDesdeArchivo(std::string);
  std::string toString() { return std::string("VehiculoTipo:").append(nombre);}
};

#endif
