#include "tmx_render.h"
#include "compositor.h"
#include "TmxParser/Tmx.h"
#include <SDL/SDL.h>
#include <map>
#include <string>
#include <iostream>
#include <cstdlib>

TmxRender::TmxRender()
{
  tmx = NULL;
}

TmxRender::~TmxRender()
{
  if(tmx)
    delete tmx;
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


/**
 *Renderiza o imprime un rectangulo desde un archivo TMX
 *a una superficie SDL.
 *La idea general es:
 * * se crea imagen de tamano del rectangulo origen esperado
 * * se imprime en esta imagen la cantidad de tiles correspondieste
 * * se imprime a superficie de la imagen anterior desplazando para obtener peticion x,y
 */
void TmxRender::blit(const char * capa, SDL_Rect *srect, SDL_Surface *dest, SDL_Rect *drect){
  SDL_Rect ssrect = *srect;
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

    //VOY AQUI 
    //ESTOY PROBANDO COMO RENDERIZAR CORRECTAMENTE
    //NO FUNCIONA...
    //peticion de rectangulo de pixel se convierte a columnas y filas

    int sy = srect->y  / tmx->GetTileHeight();
    int sx = srect->x / tmx->GetTileWidth();
    //srows ++; scols ++;
    //se hace un offset desde *imagen ha superficie
    //final para sacar la porcion de la imagen pedida
    //ssrect.x -= (srect->x - (sx * tmx->GetTileWidth()));
    //ssrect.y -= (srect->y - (sy * tmx->GetTileHeight()));
    std::cerr << "scols:" << scols << " srows:" << srows << " sy:" << sy << " sx:" << sx << std::endl;
    /**
     *@todo hay un error, creo que es con TmxParser
     *no se lee el primer tile 
     */
    for(int y = 0; y <= srows; ++y) {
      for(int x = 0; x <= scols; ++x) {
	int dx = x + sx; int dy = y + sy;

	int CurTile = layer->GetTileId(dx,dy);	
	const Tmx::Tileset *tileset = tmx->FindTileset(CurTile);

	
	if(CurTile == 0 || tileset == NULL) {
	  continue;
	}
	//std::cerr << "Tileid:" << CurTile << std::endl;
	std::cerr << "dx:" << dx << " dy:" << dy << std::endl;
	SDL_Rect src,dst;
	int cols = tileset->GetImage()->GetWidth()/tileset->GetTileWidth();;
	int tileset_row = (CurTile / cols);
	int tileset_col = (CurTile % cols);

	src.x = (tileset->GetMargin() + (tileset->GetTileWidth() + tileset->GetSpacing()) * tileset_col);
	src.y = (tileset->GetMargin() + (tileset->GetTileHeight() + tileset->GetSpacing()) * tileset_row);
	src.w = tileset->GetTileWidth();
	src.h = tileset->GetTileHeight();
	std::cout << "Tileid:" << CurTile << " src x:" << src.x << " .y:" << src.y << " .w:" << src.w << " .h:" << src.h << std::endl;
	dst.x = x * tileset->GetTileWidth(); 
	dst.y = y * tileset->GetTileHeight();
	dst.w = tileset->GetTileWidth();
	dst.h = tileset->GetTileHeight();
	std::cout << "dst x:" << dst.x << " .y:" << dst.y << " .w:" << dst.w << " .h:" << dst.h << std::endl;
	SDL_BlitSurface(s_tileset[tileset->GetFirstGid()],&src, imagen, &dst);
      }
    }
    break;
  }
  

  ssrect.x= abs(ssrect.x - (srect->x / tmx->GetTileWidth()) * tmx->GetTileWidth());
  ssrect.y= abs(ssrect.y - (srect->y / tmx->GetTileHeight()) * tmx->GetTileHeight());

  std::cerr << "Ssrect.x:" << ssrect.x << " .y:" << ssrect.y << " .w:" << ssrect.w << " .h:" << ssrect.h << std::endl;
  std::cerr << "Imagen .w: " << imagen->w << " .h" << imagen->h << std::endl;
  // SDL_BlitSurface(imagen, &ssrect, dest, drect);
  SDL_BlitSurface(imagen, &ssrect, dest, drect);
  SDL_FreeSurface(imagen);
}
