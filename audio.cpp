#include "audio.h"

Audio* Audio::_self = 0;

Audio::Audio() {
}

Audio* Audio::instancia() {
  if(_self == 0) {
    _self = new Audio();
  }
  return _self;
}
