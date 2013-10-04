BASEDIR=.
CC=g++
CFLAGS=`sdl-config --cflags` -lSDL_image 
LIBS=`sdl-config --libs` -lSDL_gfx -lSDL_ttf -lSDL_gfx -lSDL_image -lSGE -lz
CPPFLAGS=-Ivendor/tinyxml-git -Ivendor/tmx-parser-read-only 
OBJECTS = mando.o jugador.o control_mando.o control_teclado.o punto_paso_gestor.o punto_paso.o colision.o objeto.o video.o audio.o reloj.o teclado.o recurso.o cosa.o escenario.o escenario_carrera.o vehiculo.o vehiculo_tipo.o camara.o main.o escenario_intro.o texto.o util.o tmx_render.o
OBJECTS_MRUBY=$(patsubst %.cpp,%.o,$(wildcard $(BASEDIR)/src/*.cpp))
CPPFLAGS_MRUBY=-I$(BASEDIR)/vendor/mruby/include
TINYXML_OBJECTS=vendor/tinyxml-git/tinyxml.o vendor/tinyxml-git/tinyxmlparser.o vendor/tinyxml-git/tinyxmlerror.o vendor/tinyxml-git/tinystr.o
snarfcppopts = $(DEFS) $(INCLUDES) $(CPPFLAGS) $(CFLAGS)
.SUFFIXES: .x
.cpp.x:
	guile-snarf -o $ $< $(snarfcppopts)


microcalo: $(OBJECTS) libtmxparser.a vehiculo.h mruby
	$(CC) -ggdb -o $@ $(OBJECTS) vendor/tmx-parser-read-only/libtmxparser.a $(TINYXML_OBJECTS) $(CFLAGS) $(CPPFLAGS_MRUBY) $(LIBS)


.PHONY : mruby
mruby: 
	$(MAKE) -C vendor/mruby

libtmxparser.a:
	make -C vendor/tinyxml-git -f Makefile
	make -C vendor/tmx-parser-read-only -f Makefile.linux

clean:
	@rm *.o
	@rm microcalo