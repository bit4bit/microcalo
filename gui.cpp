#include "gui.h"
#include "escenario_menu.h"
#include "compositor.h"

RWidget::RWidget(Graficador* _graficador, int _x, int _y): graficador(_graficador),
										x(_x),
										y(_y)

{
  robj = mrb_nil_value();
}

void RWidget::actualizar() {
  mrb_state* mrb = Compositor::obScript()->obState();
  if(mrb_nil_p(robj)) return;
  if(mrb_respond_to(mrb, robj, mrb_intern_cstr(mrb, "actualizar")) == FALSE)
    return;

  int ai = mrb_gc_arena_save(mrb);
  mrb_value ret = mrb_funcall(mrb, robj, "actualizar", 0);
  mrb_gc_arena_restore(mrb, ai);
}

void RWidget::dibujar() {
  mrb_state* mrb = Compositor::obScript()->obState();
  if(mrb_nil_p(robj)) return;
  if(mrb_respond_to(mrb, robj, mrb_intern_cstr(mrb, "dibujar")) == FALSE)
    return;

  int ai = mrb_gc_arena_save(mrb);
  mrb_value ret = mrb_funcall(Compositor::obScript()->obState(), robj, "dibujar", 0);
  mrb_gc_arena_restore(mrb, ai);
}



//binding




DEF_RFUNC(rwidget_new) {
  mrb_value rmenu;
  mrb_int rx;
  mrb_int ry;
  mrb_get_args(mrb, "oii", &rmenu, &rx, &ry);

  RWidget* ptr = reinterpret_cast<RWidget*>(DATA_PTR(self));
  if(ptr)
    mrb_free(mrb, ptr);
  DATA_TYPE(self) = &rwidget_type;
  EscenarioMenu* m = static_cast<EscenarioMenu*>(DATA_PTR(rmenu));
  ptr = new RWidget(m->obGraficador(), rx, ry);
  DATA_PTR(self) = ptr;
  ptr->asignarRObjeto(self);
  ptr->comoObjetoRuby();




  RClass* graficador = (RClass*)mrb_obj_alloc(mrb, MRB_TT_CLASS, c_graficador);
  mrb_value og = mrb_obj_value(graficador);
  DATA_PTR(og) = ptr->obGraficador();
  mrb_iv_set(mrb, self, mrb_intern(mrb, "@graficador"), og);

  return self;
}

DEF_RFUNC(rwidget_graficador) {
  return mrb_iv_get(mrb, self, mrb_intern(mrb, "graficador"));
}

void RWidget::bindingScript(mrb_state* mrb) {
  c_rwidget = mrb_define_class(mrb, "RWidget", mrb->object_class);
  MRB_SET_INSTANCE_TT(c_rwidget, MRB_TT_DATA);
  mrb_define_method(mrb, c_rwidget, "initialize", rwidget_new, MRB_ARGS_REQ(3));
  mrb_define_method(mrb, c_rwidget, "graficador", rwidget_graficador, MRB_ARGS_NONE());
}
