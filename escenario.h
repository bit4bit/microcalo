#ifndef ESCENARIO_H
#define ESCENARIO_H

#include <SDL/SDL.h>
#include <list>
#include <string>
#include "cosa.h"
#include "exportar_script.h"

#define ID_ESCENARIO_CARRERA 1
#define ID_ESCENARIO_INTRO 2
/**
 *El escenario representa el mapa
 *la camara, el espacio donde se desplazan los vehiculos
 *en pocas palabras toda la logica del juego actual.
 */
class Escenario : public Cosa, public ExportarScript
{
 public:
  virtual ~Escenario();

  virtual void actualizar();
  virtual void dibujar();

  void agregar(Cosa*);
  void remover(Cosa*);
  void asignarNombre(std::string);
  const std::string& obNombre();

 protected:
  Escenario(Uint32 _id);

 private:
  std::list<Cosa*> cosas;
  std::string _nombre;
  bool es_objeto_ruby;
};

#endif
