#ifndef AUDIO_H
#define AUDIO_H

#include <SDL/SDL.h>
#include <SDL/SDL_mixer.h>

class Audio
{
 protected:
  Audio();
  ~Audio();
 private:
  bool iniciado;
  static Audio* _self;
 public:
  static Audio* instancia();
  static void cerrar();

  int reproducir(Mix_Chunk *, int);
  int reproducir(Mix_Music*, int);
  void detener(int);
  int fadeOut(int, int = 500);
  bool reproduciendo(int);
};

#endif
