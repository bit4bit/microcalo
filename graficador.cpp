#include "graficador.h"
#include <mrubybind.h>
#include <iostream>
#include "compositor.h"

Graficador::Graficador(SDL_Surface* _s) : s(_s) 
{
}

void Graficador::imprimirTexto(int x, int y, std::string texto, int tamano, SDL_Color color) { 
  SDL_Surface *stxt = Compositor::obTexto()->renderTextSolid(texto.c_str(), color);
  SDL_Rect p = {x, y, stxt->w, stxt->h};
  SDL_BlitSurface(stxt, NULL, s, &p);

}

void Graficador::imprimirImagen(int x, int y, std::string ruta) {
}

void Graficador::imprimirRecuadro(int x, int y, int ancho, int alto, SDL_Color color) {

}

void Graficador::imprimirBorde(int x, int y, int ancho, int alto, int grosor, SDL_Color color) {
}

//BINDING
//INICIALIZA SDL_Color apartir de arreglo
#define RARY_TO_SDL_COLOR(ary) {mrb_fixnum(mrb_ary_ref(mrb, ary, 0)), \
		      mrb_fixnum(mrb_ary_ref(mrb, ary, 1)), \
		      mrb_fixnum(mrb_ary_ref(mrb, ary, 2)), \
		      0}

DEF_RFUNC(graficador_new) {
  mrb_value surface;
  mrb_get_args(mrb, "o", &surface);
  void* p = DATA_PTR(self);
  if(p) mrb_free(mrb, p);
  Graficador* ptr = new Graficador(reinterpret_cast<SDL_Surface*>(mrb_obj_ptr(surface)));
  DATA_TYPE(self) = &graficador_type;
  DATA_PTR(self) = ptr;
  return self;
}



DEF_RFUNC(graficador_imprimir_texto) {
  mrb_int x,y,tamano;
  mrb_value rtexto;
  mrb_value rcolor;
  mrb_get_args(mrb, "iiSiA", &x, &y, &rtexto, &tamano, &rcolor);
  Graficador* ptr = reinterpret_cast<Graficador*>(DATA_PTR(self));
  SDL_Color color =  RARY_TO_SDL_COLOR(rcolor);
  ptr->imprimirTexto(x, y, mrb_str_to_cstr(mrb, rtexto), tamano, color);
  return self;
}



void Graficador::bindingScript(mrb_state* mrb) {
  //graficador
  c_graficador = mrb_define_class(mrb, "Graficador", mrb->object_class);
  mrb_define_method(mrb, c_graficador, "initialize", graficador_new, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, c_graficador, "imprimirTexto", graficador_imprimir_texto, MRB_ARGS_REQ(4));
}
