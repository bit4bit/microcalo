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
    SDL_Surface *tmp = Compositor::obRecurso()->cargarImagen(ruta.c_str());
    if(!tmp) {
      std::cerr << "Fallo leer imagen:" << ruta.c_str() << std::endl;
      return NULL;
    }

    s_tileset[tileset->GetFirstGid()] = tmp;
  }


  return true;
}

void TmxRender::blit(const char * capa, SDL_Rect *srect, SDL_Surface *dest, SDL_Rect *drect){
  blitTile(capa, srect, dest, drect);
  //blitImage(capa, srect, dest, drect);
}

/**
 *Renderiza o imprime un rectangulo desde un archivo TMX
 *a una superficie SDL, cuadro a cuadro
 *La idea general es:
 * * se crea imagen de tamano del rectangulo origen esperado
 * * se imprime en esta imagen la cantidad de tiles correspondieste
 * * se imprime a superficie de la imagen anterior desplazando para obtener peticion x,y
 */
void TmxRender::blitTile(const char * capa, SDL_Rect *srect, SDL_Surface *dest, SDL_Rect *drect){
  SDL_Rect ssrect = *srect;
  assert(srect != NULL);
  
  int scols = srect->w / tmx->GetTileWidth();
  int srows = srect->h / tmx->GetTileHeight();

  //imagen general
  SDL_Surface *tmp = Compositor::obVideo()->createSurface((scols + 1)*tmx->GetTileWidth() , (srows + 1) * tmx->GetTileHeight());
  SDL_Surface *imagen = SDL_DisplayFormat(tmp);
  SDL_FreeSurface(tmp);

  for(int i=0; i < tmx->GetNumLayers(); ++i) {
    const Tmx::Layer *layer = tmx->GetLayer(i);

    if(layer->GetName() != capa)
      continue;


    int sy = srect->y  / tmx->GetTileHeight();
    int sx = srect->x / tmx->GetTileWidth();
    //std::cerr << "scols:" << scols << " srows:" << srows << " sy:" << sy << " sx:" << sx << std::endl;

    for(int y = 0; y <= srows+1; ++y) {
      for(int x = 0; x <= scols+1; ++x) {
	int dx = x + sx; int dy = y + sy;

	int CurTile = layer->GetTileId(dx,dy);	
	const Tmx::Tileset *tileset = tmx->FindTileset(CurTile);

	
	if(CurTile == 0 || tileset == NULL) {
	  continue;
	}
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
	dst.x = x * tileset->GetTileWidth();
	dst.y = y * tileset->GetTileHeight();
	dst.w = tileset->GetTileWidth();
	dst.h = tileset->GetTileHeight();
	//std::cout << "dst x:" << dst.x << " .y:" << dst.y << " .w:" << dst.w << " .h:" << dst.h << std::endl;
	SDL_BlitSurface(s_tileset[tileset->GetFirstGid()],&src, imagen, &dst);
      }
    }
    break;
  }
  

  //ssrect.x= abs(ssrect.x - (srect->x / tmx->GetTileWidth()) * tmx->GetTileWidth());
  //ssrect.y= abs(ssrect.y - (srect->y / tmx->GetTileHeight()) * tmx->GetTileHeight());
  ssrect.x = srect->x % tmx->GetTileWidth();
  ssrect.y = srect->y % tmx->GetTileHeight();

  //std::cerr << "Ssrect.x:" << ssrect.x << " .y:" << ssrect.y << " .w:" << ssrect.w << " .h:" << ssrect.h << std::endl;
  //std::cerr << "Imagen .w: " << imagen->w << " .h" << imagen->h << std::endl;
  // SDL_BlitSurface(imagen, &ssrect, dest, drect);
  SDL_BlitSurface(imagen, &ssrect, dest, drect);
  SDL_FreeSurface(imagen);
}


void TmxRender::blitImage(const char * capa, SDL_Rect *srect, SDL_Surface *dest, SDL_Rect *drect){
  SDL_Surface *imagen = NULL;
  std::string ncapa(capa);
  if(cache_image.count(ncapa)){
    imagen = cache_image[ncapa];
  }else{
    SDL_Surface *tmp = Compositor::obVideo()->createSurface(obAncho(), obAlto());
    imagen = SDL_DisplayFormat(tmp);
    SDL_FreeSurface(tmp);
    SDL_Rect ssrect = { 0, 0, obAncho(), obAlto()};
    blitTile(capa, &ssrect, imagen, NULL);
    cache_image[ncapa] = imagen;
  }
  SDL_BlitSurface(imagen, srect, dest, drect);
}
