$_particleBlue    = Sprite.new("cpbase\\particle\\blue.png",4,4)
$_particleBlue.blend = ADD
$_particleOrange    = Sprite.new("cpbase\\particle\\orange.png",4,4)
$_particleOrange.blend = ADD

$_particle = Sprite.new("cpbase\\particle\\particle.bmp",1,1)
$_particle.blend = ADD

if $_particleBlue == nil or $_particleOrange == nil or $_particle == nil
	Debug.error "Particle - Failed to load resource"
end

class Particle < GameObject
	auto_dispose :false

    attr_accessor :x,:y
    attr_accessor :sx,:sy
    attr_accessor :angle, :angleStep
	attr_accessor :angleDirection
	attr_accessor :alpha, :alphaStep
    attr_accessor :color, :speed
    attr_accessor :lifeTime

    attr_accessor :sprite

    attr_reader :generator

    def initialize(generator)
        super(generator.x,generator.y,$_particle)

        @sx = @sy = 0

        @angle = @angleStep = 0

        @alpha = 255
        @alphaStep = -1

		@angleDirection = rand(360)

        @color = Color.White

		@lifeTime = 1000
		@speed = 1

        @generator = generator

        @startTime = getTicks
    end
    def dispose
        @generator.delete self
    end

    def process
        @x += @sx *  @speed
        @y += @sy * @speed
        @angle += @angleStep
        @alpha += @alphaStep
    end
    def draw(x,y)
        @sprite.color = @color
        @sprite.angle = @angle
        @sprite.alpha = @alpha
        @sprite.step = (getTicks-@startTime) / 16
        @sprite.draw(@x,@y)
    end
    def update
        process

        if (getTicks-@startTime) >= @lifeTime or
            @alpha <= 0
            dispose
        end

        draw(@x,@y)
    end
end
