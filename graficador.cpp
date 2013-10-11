#include "graficador.h"
#include <mrubybind.h>
#include <iostream>
#include "compositor.h"
#include <sdl-gfx/SDL_gfxPrimitives.h>

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

int Graficador::imprimirCuadro(int x, int y, int ancho, int alto, SDL_Color color, int alpha) {
  return boxRGBA(s, x, y, x + ancho, y + alto, color.r, color.g, color.b, alpha);
}

int Graficador::imprimirBorde(int x, int y, int ancho, int alto, SDL_Color color, int grosor, int alpha) {
  for(int i=0; i < grosor; ++i) {
    rectangleRGBA(s, x + i, y + i, x + ancho - i, y + alto - i, color.r, color.g, color.b, alpha);
  }
  return 0;
}

int Graficador::imprimirCuadroRedondo(int x, int y, int ancho, int alto, int rad,  SDL_Color color, int grosor, int alpha) {
  for(int i=0; i < grosor; ++i) {
    roundedBoxRGBA(s, x + i, y + i, x + ancho - i, y + alto - i, rad,  color.r, color.g, color.b, alpha);
  }
  return 0;
}

int Graficador::imprimirLinea(int x, int y, int x2, int y2, SDL_Color color, int ancho, int alpha) {
  return thickLineRGBA(s, x, y, x2, y2, ancho, color.r, color.g , color.b, alpha);
}

int Graficador::imprimirPoligono(std::vector<std::pair<int, int> >& puntos, SDL_Color color, bool rellenar, int alpha) {
  Sint16* xs = new Sint16[puntos.size()];
  Sint16* ys = new Sint16[puntos.size()];
  int c = 0;
  std::cout << "Dibujando poligonodo" << std::endl;
  for(std::vector<std::pair<int, int> >::iterator iter = puntos.begin(); iter != puntos.end(); ++iter) {
    xs[c] = (*iter).first;
    ys[c] = (*iter).second;
    std::cout << "Poligono(" << (*iter).first << "," << (*iter).second << ")" << std::endl;
    c++;
  }

  if(rellenar) {
    filledPolygonRGBA(s,xs, ys, puntos.size(), color.r, color.g, color.b, alpha);
  }else{
    aapolygonRGBA(s, xs, ys, puntos.size(), color.r, color.g, color.b, alpha);
  }
  delete xs;
  delete ys;
  return 0;
}

//BINDING
//INICIALIZA SDL_Color apartir de arreglo
#define RARY_TO_SDL_COLOR(ary) {mrb_fixnum(mrb_ary_ref(mrb, ary, 0)), \
		      mrb_fixnum(mrb_ary_ref(mrb, ary, 1)), \
		      mrb_fixnum(mrb_ary_ref(mrb, ary, 2)), \
		      0}

#define GRAFICADOR_PTR(obj) reinterpret_cast<Graficador*>(DATA_PTR(obj))
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

DEF_RFUNC(graficador_imprimir_cuadro) {
  mrb_int x,y,ancho,alto,alpha = 255;
  mrb_value rcolor;
  mrb_get_args(mrb, "iiiiA|i", &x, &y, &ancho, &alto, &rcolor, &alpha);
  SDL_Color color = RARY_TO_SDL_COLOR(rcolor);
  Graficador* ptr = GRAFICADOR_PTR(self);
  ptr->imprimirCuadro(x, y, ancho, alto, color, alpha);
  return self;
}

DEF_RFUNC(graficador_imprimir_borde) {
  mrb_int x,y,ancho,alto,alpha = 255, grosor = 1;
  mrb_value rcolor;
  mrb_get_args(mrb, "iiiiA|ii", &x, &y, &ancho, &alto, &rcolor, &grosor, &alpha);
  SDL_Color color = RARY_TO_SDL_COLOR(rcolor);
  Graficador* ptr = GRAFICADOR_PTR(self);
  ptr->imprimirBorde(x, y, ancho, alto, color, grosor, alpha);
  return self;
}

DEF_RFUNC(graficador_imprimir_cuadro_redondo) {
  mrb_int x,y,ancho,alto, rad, alpha = 255, grosor = 1;
  mrb_value rcolor;
  mrb_get_args(mrb, "iiiiiA|ii", &x, &y, &ancho, &alto, &rad, &rcolor, &grosor, &alpha);
  SDL_Color color = RARY_TO_SDL_COLOR(rcolor);
  Graficador* ptr = GRAFICADOR_PTR(self);
  ptr->imprimirCuadroRedondo(x, y, ancho, alto, rad, color, grosor, alpha);
}


DEF_RFUNC(graficador_imprimir_linea) {
  mrb_int x,y,x1,y1, alpha = 255,  ancho = 1;
  mrb_value rcolor;
  mrb_get_args(mrb, "iiiiA|ii", &x, &y, &x1, &y1, &rcolor, &ancho, &alpha);
  SDL_Color color = RARY_TO_SDL_COLOR(rcolor);
  Graficador* ptr = GRAFICADOR_PTR(self);
  ptr->imprimirLinea(x, y, x1, y1, color, ancho, alpha);
  return self;
}

DEF_RFUNC(graficador_imprimir_poligono) {
  mrb_int alpha = 255;
  mrb_value rpuntos, rcolor;
  mrb_bool rellenar;
  mrb_get_args(mrb, "AA|bi", &rpuntos, &rcolor, &rellenar, &alpha);
  SDL_Color color = RARY_TO_SDL_COLOR(rcolor);
  Graficador* ptr = GRAFICADOR_PTR(self);
  std::vector<std::pair<int, int> > puntos;
  std::pair<int, int> xy;
  for(int i = 0; i < mrb_ary_len(mrb, rpuntos); ++i) {
    mrb_value pair = mrb_ary_ref(mrb, rpuntos, i);
    int x = mrb_fixnum(mrb_ary_ref(mrb, pair, 0));
    int y = mrb_fixnum(mrb_ary_ref(mrb, pair, 1));
    xy = std::make_pair(x,y);
    puntos.push_back(xy);
  }

  ptr->imprimirPoligono(puntos, color, rellenar == TRUE ? true : false, alpha);

  return self;
}
void Graficador::bindingScript(mrb_state* mrb) {
  //graficador
  c_graficador = mrb_define_class(mrb, "Graficador", mrb->object_class);
  mrb_define_method(mrb, c_graficador, "initialize", graficador_new, MRB_ARGS_REQ(1));
  mrb_define_method(mrb, c_graficador, "imprimirTexto", graficador_imprimir_texto, MRB_ARGS_REQ(4));
  mrb_define_method(mrb, c_graficador, "imprimirCuadro", graficador_imprimir_cuadro, MRB_ARGS_REQ(5));
  mrb_define_method(mrb, c_graficador, "imprimirBorde", graficador_imprimir_borde, MRB_ARGS_REQ(5));
  mrb_define_method(mrb, c_graficador, "imprimirBordeRedondo", graficador_imprimir_cuadro_redondo, MRB_ARGS_REQ(5));
  mrb_define_method(mrb, c_graficador, "imprimirLinea", graficador_imprimir_linea, MRB_ARGS_REQ(5));
  mrb_define_method(mrb, c_graficador, "imprimirPoligono", graficador_imprimir_poligono, MRB_ARGS_REQ(2));
}
