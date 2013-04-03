#ifndef COSA_H
#define COSA_H

#include <list>
#include <SDL/SDL.h>

/**
 *La cosa representa el objeto/entidad 
 *en el juego, todo lo que pueda ser actualizado y 
 *dibujado, como el vehiculo, el escenario, los items..etc.
 */
class Cosa
{
 public:
  Uint32 obId();

  virtual ~Cosa();
    
  virtual void actualizar();
  virtual void dibujar();

  
  virtual void agregar(Cosa*);
  virtual void remover(Cosa*);
  
  Uint32 obX() { return escenario_x; }
  Uint32 obY() { return escenario_y; }
 protected:
  Cosa(Uint32);

  Uint32 escenario_x;
  Uint32 escenario_y;
  Uint32 pantalla_x;
  Uint32 pantalla_y;
  
 private:
  Uint32 id;

};

#endif
