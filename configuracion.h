#ifndef CONFIGURACION_H
#define CONFIGURACION_H

#include <string>
#include <map>
#include <mruby.h>
#include "carray.h"
#include "exportar_script.h"

class Configuracion: public ExportarScript
{
 protected:
  Configuracion();

 public:
  ~Configuracion();

  static void bindingScript(mrb_state *);
  static Configuracion* instancia();
  static void cerrar();

  void asignarLiteral(std::string, std::string);
  void asignarEntero(std::string, int);
  void asignarFlotante(std::string, float);
  void asignarArregloCadena(std::string, std::string);
  CArrayString* crearArregloCadena();
  std::string obtenerLiteral(std::string);
  int obtenerEntero(std::string);
  float obtenerFlotante(std::string);
  CArrayString* obtenerArregloCadena(std::string);
  std::string obtenerArregloCadenaR(std::string);
  typedef std::map<std::string, CArrayString*> TipoConfArreglo;
 private:
  static Configuracion *_self;

  std::map<std::string, std::string> confLiteral;
  std::map<std::string, int> confEntero;
  std::map<std::string, float> confFlotante;
  std::map<std::string, CArrayString*> confArreglo;
  std::map<std::string, CArrayString*>::iterator iter_confArreglo;
  
};

#endif
