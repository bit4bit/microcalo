#ifndef VIDEO_H
#define VIDEO_H

#include <SDL/SDL.h>

class Video
{
 protected:
  Video();  
  
 private:
  static Video *_self;
  SDL_Surface *s_pantalla;
  Uint16 ancho;
  Uint16 alto;

 public:
  static Video* instancia();
  void actualizar();
  void dibujar();

  Uint16 obAncho() {
    return ancho;
  }

  Uint16 obAlto() {
    return alto;
  }

  Uint32 mapRGB(Uint8 r, Uint8 g, Uint8 b) {
    return SDL_MapRGB(s_pantalla->format, r, g, b);
  }

  SDL_Surface* displayFormat(SDL_Surface *s) {
    return SDL_DisplayFormat(s);
  }

  SDL_Surface* createSurface(Uint32 w, Uint32 h);  

  int toggleFullScreen() {
    return SDL_WM_ToggleFullScreen(s_pantalla);
  }

  int clearScreenColor(Uint32 color) {
    return SDL_FillRect(s_pantalla, NULL, color);
  }

  int blit(SDL_Surface *s, SDL_Rect *srect, SDL_Rect *drect) {
    return SDL_BlitSurface(s, srect, s_pantalla, drect);
  }
};

#endif
