###################################################
#             ChocoPie GameEngine                 #
#                           Window Button         #
###################################################

#NONE = 0
HOT = 1
#DOWN = 2

class WindowButton < WindowBase
    include EventHandler

    attr_accessor :dx, :dy
    attr_reader :state
    attr_accessor :img

    def initialize(x,y,w,h,text="",alpha=255)

        super(x,y,w,h,alpha)

        @state = NONE

        @text = text
        @dx = 10
        @dy = 10
        @align = NONE

        @img = nil
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
        if @state == NONE
            @color = Color.White
        elsif @state == HOT
            @color = Color.Gray
        elsif @state == DOWN
            @color = Color.DarkGray
        end

        if @img == nil
            super
        else
            @img.alpha = 255
            @img.color = @color
            @img.draw(@x,@y)
#        @img.stretch(@x,@y,@w,@h)
        end

        drawText(@dx,@dy,@text,@font)
    end
    def update
        super
    end



    def leftDown(x,y)
        @state = DOWN
    end
    def leftUp(x,y)
        if @state == DOWN
            @buttonPressedHandler.call(self,Point.new(x,y))
        end
        @state = HOT
    end
    def mouseHover(x,y)
        puts x,y
        @state = HOT
    end
    def mouseLeave(x,y)
        @state = NONE
    end


###########
    def initializeHandler
        super
        self.buttonPressedHandler = method(:nullHandler)
    end
    def buttonPressedHandler=(handler)
        @buttonPressedHandler = handler
    end
end

