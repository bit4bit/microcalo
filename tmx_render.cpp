#include "tmx_render.h"
#include "compositor.h"
#include "TmxParser/Tmx.h"
#include <SDL/SDL.h>
#include <map>
#include <string>
#include <iostream>
#include <cstdlib>
#include <cassert>

TmxRender::TmxRender()
{
  tmx = NULL;
}

TmxRender::~TmxRender()
{
  if(tmx)
    delete tmx;
  for(std::map<int, SDL_Surface*>::iterator iter = s_tileset.begin(); iter != s_tileset.end(); iter++) {
    if(iter->second)
      SDL_FreeSurface(iter->second);
  }

  for(std::map<std::string, SDL_Surface*>::iterator iter = cache_image.begin(); iter != cache_image.end(); iter++) {
    if(iter->second)
      SDL_FreeSurface(iter->second);
  }
}

bool TmxRender::CargarDesdeArchivo(const char *archivo)
{
  SDL_Surface *tmp = NULL;
  tmx = new Tmx::Map();
  tmx->ParseFile(archivo);
  
  if(tmx->HasError()) {
    std::cerr << "Fallo cargar tmx:" << archivo << std::endl;
    std::cerr << "\tcodigo error:" << tmx->GetErrorCode() << std::endl;

    std::cerr << "\ttexto error:" << tmx->GetErrorText() << std::endl;

    return false;
  }
  
  for(int i=0; i < tmx->GetNumTilesets(); ++i) {
    const Tmx::Tileset *tileset = tmx->GetTileset(i); 
    //@todo data debe ser global
    std::string ruta = std::string("data/") + tileset->GetImage()->GetSource();
    if(tileset->GetProperties().HasProperty("alpha") && tileset->GetProperties().GetLiteralProperty("alpha") == "disable"){
      tmp = Compositor::obRecurso()->cargarImagen(ruta.c_str(), true);
    }else
      {
       tmp = Compositor::obRecurso()->cargarImagen(ruta.c_str(), false);
      }

    if(!tmp) {
      std::cerr << "Fallo leer imagen:" << ruta.c_str() << std::endl;
      return NULL;
    }
    std::cout << "Cargado tileset:" << ruta << " con Gid:" << tileset->GetFirstGid() <<std::endl;
    s_tileset[tileset->GetFirstGid()] = tmp;

    tmp = NULL;
  }


  return true;
}

void TmxRender::blit(const char * capa, SDL_Rect *srect, SDL_Surface *dest, SDL_Rect *drect, int alpha){
  
  blitTile(capa, srect, dest, drect, alpha);
  //blitImage(capa, srect, dest, drect, alpha);
}

/**
 *Renderiza o imprime un rectangulo desde un archivo TMX
 *a una superficie SDL, cuadro a cuadro
 *La idea general es:
 * * se crea imagen de tamano del rectangulo origen esperado
 * * se imprime en esta imagen la cantidad de tiles correspondieste
 * * se imprime a superficie de la imagen anterior desplazando para obtener peticion x,y
 */
void TmxRender::blitTile(const char * capa, SDL_Rect *srect, SDL_Surface *dest, SDL_Rect *drect, int alpha){
  SDL_Rect ssrect = *srect;
  int layer_alpha = SDL_ALPHA_OPAQUE;
  assert(srect != NULL);
  
  int scols = srect->w / tmx->GetTileWidth();
  int srows = srect->h / tmx->GetTileHeight();


  for(int i=0; i < tmx->GetNumLayers(); ++i) {
    const Tmx::Layer *layer = tmx->GetLayer(i);

    if(layer->GetName() != capa)
      continue;
    

    layer_alpha = SDL_ALPHA_OPAQUE * layer->GetOpacity();


    int sy = srect->y  / tmx->GetTileHeight();
    int sx = srect->x / tmx->GetTileWidth();
    //std::cerr << "scols:" << scols << " srows:" << srows << " sy:" << sy << " sx:" << sx << std::endl;

    for(int y = 0; y <= srows+1; ++y) {
      for(int x = 0; x <= scols+1; ++x) {
	int dx = x + sx; int dy = y + sy;

	int CurTile = layer->GetTileId(dx,dy);		
	if(CurTile == 0) {
	  continue;
	}
	//	const Tmx::MapTile& tile = layer->GetTile(dx,dy);
	
	int tilesetid = layer->GetTileTilesetIndex(dx,dy);
	//int tilesetid = tile.tilesetId;
	//std::cerr << "tilesetid:" << tilesetid << std::endl;
	//@todo esto no funciono
	const Tmx::Tileset *tileset = tmx->GetTileset(tilesetid);
	//const Tmx::Tileset *tileset = tmx->FindTileset(CurTile);	
	if(!tileset) continue;
	//std::cerr << "Tileid:" << CurTile << std::endl;
	//std::cerr << "dx:" << dx << " dy:" << dy << std::endl;
	SDL_Rect src,dst;
	int cols = tileset->GetImage()->GetWidth()/tileset->GetTileWidth();;
	int tileset_row = (CurTile / cols);
	int tileset_col = (CurTile % cols);

	src.x = (tileset->GetMargin() + (tileset->GetTileWidth() + tileset->GetSpacing()) * tileset_col);
	src.y = (tileset->GetMargin() + (tileset->GetTileHeight() + tileset->GetSpacing()) * tileset_row);
	src.w = tileset->GetTileWidth();
	src.h = tileset->GetTileHeight();
	dst.x = x * tileset->GetTileWidth() - srect->x % tmx->GetTileWidth();
	dst.y = y * tileset->GetTileHeight() - srect->y % tmx->GetTileHeight();
	dst.w = tileset->GetTileWidth();
	dst.h = tileset->GetTileHeight();

	if(drect) {
	  dst.x += drect->x;
	  dst.y += drect->y;
	}

	SDL_SetAlpha(s_tileset[tileset->GetFirstGid()], SDL_SRCALPHA, layer_alpha);
	SDL_BlitSurface(s_tileset[tileset->GetFirstGid()],&src, dest, &dst);
      }
    }
    break;
  }
  


}


void TmxRender::blitImage(const char * capa, SDL_Rect *srect, SDL_Surface *dest, SDL_Rect *drect, int alpha){
  SDL_Surface *imagen = NULL;
  std::string ncapa(capa);
  if(cache_image.count(ncapa)){
    imagen = cache_image[ncapa];
  }else{
    SDL_Surface *tmp = Compositor::obVideo()->createSurface(obAncho(), obAlto());
    imagen = SDL_DisplayFormat(tmp);
    SDL_FreeSurface(tmp);
    SDL_Rect ssrect = { 0, 0, obAncho(), obAlto()};
    blitTile(capa, &ssrect, imagen, NULL, alpha);
    cache_image[ncapa] = imagen;
  }
  SDL_BlitSurface(imagen, srect, dest, drect);
}
