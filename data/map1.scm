(define-module (map1))
(define-public nombre "mapa 1")
(define-public descripcion "primer mapa de prueba")
(define-public tmx "map1.tmx") ;ruta de como dibujar mapa y otros
(define-public musica-fondo "map1fondo.ogg")




(define-public vehiculos '(
			   (
			    (tipo carro) ;camion,bote,helicopetro mirar tipos de vehicuol
			    (id 1)
			    (posicion 100 100)
			    )
			   (
			    (tipo carro)
			    (id 2)
			    (posicion 100 200)
			    )
			   ;lo mismo para la cantidad de vehiculos que pueden
					;jugar en el escenario
			   
			   )
  )

;;ejemplo de agregar objetos al escenario
;;se cpuede hacer un lector de archivos tmx
;;y cree esto

(define-public objetos '(
			 (
			  (id automatico)
			  (imagen "obj1.png")
			  (posicion 800 900)
			  (colision-circular ;tipo de colision
			   (150, 150, 10) ;x,y,radio colision
			   (150, 210, 10) ;x,y,radio colision
			   )
			  (animacion
			   (imagen "obj1m.png")
			   (espera 1) ;en tickes
			   (imagen "obj2m.png")
			   (reinicia)
			   )
			  )

			 )
)