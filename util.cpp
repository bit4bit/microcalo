#include "util.h"
#include "TmxParser/Tmx.h"
#include <SDL/SDL.h>
#include "compositor.h"
#include <map>
#include <string>
#include <iostream>




SDL_Surface *surfaceDesdeCapaTmx(const char *capa, const char *archivo_tmx) {
  Tmx::Map *map = new Tmx::Map();
  map->ParseFile(archivo_tmx);
  SDL_Surface *fondo = NULL;
  std::map<int, SDL_Surface*> tilesets;

  if(map->HasError()) {
    std::cerr << "Fallo cargar tmx:" << archivo_tmx << std::endl;
    std::cerr << "\tcodigo error:" << map->GetErrorCode() << std::endl;

    std::cerr << "\ttexto error:" << map->GetErrorText() << std::endl;
    system("PAUSE");
    return NULL;
  }
  std::cerr << "Cargando tmx..." << archivo_tmx << std::endl;
  for(int i=0; i < map->GetNumTilesets(); ++i) {
    const Tmx::Tileset *tileset = map->GetTileset(i); 
    std::string ruta = std::string("data/") + tileset->GetImage()->GetSource();
    SDL_Surface *tmp = Compositor::obRecurso()->cargarImagen(ruta.c_str());
    if(!tmp) {
      std::cerr << "Fallo leer imagen:" << ruta.c_str() << std::endl;
      return NULL;
    }

    tilesets[tileset->GetFirstGid()] = tmp;
  }

  SDL_Surface *tmpfondo = Compositor::obVideo()->createSurface(map->GetWidth() * map->GetTileWidth(), map->GetHeight() * map->GetTileHeight());
  fondo = SDL_DisplayFormat(tmpfondo);
  SDL_FreeSurface(tmpfondo);

  for(int i=0; i < map->GetNumLayers(); ++i) {
    const Tmx::Layer *layer = map->GetLayer(i);

    if(layer->GetName() != capa)
      continue;


    /**
     *@todo hay un error, creo que es con TmxParser
     *no se lee el primer tile 
     */
    for(int y = 0; y < layer->GetHeight(); ++y) {
      for(int x = 0; x < layer->GetWidth(); ++x) {
	const Tmx::Tileset *tileset = map->FindTileset(layer->GetTileId(x, y));
	int CurTile = layer->GetTileId(x,y);	
	
	if(CurTile == 0) {
	  continue;
	}

	SDL_Rect src,dst;
	int cols = tileset->GetImage()->GetWidth()/tileset->GetTileWidth();;
	int tileset_row = (CurTile / cols);
	int tileset_col = (CurTile % cols);

	src.x = (tileset->GetMargin() + (tileset->GetTileWidth() + tileset->GetSpacing()) * tileset_col);
	src.y = (tileset->GetMargin() + (tileset->GetTileHeight() + tileset->GetSpacing()) * tileset_row);
	src.w = tileset->GetTileWidth();
	src.h = tileset->GetTileHeight();

	dst.x = x * tileset->GetTileWidth(); 
	dst.y = y * tileset->GetTileHeight();
	dst.w = tileset->GetTileWidth();
	dst.h = tileset->GetTileHeight();
	SDL_BlitSurface(tilesets[tileset->GetFirstGid()],&src, fondo, &dst);
      }
    }
    break;
  }
  delete map;
  std::cerr << "Fondo cargado correctamente desde tmx" << std::endl;
  //  Compositor::obVideo()->blit(SDL_DisplayFormat(fondo),NULL,NULL);
  return fondo;
}
