#ifndef TMX_RENDER_H
#define TMX_RENDER_H

#include "TmxParser/Tmx.h"
#include <SDL/SDL.h>
#include <map>

/**
 *Renderiza o bien grafica
 *imagen basado es un mapa .tmx
 */
class TmxRender
{
 public:
  TmxRender();
  ~TmxRender();

  bool CargarDesdeArchivo(const char *archivo);
 
  int obAlto() { return tmx->GetHeight() * tmx->GetTileHeight(); }
  int obAncho() { return tmx->GetWidth() * tmx->GetTileWidth();}
  /**
   *Imprime srect desde capa desde tmx a 
   *superficie *dst
   */
  void blit(const char * capa, SDL_Rect *srect, SDL_Surface *dst, SDL_Rect *drect);


 private:
  std::map<int,SDL_Surface *> s_tileset;

  Tmx::Map *tmx;
};

#endif