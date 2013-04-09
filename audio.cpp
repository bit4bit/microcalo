#include "cspa.h"
#include "audio.h"

Audio* Audio::_self = 0;

Audio::Audio() {
}

Audio* Audio::instancia() {
  si(_self == 0) {
    _self = new Audio();
  }
  retorna _self;
}
