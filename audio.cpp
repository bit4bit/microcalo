#include "cspa.h"
#include "audio.h"
#include <iostream>

Audio* Audio::_self = 0;

Audio::Audio() {
  iniciado = false;
  SDL_InitSubSystem(SDL_INIT_AUDIO);
  int audio_rate = 22050;
  Uint16 audio_format = AUDIO_S16; 
  int audio_channels = 2;
  int audio_buffers = 4096;
  if(Mix_OpenAudio(audio_rate, audio_format, audio_channels, audio_buffers)) {
    std::cerr << "Fallo abrir dispositivo de audio" << std::endl;
  }else{
    std::cerr << "Inicializado sistema de audio" << std::endl;
    iniciado = true;
  }
}

Audio::~Audio() {
  Mix_CloseAudio();
  SDL_QuitSubSystem(SDL_INIT_AUDIO);
}

Audio* Audio::instancia() {
  si(_self == 0) {
    _self = new Audio();
  }
  retorna _self;
}

void Audio::cerrar() {
  delete _self;
  _self = 0;
}

int Audio::reproducir(Mix_Chunk *chunk, int loop) {
  if(!iniciado) return 0;
  return Mix_PlayChannel(-1, chunk, loop);
}

int Audio::reproducir(Mix_Music *chunk, int loop) {
  if(!iniciado) return 0;
  if(Mix_PlayMusic(chunk, loop) == -1) {
    std::cerr << "Fallo reproducir musica:" << Mix_GetError() << std::endl;
  }
  return 0;
}

int Audio::fadeOut(int channel, int ms) {
  if(!iniciado) return 0;
  return Mix_FadeOutChannel(channel, ms);
}

bool Audio::reproduciendo(int channel) {
  if(!iniciado) return 0;
  return Mix_Playing(channel) == 0 ? false : true;
}

void Audio::detener(int channel) {
  if(!iniciado) return;
  Mix_HaltChannel(channel);
}
