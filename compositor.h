#ifndef COMPOSITOR_H
#define COMPOSITOR_H

#include <SDL/SDL.h>

#include "video.h"
#include "audio.h"
#include "reloj.h"
#include "teclado.h"
#include "cosa.h"
#include "recurso.h"
#include "camara.h"

class Compositor
{
 protected:
  Compositor() {};

 private:
  
 public:
  static Video *obVideo() { return Video::instancia(); }
  static Audio *obAudio() { return Audio::instancia(); }
  static Reloj *obReloj() { return Reloj::instancia(); }
  static Teclado *obTeclado() { return Teclado::instancia(); }
  static Recurso *obRecurso() { return Recurso::instancia(); }
  static Camara *obCamara() { return Camara::instancia(); }
};

#endif
