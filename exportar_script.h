#ifndef EXPORTAR_SCRIPT_H
#define EXPORTAR_SCRIPT_H

#include <mruby.h>
#include "bindingscript.h"

#define DEF_RFUNC(n) static mrb_value n(mrb_state* mrb, mrb_value self)

class ExportarScript
{
 public:


  virtual  bool esObjetoRuby() { return es_objeto_ruby; }
  virtual void comoObjetoRuby() { es_objeto_ruby = true; }
 protected:
  bool es_objeto_ruby;
};

extern void exportar_script_free(mrb_state *mrb, void *d);
extern void exportar_script_free_null(mrb_state *mrb, void* data);
extern mrb_data_type escenario_menu_type;
extern mrb_data_type rwidget_type;
extern mrb_data_type graficador_type;
extern mrb_data_type escenario_guion_type;
extern mrb_data_type juego_type;

extern RClass* c_escenario_menu;
extern RClass* c_rwidget;
extern RClass* c_graficador;
extern RClass* c_escenario_guion;
extern RClass* c_juego;
#endif
