#Script para la creacion de los tipos de vehiculos
#al llamar +VehiculoTipo.new+ automaticamente se 
#agregar al gestor de vehiculos tipo

puts "Creando tipos vehiculos"

carro = VehiculoTipo.new("rapido")
carro.max_vel = 20;
carro.imagen = "data/rapido.png"
carro.ancho = 32
carro.alto = 32
