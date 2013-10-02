(define escenario-intro '(
			  (texto "video juego similar micro-machines")
			  (pausa "2")
			  (imagen "data/logo.png")
			  (pausa "10")
			  )
  )

(define escenario-creditos '(
			     (texto "desarrollador bit4bit")
			     (pausa "2")
			     (texto "2013")
			     )
  )

(define escenarios '(
		     (escenario "escenarios/ciudad.scm")
		     )
 )

(define vehiculos '(
		    (
		     (id 3)
		     (tipo 'carro')
		     (imagen "data/carro.xpm" 1 1)
		     (animacion-andando (1))
		     )
		    )
  )