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
  Tmx::Map *obMap() { return tmx; }
  int obAlto() { return tmx->GetHeight() * tmx->GetTileHeight(); }
  int obAncho() { return tmx->GetWidth() * tmx->GetTileWidth();}
  int obColumnas() { return tmx->GetWidth();}
  int obFilas() { return tmx->GetHeight();}
  /**
   *Imprime srect desde capa desde tmx a 
   *superficie *dst
   */
  void blit(const char * capa, SDL_Rect *srect, SDL_Surface *dst, SDL_Rect *drect = NULL, int alpha = -1);


 private:
  /**
   *Imprime cuadro a cuadro
   */
  void blitTile(const char * capa, SDL_Rect *srect, SDL_Surface *dst, SDL_Rect *drect = NULL, int alpha = -1);
  /**
   *cachea cuadro a imagen y renderiza
   */
  void blitImage(const char * capa, SDL_Rect *srect, SDL_Surface *dst, SDL_Rect *drect = NULL, int alpha = -1);
  std::map<int,SDL_Surface *> s_tileset;

  Tmx::Map *tmx;
  std::map<std::string, SDL_Surface *> cache_image;
  
};

#endif
