#include "colision_mapa.h"
#include "TmxParser/Tmx.h"
#include "<SDL/SDL.h>"
#include <map>



ColisionMapa::ColisionMapa() {
  memset(colmap, 0, sizeof(colmap));
}

ColisionMapa::~ColisionMapa() {
  
}

/**
 *Crea mapa colision apartir de capa de archivo tmx
 *@param const char* capa nombre de la capa
 *@param Tmx::Map* tmx precargaddo tmx
 *@param std::map* mapeo relacion BLOQUEO_NINGUNO, BLOQUEO_TODO  a valor de atributo "tipo"
 */
void ColisionMapa::asignarMapaDesdeCapaTmx(const char *capa, Tmx::Map *tmx,const std::map<int,std::string> *mapeo) {
}

void ColisionMapa::asignarMapa(int _colmapa[255][255], int ancho, int alto){
  for(int i=0; i < ancho; i++)
    for(int j=0; j < alto; j++)
      colmap[i][j] = _colmap[i][j];
}

/**
 *Actualiza x,y en base al angulo y velocidad
 *@return bool true si se pudo mover de lo contrario false
 */
bool ColisionMapa::moverVehiculo(int &x, int &y, double vel, double angle){
}

bool ColisionMapa::mover(int &x, int &y, int paso_x, int paso_y){
}
