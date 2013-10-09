#ifndef EXPORTAR_SCRIPT_H
#define EXPORTAR_SCRIPT_H

#include <mruby.h>
#include "bindingscript.h"
class ExportarScript
{
 public:


  virtual  bool esObjetoRuby() { return es_objeto_ruby; }
  virtual void comoObjetoRuby() { es_objeto_ruby = true; }
 protected:
  bool es_objeto_ruby;
};

#endif
