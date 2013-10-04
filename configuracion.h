#ifndef CONFIGURACION_H
#define CONFIGURACION_H

#include <string>
#include <map>
#include <mruby.h>

class Configuracion
{
 protected:
  Configuracion();

 public:
  static void bindingScript(mrb_state *);
  static Configuracion* instancia();
  void asignarLiteral(std::string, std::string);
  void asignarEntero(std::string, int);
  void asignarFlotante(std::string, float);

  const char *obtenerLiteral(std::string);
  int obtenerEntero(std::string);
  float obtenerFlotante(std::string);
  
 private:
  static Configuracion *_self;

  std::map<std::string, std::string> confLiteral;
  std::map<std::string, int> confEntero;
  std::map<std::string, float> confFlotante;
};

#endif
