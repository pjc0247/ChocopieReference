Debug.protect("Particle - 리소스 로드 실패") do
    $_particleBlue    = Sprite.new("cpbase\\particle\\orange.png",4,4)
    $_particleBlue.blend = ADD
    $_particleOrange    = Sprite.new("cpbase\\particle\\orange.png",4,4)
    $_particleOrange.blend = ADD

    $_particle = Sprite.new("cpbase\\particle\\particle.bmp",1,1)
    $_particle.blend = ADD
end


## speedX, speedY
## angleStep
## lifeTime
## 
##

class Processor
    def initialize
    end
    def dispose
    end

    def update
    end
end

class ParticleData
attr_accessor :x,:y
attr_accessor :sx,:sy
attr_accessor :angle,:angleStep
attr_accessor :angleDirection
attr_accessor :alpha, :alphaStep
attr_accessor :color
              
    def initialize
        @x = @y = 0
        @sx = @sy = 0
        @angle = @angleStep = 0
        @alpha = 255
        @alphaStep = -1
        @color = Color.White
    end
end

class ParticleGeneratorData
attr_accessor :x,:y, :z
attr_accessor :sx,:sy
attr_accessor :color
attr_accessor :activity
attr_accessor :processor
attr_accessor :speed
attr_accessor :lifeTime

    def initialize
        @x = @y = 0
        @z = Z_OBJECT
        @sx = @sy = 0
        @color = Color.White
        @activity = 100
        @processor = ""
        @speed = 1
        @lifeTime = 1000
    end
end

class Particle < GameObject
    attr_accessor :sx,:sy
    attr_accessor :angleStep
    attr_accessor :color

    attr_reader :x,:y
    attr_reader :angle
    attr_reader :lifeTime

    attr_reader :generator

    def initialize(d,s)
        super(d.x,d.y,$_particleBlue)

        @sx = d.sx
        @sy = d.sy
        @angle = d.angle
        @angleStep = d.angleStep
        @angleDirection = d.angleDirection
        @alpha = d.alpha
        @alphaStep = d.alphaStep
        @lifeTime = 0

        @generator = s

        @startTime = getTicks
    end
    def dispose
        @generator.delete self
    end

    def getSpeed
        @generator.speed
    end
    def getLifeTime
        @generator.lifeTime
    end
    def getRemainTime
        getTicks - @startTime
    end

    def process
        @x += @sx
        @y += @sy
        @angle += @angleStep
        @alpah += @alphaStep
    end
    def draw(x,y)
        $_particle.color = @color
        $_particle.angle = @angle
        $_particle.alpha = @alpha
#$_particleBlue.step = getRemainTime / 16
        $_particle.draw(@x,@y)
    end
    def update
        process

        if getRemainTime >= getLifeTime or
            @alpha <= 0
            dispose
        end

        draw(@x,@y)
    end
end

class ParticleGenerator < GameObject
    attr_accessor :x,:y
    attr_accessor :sx,:sy
    attr_accessor :color
    attr_accessor :activity
    attr_accessor :lifeTime
    attr_accessor :speed
            
    attr_reader :z
    attr_reader :processor

    def initialize(d)
        super(d.x,d.y,nil)

        @layer = Layer.new(d.z)

        @x = d.x
        @y = d.y
        @sx = d.sx
        @sy = d.sy
        @z = d.z
        @precessor = d.processor
        @color = d.color
        @activity = d.activity
        @speed = d.speed

        @lifeTime = 3000
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
        pd = ParticleData.new
        pd.x = @x
        pd.y = @y
        pd.angle = 0
        pd.angleDirection = rand(360)
        add(Particle.new(pd,self))
    end

    def update
        @x += @sx
        @y += @sy

        if rand(100) < @activity
            generate
        end
    end
end