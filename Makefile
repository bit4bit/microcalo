BASEDIR=.
CC=g++
CFLAGS=`sdl-config --cflags` -lSDL_image  -ggdb
CPPFLAGS_MRUBY=`sdl-config --cflags` -I$(BASEDIR)/vendor/ -I$(BASEDIR)/vendor/mruby/include -I$(BASEDIR)/vendor/mrubybind/  -Wall -g -O0
LIBS=`sdl-config --libs` -lSDL_mixer -lSDL_ttf -lSDL_image -lSGE -lz -lm -ggdb
CPPFLAGS=-Ivendor/tinyxml-git -Ivendor/tmx-parser-read-only $(CPPFLAGS_MRUBY) -Ivendor/vmath/src
OBJECTS = mando.o jugador.o control_mando.o control_teclado.o punto_paso_gestor.o punto_paso.o colision.o objeto.o video.o audio.o reloj.o teclado.o recurso.o cosa.o escenario.o escenario_carrera.o vehiculo.o vehiculo_tipo.o camara.o main.o escenario_guion.o texto.o util.o tmx_render.o configuracion.o script.o gestor_vehiculo_tipo.o gestor_escenario.o carray.o gui.o escenario_menu.o graficador.o  exportar_script.cpp
OBJECTS_MRUBY=$(shell find $(BASEDIR)/vendor/mruby/build/host -type f -name '*.a') $(BASEDIR)/mrubybind.o
SDL_GFX=SDL_gfxPrimitives.o SDL_imageFilter.o SDL_rotozoom.o SDL_gfxBlitFunc.o SDL_framerate.o
TINYXML_OBJECTS=vendor/tinyxml-git/tinyxml.o vendor/tinyxml-git/tinyxmlparser.o vendor/tinyxml-git/tinyxmlerror.o vendor/tinyxml-git/tinystr.o


microcalo: $(OBJECTS) libtmxparser.a vehiculo.h mruby mrubybind.o vmath.o 
	$(CC) -ggdb -O0 -o  $@ $(OBJECTS) vendor/tmx-parser-read-only/libtmxparser.a $(TINYXML_OBJECTS) $(CFLAGS) $(CPPFLAGS_MRUBY) $(LIBS) $(OBJECTS_MRUBY)  $(SDL_GFX)

.PHONY : mrubybind.o
mrubybind.o:
	$(CC)  -c -o $@ $(BASEDIR)/vendor/mrubybind/mrubybind.cc $(CPPFLAGS_MRUBY) $(OBJECTS_MRUBY) -ggdb

vmath.o:
	$(CC)  -c -o $@ $(BASEDIR)/vendor/vmath/src/vmath.cpp -lm

SDL_gfx2.o: 
	gcc -c  vendor/sdl-gfx/SDL_gfxPrimitives.c vendor/sdl-gfx/SDL_framerate.c vendor/sdl-gfx/SDL_gfxBlitFunc.c vendor/sdl-gfx/SDL_imageFilter.c vendor/sdl-gfx/SDL_rotozoom.c `sdl-config --cflags` 

.PHONY : mruby
mruby: 
	$(MAKE) -C vendor/mruby ENABLE_DEBUG=1 

libtmxparser.a:
	make -C vendor/tinyxml-git -f Makefile
	make -C vendor/tmx-parser-read-only -f Makefile.linux

clean:
	@rm *.o
	@rm microcalo