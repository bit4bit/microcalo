class Configuracion

  def self.instance
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
        end
      end
    end
  end
  private :new
end

#Clase que contiene acceso
#a clases de juego
class Juego

  #Configuracion por claves
  def self.conf
    Configuracion.instance
  end
  
end
