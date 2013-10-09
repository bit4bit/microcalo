puts "Configuracion..."

Juego.conf.data_path = "data/"

Juego.conf.mapas = ["mapa1.tmx", "lateral1.tmx", "mapa1.tmx", "bosque.tmx"]

escena_intro = EscenarioGuion.new("intro")
escena_intro << [["texto", "hola mundo"],["pausa", "5"],["cambiar","carrera"]]

escena_creditos = EscenarioGuion.new("creditos")
escena_creditos << [
                    ["texto", "los credito"]
                   ]

Juego.gestor_escenarios.<< escena_intro
Juego.gestor_escenarios << escena_creditos 

puts "fin conf"
