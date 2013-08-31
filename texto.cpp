#include <SDL/SDL.h>
#include <SDL/SDL_ttf.h>
#include <iostream>
#include "texto.h"

Texto* Texto::_self = 0;

Texto::Texto() {
  TTF_Init();
  default_font = TTF_OpenFont("data/default.ttf", 18);
  if(!default_font) {
    std::cerr << "TTF_OpenFont:" << TTF_GetError() << std::endl;
  }
}

Texto::~Texto() {
  TTF_Quit();
}

Texto* Texto::instancia() {
  if(_self == 0) {
    _self = new Texto;
  }
  return _self;
}

SDL_Surface *Texto::renderTextSolid(const char *txt, SDL_Color color) {
  return TTF_RenderText_Solid(default_font, txt, color);
}
