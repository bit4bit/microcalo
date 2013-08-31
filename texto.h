#ifndef TEXTO_H
#define TEXTO_H

#include <SDL/SDL_ttf.h>
#include <SDL/SDL.h>

/**
 *Graficar texto
 */
class Texto
{
 protected:
  Texto();
  ~Texto();

 public:
  static Texto* instancia();
  SDL_Surface *renderTextSolid(const char *txt, SDL_Color color);
 private:
  static Texto *_self;
  TTF_Font *default_font;
};

#endif
