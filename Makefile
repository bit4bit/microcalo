CC=g++
CFLAGS=`sdl-config --cflags` -lSDL_image `guile-config compile`
LIBS=`sdl-config --libs` -lSDL_gfx -lSDL_ttf -lSDL_gfx -lSDL_image `guile-config link` -lSGE -lz
CPPFLAGS=-Ivendor/tinyxml-git -Ivendor/tmx-parser-read-only `guile-config compile`
OBJECTS = mando.o jugador.o control_mando.o control_teclado.o punto_paso_gestor.o punto_paso.o colision.o objeto.o video.o audio.o reloj.o teclado.o recurso.o cosa.o escenario.o escenario_carrera.o vehiculo.o vehiculo_tipo.o camara.o main.o escenario_intro.o script.o texto.o util.o tmx_render.o
TINYXML_OBJECTS=vendor/tinyxml-git/tinyxml.o vendor/tinyxml-git/tinyxmlparser.o vendor/tinyxml-git/tinyxmlerror.o vendor/tinyxml-git/tinystr.o
snarfcppopts = $(DEFS) $(INCLUDES) $(CPPFLAGS) $(CFLAGS)
.SUFFIXES: .x
.cpp.x:
	guile-snarf -o $ $< $(snarfcppopts)


microcalo: $(OBJECTS) libtmxparser.a vehiculo.h
	$(CC) -ggdb -o $@ $(OBJECTS) vendor/tmx-parser-read-only/libtmxparser.a $(TINYXML_OBJECTS) $(CFLAGS) $(LIBS)

libtmxparser.a:
	make -C vendor/tinyxml-git -f Makefile
	make -C vendor/tmx-parser-read-only -f Makefile.linux

clean:
	@rm *.o
	@rm microcalo