#include "vehiculo_tipo.h"
#include "compositor.h"
#include <mrubybind.h>

VehiculoTipo::VehiculoTipo()
{
  //@todo esto no debe quedar aqui
  //por ahora, hay que crear tipos de vehiculos
  nombre.assign("notipo");
  ancho = 32;
  alto = 32;
  max_vel = 15;
  min_vel = -10;
  def_accel = 1;
  def_retro = 5;
  def_giro = 4; //cantidad de grados de la imagen
  def_giro_frenando = 7;
  
  s_vehiculo = NULL;
  s_vehiculo_columnas = 1;
  s_vehiculo_der = NULL;
  s_vehiculo_izq = NULL;
  audio_motor = NULL;
}
 
void VehiculoTipo::asignarSVehiculoDesdeArchivo(std::string ruta) 
{
  s_vehiculo = Compositor::obRecurso()->cargarImagen(ruta.c_str(), true);
}

void VehiculoTipo::asignarSVehiculoDerDesdeArchivo(std::string ruta) 
{
  s_vehiculo_der = Compositor::obRecurso()->cargarImagen(ruta.c_str(), true);
}

void VehiculoTipo::asignarSVehiculoIzqDesdeArchivo(std::string ruta) 
{
  s_vehiculo_izq = Compositor::obRecurso()->cargarImagen(ruta.c_str(), true);
}

static VehiculoTipo* vehiculo_tipo_new(std::string nombre)
{
  VehiculoTipo *vt =  Compositor::obGestorVehiculoTipo()->crear(nombre);
  std::cout << nombre <<std::endl;
  return vt;
}

void VehiculoTipo::bindingScript(mrb_state *mrb) 
{
  mrubybind::MrubyBind b(mrb);
  b.bind_class("VehiculoTipo", vehiculo_tipo_new);
  
  b.bind_instance_method("VehiculoTipo", "nombre", &VehiculoTipo::obNombre);
  b.bind_instance_method("VehiculoTipo", "nombre=", &VehiculoTipo::asignarNombre);
  b.bind_instance_method("VehiculoTipo", "ancho", &VehiculoTipo::obAncho);
  b.bind_instance_method("VehiculoTipo", "ancho=", &VehiculoTipo::asignarAncho);
  
  b.bind_instance_method("VehiculoTipo", "alto", &VehiculoTipo::obAlto);
  b.bind_instance_method("VehiculoTipo", "alto=", &VehiculoTipo::asignarAlto);

  b.bind_instance_method("VehiculoTipo", "max_vel", &VehiculoTipo::obMaxVel);
  b.bind_instance_method("VehiculoTipo", "max_vel=", &VehiculoTipo::asignarMaxVel);

  b.bind_instance_method("VehiculoTipo", "min_vel", &VehiculoTipo::obMinVel);
  b.bind_instance_method("VehiculoTipo", "min_vel=", &VehiculoTipo::asignarMinVel);

  b.bind_instance_method("VehiculoTipo", "accel", &VehiculoTipo::obDefAccel);
  b.bind_instance_method("VehiculoTipo", "accel=", &VehiculoTipo::asignarDefAccel);

  b.bind_instance_method("VehiculoTipo", "retro", &VehiculoTipo::obDefRetro);
  b.bind_instance_method("VehiculoTipo", "retro=", &VehiculoTipo::asignarDefRetro);

  b.bind_instance_method("VehiculoTipo", "giro", &VehiculoTipo::obDefGiro);
  b.bind_instance_method("VehiculoTipo", "giro=", &VehiculoTipo::asignarDefGiro);

  b.bind_instance_method("VehiculoTipo", "imagen=", &VehiculoTipo::asignarSVehiculoDesdeArchivo);
  b.bind_instance_method("VehiculoTipo", "imagen_columnas=", &VehiculoTipo::asignarSVehiculoColumnas);
  b.bind_instance_method("VehiculoTipo", "imagen_der=", &VehiculoTipo::asignarSVehiculoDerDesdeArchivo);
  b.bind_instance_method("VehiculoTipo", "imagen_izq=", &VehiculoTipo::asignarSVehiculoIzqDesdeArchivo);
  b.bind_instance_method("VehiculoTipo", "audio_motor=", &VehiculoTipo::asignarAudioMotor);
}









