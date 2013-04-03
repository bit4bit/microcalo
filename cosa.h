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
  

 protected:
  Cosa(Uint32);

 private:
  Uint32 id;

};

#endif
