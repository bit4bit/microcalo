#ifndef VEHICULO_TIPO_H
#define VEHICULO_TIPO_H

#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>
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
  int s_vehiculo_columnas; //colunmas para sacar imagenes de s_vehiculo
  SDL_Surface* s_vehiculo_izq;
  SDL_Surface* s_vehiculo_der;
  Mix_Chunk* audio_motor; //cuando esta en motor
 public:
  VehiculoTipo();
  static void bindingScript(mrb_state *mrb);
  const std::string& obNombre() { return nombre;}
  void asignarNombre(std::string n) { nombre = n;}
  int obSVehiculoColumnas() { return s_vehiculo_columnas;}
  void asignarSVehiculoColumnas(int v) { s_vehiculo_columnas = v; }

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
  SDL_Surface* obSVehiculoDer() { return s_vehiculo_der;}
  SDL_Surface* obSVehiculoIzq() { return s_vehiculo_izq;}
  void asignarSVehiculo(SDL_Surface *t){ s_vehiculo = t;}
  void asignarSVehiculoDer(SDL_Surface *t){ s_vehiculo_der = t;}
  void asignarSVehiculoIzq(SDL_Surface *t){ s_vehiculo_izq = t;}
  void asignarSVehiculoDesdeArchivo(std::string);
  void asignarSVehiculoDerDesdeArchivo(std::string);
  void asignarSVehiculoIzqDesdeArchivo(std::string);
  std::string toString() { return std::string("VehiculoTipo:").append(nombre);}

  Mix_Chunk* obAudioMotor() { return audio_motor; }
  void asignarAudioMotor(std::string archivo) {
    audio_motor = Mix_LoadWAV(archivo.c_str());
  }

  void correr(void *block);
};

#endif
