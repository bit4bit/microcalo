#include "escenario_menu.h"

EscenarioMenu::EscenarioMenu() : Escenario(99) {
  s_fondo = NULL;
  SDL_Surface* t = Compositor::obVideo()->createSurface(Compositor::obVideo()->obAncho(), Compositor::obVideo()->obAlto());
  SDL_FillRect(t, NULL, 0);
  imagen = SDL_DisplayFormat(t);
  SDL_FreeSurface(t);
  graficador = new Graficador(imagen);
}

EscenarioMenu::~EscenarioMenu() {
  if(graficador)
    delete graficador;
  for(iter_widgets = widgets.begin(); iter_widgets != widgets.end(); ++iter_widgets) {
    if(!(*iter_widgets)->esObjetoRuby()){
      delete (*iter_widgets);
    }
  }
}

void EscenarioMenu::actualizar() {
  for(iter_widgets = widgets.begin(); iter_widgets != widgets.end(); ++iter_widgets) {
    (*iter_widgets)->actualizar();
  }
}

void EscenarioMenu::dibujar() {
  for(iter_widgets = widgets.begin(); iter_widgets != widgets.end(); ++iter_widgets) {
    (*iter_widgets)->dibujar();
  }
  Compositor::obVideo()->blit(imagen, NULL, NULL);
}

void EscenarioMenu::agregarWidget(RWidget* w) {
  widgets.push_back(w);
}

Graficador* EscenarioMenu::obGraficador() {
  return graficador;
}


//BINDING

static mrb_value escenario_menu_new(mrb_state* mrb, mrb_value self) {
  mrb_value key;

  EscenarioMenu* ptr = static_cast<EscenarioMenu*>(DATA_PTR(self));
  if(ptr)
    mrb_free(mrb, ptr);

  mrb_get_args(mrb, "S", &key);
  DATA_TYPE(self) = &escenario_menu_type;
  ptr = new EscenarioMenu();
  ptr->asignarNombre(mrb_str_to_cstr(mrb, key));
  ptr->comoObjetoRuby();
  DATA_PTR(self) = ptr;
  //mrb_singleton_class(mrb, self);
  mrb_gc_protect(mrb, self);
  return self;
}

static mrb_value escenario_menu_agregar(mrb_state* mrb, mrb_value self) {
  mrb_value obj;
  mrb_get_args(mrb, "o", &obj);
  EscenarioMenu* ptr = DATA_GET_PTR(mrb, self, &escenario_menu_type, EscenarioMenu);
  ptr->agregarWidget(static_cast<RWidget*>(DATA_PTR(obj)));
  return self;
}

void EscenarioMenu::bindingScript(mrb_state *mrb) {
  c_escenario_menu = mrb_define_class(mrb, "EscenarioMenu", mrb->object_class);
  MRB_SET_INSTANCE_TT(c_escenario_menu, MRB_TT_DATA);
  mrb_define_method(mrb, c_escenario_menu, "initialize", escenario_menu_new, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, c_escenario_menu, "agregar", escenario_menu_agregar, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, c_escenario_menu, "<<", escenario_menu_agregar, MRB_ARGS_REQ(1));
}
