#ifndef COMPOSITOR_H
#define COMPOSITOR_H

#include <SDL/SDL.h>
#include <iostream>
#include "video.h"
#include "audio.h"
#include "reloj.h"
#include "teclado.h"
#include "cosa.h"
#include "recurso.h"
#include "camara.h"
#include "colision.h"
#include "mando.h"
#include "texto.h"
#include "configuracion.h"
#include "script.h"
#include "gestor_vehiculo_tipo.h"
#include "gestor_escenario.h"




class Compositor
{
 protected:
  Compositor() {};
 private:
  
 public:
  static void cerrar() {
    std::cout << "Finalizando compositor" << std::endl;
    obScript()->cerrar();
    obGestorVehiculoTipo()->cerrar();
    obGestorEscenario()->cerrar();
  }
  static Video *obVideo() { return Video::instancia(); }
  static Audio *obAudio() { return Audio::instancia(); }
  static Reloj *obReloj() { return Reloj::instancia(); }
  static Teclado *obTeclado() { return Teclado::instancia(); }
  static Mando* obMando() { return Mando::instancia(); }
  static Recurso *obRecurso() { return Recurso::instancia(); }
  static Camara *obCamara() { return Camara::instancia(); }
  static Colision *obColision() { return Colision::instancia(); }
  static Texto *obTexto() { return Texto::instancia(); }
  static Configuracion* obConfiguracion() { return Configuracion::instancia(); }
  static Script* obScript() { return Script::instancia();}
  static GestorVehiculoTipo* obGestorVehiculoTipo() { return GestorVehiculoTipo::instancia();}
  static GestorEscenario* obGestorEscenario() { return GestorEscenario::instancia(); }
};

extern bool SALIR;
#endif
