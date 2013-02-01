###################################################
#             ChocoPie GameEngine                 #
#                           Physics Objects       #
###################################################


# Physics객체를 사용하는 게임 오브젝트를 위한 클래스입니다.
class PhysicsObject < GameObject
    attr_reader :physics

    def initialize(bitmap)
        super(0,0,bitmap)

        @physics = Physics.new()
    end
    
    def asBox(w,h)
        @w = w
        @h = h
    end
    def asCircle(r)
        @rad = r
    end
    def asLine(x1,y1,x2,y2)
        @x1 = x1
        @x2 = x2
        @y1 = y1
        @y2 = y2
    end
    def create(x,y,type)
        @physics.create(x,y,type)
    end


    def draw
        @physics.draw
    end
    def update
        draw
    end
end