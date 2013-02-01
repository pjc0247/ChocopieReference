###################################################
#             ChocoPie GameEngine                 #
#                           Window Text           #
###################################################

class WindowText < WindowBase
    attr_accessor :dx, :dy

    def initialize(x,y,w,h,text="",alpha=255)

        super(x,y,w,h,alpha)
        @text = text
        @dx = 10
        @dy = 10
        @align = NONE
    end

    def align
        @align
    end
    def align=(a)
        @align = a
        if @align == CENTER
            size = @font.size(@text)
            @dx = @w/2 - size.w/2
            @dy = @h/2 - size.h/2
        end
    end

    def text
        @text
    end
    def text=(v)
        @text = v
        self.align = @align
    end

    
    def draw(x=0,y=0)
        super
        drawText(@dx,@dy,@text,@font)
    end
    def update
        super
    end
end

