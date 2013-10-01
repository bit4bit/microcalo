#include "vehiculo_tipo.h"
#include "compositor.h"

VehiculoTipo::VehiculoTipo()
{
  //@todo esto no debe quedar aqui
  //por ahora, hay que crear tipos de vehiculos
  nombre.assign("Generico");
  ancho = 32;
  alto = 32;
  max_vel = 15;
  min_vel = -10;
  def_accel = 1;
  def_retro = 5;
  def_giro = 4; //cantidad de grados de la imagen
  def_giro_frenando = 7;

  s_andando = Compositor::obRecurso()->cargarImagen("./data/carro.xpm");
  s_cayendo = Compositor::obRecurso()->cargarImagen("./data/car1.png");
  s_saltando = Compositor::obRecurso()->cargarImagen("./data/car1.png");
}
  
