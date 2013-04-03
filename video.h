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

  SDL_Surface* displayFormat(SDL_Surface *s) {
    return SDL_DisplayFormat(s);
  }

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
