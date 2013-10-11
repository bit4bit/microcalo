#include "gui.h"
#include "escenario_menu.h"
#include "compositor.h"
#include "graficador.h"

RWidget::RWidget(int _x, int _y, int _ancho, int _alto): 
										  x(_x),
										  y(_y),
										  ancho(_ancho),
										  alto(_alto)
										  

{
  robj = mrb_nil_value();
  SDL_Surface* tmp = Compositor::obVideo()->createSurface(ancho, alto);
  s = SDL_DisplayFormat(tmp);
  SDL_FreeSurface(tmp);
  graficador = new Graficador(s);
}

RWidget::~RWidget() {
  SDL_FreeSurface(s);
  delete graficador;
}

//se llama cuando se activa el widget o bien se da click en el
void RWidget::actualizarActivo() {
  mrb_state* mrb = Compositor::obScript()->obState();

  mrb_sym id_cb_activo = mrb_intern(mrb, "cb_activo");
  if(mrb_respond_to(mrb, robj, id_cb_activo) == TRUE) {
    Uint8* keys = Compositor::obTeclado()->obTeclas();
    mrb_value rkeys = mrb_ary_new(mrb);

    for(int i = 0; i < SDLK_LAST; ++i) {
      mrb_ary_set(mrb, rkeys, i, mrb_fixnum_value(keys[i]));
    }
    mrb_funcall(mrb, robj, "cb_activo", 1, rkeys);
  }
}

void RWidget::actualizar() {
  mrb_state* mrb = Compositor::obScript()->obState();
  if(mrb_nil_p(robj)) return;
  if(mrb_respond_to(mrb, robj, mrb_intern_cstr(mrb, "actualizar")) == FALSE)
    return;

  int ai = mrb_gc_arena_save(mrb);
  mrb_value ret = mrb_funcall(mrb, robj, "actualizar", 0);
  int mx, my;
  int button = SDL_GetMouseState(&mx, &my);
  mrb_sym id_cb_raton = mrb_intern(mrb, "cb_raton");
  if(mx > x && mx < x + ancho && my > y && my < y+alto) {
    if(mrb_respond_to(mrb, robj, id_cb_raton) == TRUE) {
      mrb_funcall(mrb, robj, "cb_raton", 3, mrb_fixnum_value(mx - x), mrb_fixnum_value(my - y), mrb_fixnum_value(button));
    }
  }
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
  mrb_int ry, ancho, alto;
  mrb_value sobj = mrb_nil_value();
  mrb_get_args(mrb, "oiiii|o", &rmenu, &rx, &ry, &ancho, &alto, &sobj);


  RWidget* ptr = reinterpret_cast<RWidget*>(DATA_PTR(self));
  if(ptr)
    mrb_free(mrb, ptr);
  DATA_TYPE(self) = &rwidget_type;
  EscenarioMenu* m = reinterpret_cast<EscenarioMenu*>(DATA_PTR(rmenu));
  ptr = new RWidget(rx, ry, ancho, alto);
  DATA_PTR(self) = ptr;
  if(mrb_nil_p(sobj) == FALSE) ptr->asignarRObjeto(sobj);
  else  ptr->asignarRObjeto(self);
  ptr->comoObjetoRuby();


  //CREA OBJETO GRAFICADOR Y SE ASIGNA PTR
  RClass* graficador = (RClass*)mrb_obj_alloc(mrb, MRB_TT_CLASS, c_graficador);
  mrb_value og = mrb_obj_value(graficador);
  DATA_PTR(og) = ptr->obGraficador();
  mrb_iv_set(mrb, self, mrb_intern(mrb, "@menu"), rmenu);
  mrb_iv_set(mrb, self, mrb_intern(mrb, "@graficador"), og);
  mrb_iv_set(mrb, self, mrb_intern(mrb, "@x"), mrb_fixnum_value(rx));
  mrb_iv_set(mrb, self, mrb_intern(mrb, "@y"), mrb_fixnum_value(ry));

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
