CC=g++
CFLAGS=`sdl-config --cflags` -lSDL_image `guile-config compile`
LIBS=`sdl-config --libs` -lSDL_gfx -lSDL_ttf -lSDL_gfx -lSDL_image `guile-config link` -lSGE 
CPPFLAGS=-Ivendor/tmx-parser-read-only `guile-config compile`
OBJECTS = mando.o jugador.o control_mando.o control_teclado.o punto_paso_gestor.o punto_paso.o colision.o objeto.o video.o audio.o reloj.o teclado.o recurso.o cosa.o escenario.o escenario_carrera.o vehiculo.o vehiculo_tipo.o camara.o main.o escenario_intro.o script.o texto.o

snarfcppopts = $(DEFS) $(INCLUDES) $(CPPFLAGS) $(CFLAGS)
.SUFFIXES: .x
.cpp.x:
	guile-snarf -o $ $< $(snarfcppopts)


microcalo: $(OBJECTS)  libtmxparser.a vehiculo.h
	$(CC) -ggdb -o $@ $(OBJECTS) vendor/tmx-parser-read-only/libtmxparser.a $(CFLAGS) $(LIBS)

libtmxparser.a:
	make -C vendor/tmx-parser-read-only -f Makefile.linux

clean:
	@rm *.o
	@rm microcalo