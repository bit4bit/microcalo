CC=g++
CFLAGS=`sdl-config --cflags` -lSDL_image `guile-config compile` -Ivendor/tmx-parser-read-only
LIBS=`sdl-config --libs` -lSDL_gfx -lSDL_image -lboost_filesystem `guile-config link` -lSGE

OBJECTS = mando.o jugador.o control_mando.o control_teclado.o punto_paso_gestor.o punto_paso.o colision.o objeto.o video.o audio.o reloj.o teclado.o recurso.o cosa.o escenario.o escenario_carrera.o vehiculo.o vehiculo_tipo.o camara.o main.o



microcalo: $(OBJECTS) libtmxparser.a
	$(CC) -ggdb -o $@ $(OBJECTS) vendor/tmx-parser-read-only/libtmxparser.a $(CFLAGS) $(LIBS)

libtmxparser.a: 
	cd vendor/tmx-parser-read-only; make -f Makefile.linux

clean:
	@rm *.o
	@rm microcalo