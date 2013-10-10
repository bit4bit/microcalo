puts "Configuracion..."

Juego.conf.data_path = "data/"

Juego.conf.mapas = ["mapa1.tmx", "lateral1.tmx", "mapa1.tmx", "bosque.tmx"]

escena_intro = EscenarioGuion.new("intro")
escena_intro << [["texto", "hola mundo"],["pausa", "1"],["cambiar","menu"]]

escena_creditos = EscenarioGuion.new("creditos")
escena_creditos << [
                    ["texto", "los credito"]
                   ]

escena_menu = EscenarioMenu.new("menu")
w = RWidget.new(escena_menu, 10, 10)
escena_menu << w
Juego.gestor_escenarios << escena_intro
Juego.gestor_escenarios << escena_creditos 
Juego.gestor_escenarios << escena_menu


puts "fin conf"
