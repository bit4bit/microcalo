CC=g++
CFLAGS=`sdl-config --cflags` -lSDL_image
LIBS=`sdl-config --libs` -lSDL_image

OBJECTS = video.o audio.o reloj.o teclado.o recurso.o cosa.o escenario.o escenario_carrera.o vehiculo.o camara.o main.o

microcalo: $(OBJECTS)
	$(CC) -ggdb -o $@ $(OBJECTS) $(CFLAGS) $(LIBS)

clean:
	@rm *.o
	@rm microcalo