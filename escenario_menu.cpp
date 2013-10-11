#include "escenario_menu.h"

EscenarioMenu::EscenarioMenu() : Escenario(99) {
  s_fondo = NULL;
  SDL_Surface* t = Compositor::obVideo()->createSurface(Compositor::obVideo()->obAncho(), Compositor::obVideo()->obAlto());
  SDL_FillRect(t, NULL, 0);
  imagen = SDL_DisplayFormatAlpha(t);
  SDL_FreeSurface(t);
  graficador = new Graficador(imagen);
  widget_activo = NULL;
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
  if(widget_activo != NULL) {
    widget_activo->actualizarActivo();
  }
  for(iter_widgets = widgets.begin(); iter_widgets != widgets.end(); ++iter_widgets) {
    (*iter_widgets)->actualizar();
    int mx, my;
    int button = SDL_GetMouseState(&mx, &my);
    if(mx > (*iter_widgets)->x && mx < (*iter_widgets)->x + (*iter_widgets)->obAncho() && my > (*iter_widgets)->y && my < (*iter_widgets)->y +  (*iter_widgets)->obAlto() && SDL_BUTTON(1)){

      widget_activo = (*iter_widgets);														  }

}
}

void EscenarioMenu::dibujar() {
  SDL_FillRect(imagen, NULL, 0);
  for(iter_widgets = widgets.begin(); iter_widgets != widgets.end(); ++iter_widgets) {
    (*iter_widgets)->dibujar();

    if((*iter_widgets)->obGraficador()) {
      SDL_Rect p = {(*iter_widgets)->x, (*iter_widgets)->y, 0, 0};
      SDL_BlitSurface((*iter_widgets)->obGraficador()->obSurface(), NULL, imagen, &p);
      //Compositor::obVideo()->blit((*iter_widgets)->obGraficador()->obSurface(), NULL, &p);
    }
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
