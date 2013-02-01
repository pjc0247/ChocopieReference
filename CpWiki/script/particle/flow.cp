class FlowParticle < Particle
    def process
        @x += fastSin(@angleDirection) * getSpeed
        @y += fastCos(@angleDirection) * getSpeed
        @angle += @angleStep
        @alpha += @alphaStep
    end
end

class FlowGenerator < ParticleGenerator
    def generate
        pd = ParticleData.new
        pd.x = @x
        pd.y = @y
        pd.angle = 0
        pd.angleDirection = rand(360)
        pd.alpha = 255
        pd.alphaStep = -1
        add(FlowParticle.new(pd,self))
    end
end