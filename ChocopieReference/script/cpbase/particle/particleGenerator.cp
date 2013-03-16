
class ParticleGenerator < GameObject
    attr_accessor :x,:y
    attr_accessor :sx,:sy
    attr_accessor :color
    attr_accessor :activity
    attr_accessor :lifeTime
    attr_accessor :speed
            
    attr_reader :z

    def initialize(x=0,y=0,z = Z_OBJECT)
        super(x,y,nil)

        @layer = Layer.new(z)

        @z = z
        @sx = @sy = 0
        @color = Color.White
        @activity = 100
    end
    def dispose
        @layer.dispose
    end

    def add(p)
        @layer.add(p)
    end
    def delete(p)
        @layer.delete(p)
    end
    def size
        @layer.size
    end

    def generate
        p = Particle.new(self)
        p.x = @x
        p.y = @y
        p.angle = 0
        p.angleDirection = rand(360)
        add p
    end

    def update
        @x += @sx
        @y += @sy

        if rand(100) < @activity
            generate
        end
    end
end