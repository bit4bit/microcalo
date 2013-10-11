class Configuracion

  def self.instancia
    @instance ||= new
  end
  
  def method_missing(name, *args, &block)
    @claves = Hash.new if @claves.nil?
    if name.to_s[name.to_s.length-1] == "="
      name = name.to_s.sub("=","")
      case args.first
      when Fixnum
        asignarEntero name.to_s, args.first
        @claves[name] = :fixnum
      when Float
        asignarFlotante name.to_s, args.first
        @claves[name] = :float
      when String
        asignarLiteral name.to_s, args.first
        @claves[name] = :string
      when Array
        args.first.each do |v|
          asignarArregloCadena name.to_s, v
        end

        @claves[name] = :array
      end
    else
      name = name.to_s
      if @claves.key?(name)
        case @claves[name]
        when :fixnum
          obtenerEntero name
        when :float
          obtenerFlotante name
        when :string
          obtenerLiteral name
        when :array
          obtenerArregloCadena(name).split(",")

        end
      end
    end
  end
  private :new
end


class GestorEscenario
  def self.instancia
    @instance ||= new
  end
  private :new
end

#Clase que contiene acceso
#a clases de juego
class Juego

  #Configuracion por claves
  def self.conf
    Configuracion.instancia
  end
  
  def self.gestor_escenarios
    GestorEscenario.instancia
  end
end


#EscenarioGuion
#Se crean escenarios para presentacion y creditos, o acerca
#esta es creada en clase C++ -EscenarioGuion-
class EscenarioGuion
  def <<(comandos)
    raise ArgumentError, "Se espera arreglo de arreglos [tipo, data]" unless comandos.kind_of?(Array)
    comandos.each do |comando|
      raise RuntimeError, "Comando invalido:" + comando.first.to_s + " se espera tupla." if comando.size != 2
      agregarComando(comando.first, comando.last)
    end
 end
end

#Funciones utiles de graficado
#para EscenarioMenu
=begin
class Graficador
  #Imprime texdo en +x+ y +y+ con +texto+ de +tamano+ y +color+ el
  #+color+ es un arreglo de +[R,G,B]+ donde R,G,B va de 0 a 255
  @graficador.imprimirTexto x,y, texto, tamano, color
  
  
  @graficador.imprimirCuadro x,y,ancho,alto,color,alpha=255
  
  @graficador.imprimirBorde x,y,ancho,alto,color,alpha=255

  @graficador.imprimirBordeRedondo x,y,ancho,alto,radio,color,alpha=255
  @graficador.imprimirLinea x,y,ancho,alto,color,grosor,alpha=255

  #+rellenar+ es boleano
  @graficador.imprimirPoligono [
                                [x1, y1],
                                [x2, y2],
                                [x3, y3],
                                .......
                               ], color, rellenar, alpha=255
end
=end

#RWidget
#Wdiget para escenario menu
#Cada RWidget tiene su propia superfice
class RWidget
  #Attributo +graficador+ herramientas de dibujado en la superficie
  #@graficador

  #Crea RWidget para el escenario_menu
  #def initialize(escenario_menu, x,y,ancho,alto)
  #end
  def actualizar

  end

  def dibujar
    @graficador.imprimirCuadro 0, 0, 300, 300, [255, 0,0]
  end

  def cb_activo(teclas)
  end
  

  def cb_raton(x,y,boton)
    #puts "raton relativo a widget:" + x.to_s + "," + y.to_s + " boton:" + boton.to_s
  end
  
  def cb_teclado(tecla)
  end
  
end


class Boton < RWidget
  def initialize(menu, x, y, texto)
    super(menu, x, y, 100, 30)
    @texto = texto

  end
  
  def actualizar
  end
  
  def dibujar
    @graficador.imprimirCuadro 0, 0, 100, 30, [255, 0,0]
    @graficador.imprimirTexto 30, 0, @texto, 10, [255,255,255]
  end
  
  def cb_activo(teclas)
  end
  
  def cb_raton(x, y, boton)
    if boton
      Juego.salir
    end
    
  end
  
end

class BotonSalir < RWidget
  def initialize(menu, x, y)
    super(menu, x, y, 100, 30)
    @texto = "SALIR"
  end
  
  def actualizar
  end
  
  def dibujar
    @graficador.imprimirCuadro 0, 0, 100, 30, [255, 0,0]
    @graficador.imprimirTexto 30, 0, @texto, 10, [255,255,255]
  end

  def cb_raton(x, y, boton)
    Juego.salir if boton > 0
  end
  
end
