#Script para la creacion de los tipos de vehiculos
#al llamar +VehiculoTipo.new+ automaticamente se 
#agregar al gestor de vehiculos tipo

puts "Creando tipos vehiculos"

carro = VehiculoTipo.new("rapido")
carro.max_vel = 12;
carro.min_vel = -5;
carro.accel = 0.5;
carro.retro = -0.1
carro.giro = 1
carro.imagen = "data/carro1.png"
carro.imagen_columnas = 1
carro.imagen_der = "data/carroder.png"
carro.imagen_izq = "data/carroizq.png"
carro.audio_motor = "data/carro1_andando2.wav"
carro.ancho = 32
carro.alto = 32
