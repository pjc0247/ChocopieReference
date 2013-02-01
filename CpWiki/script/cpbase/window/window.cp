###################################################
#             ChocoPie GameEngine                 #
#                           Window Base           #
###################################################

Debug.protect("WindowBase - 커먼 리소스 로드 실패") do
    $_windowBack    = Sprite.new("cpbase\\common\\windowBack.png")
    $_windowFrame    = Sprite.new("cpbase\\common\\windowFrame.png")
    $_windowFont    = Font.new("gulim.ttc",20)
end

$windowFocus = 0
$windowFocused = nil

$windowFocusOld = 0
$windowFocusedOld = nil

def setFocus(w)
    if w == $windowFocused
        return
    end
    if $windowFocused != nil
        $windowFocused.lostFocusHandler.call($windowFocused, w)
    end

    $windowFocusOld = $windowFocus
    $windowFocusedOld = $windowFocused

    $windowFocus = w.id
    $windowFocused = w

    w.getFocusHandler.call(w, nil)
end
def lostFocus(w)
    if w != $windowFocused
        return
    end
    w.lostFocusHandler.call(w, $windowFocusedOld)
    
    $windowFocus = $windowFocusOld
    $windowFocused = $windowFocusedOld

    $windowFocusOld = 0
    $windowFocusedOld = nil

    if $windowFocused != nil
        $windowFocused.getFocusHandler.call($windowFocused, nil)
    end
end
def getFocus
    $windowFocused
end

class WindowBase
    attr_accessor :x,:y,:w,:h,:alpha
    attr_accessor :font, :visible
    attr_reader :tag, :id

    attr_accessor :hovered, :idx, :layer

    attr_reader :getFocusHandler, :lostFocusHandler

    def initialize(x,y,w,h,alpha = 255)
        @x = x
        @y = y
        @w = w
        @h = h

        @idx = 0

        @position = Point.new(x,y)
        @size = Size.new(w,h)

        @alpha = alpha
        @font = $_windowFont
        @tag = 0
        @id = rand(987654)+1

        @rect = Rect.new(x,y,w,h)

        @visible = true
        
        @color = Color.new(255,255,255)

        @hovered = false

        $winmgr.add self
        $layerWindow.add self

        initializeHandler
    end
    def dispose
        $winmgr.delete self
        $layerWindow.delete self
    end

    def rect
        @rect.x = @x
        @rect.y = @y
        @rect.w = @w
        @rect.h = @h
        @rect
    end

    def size
        @size.w = @w
        @size.h = @h
        return @size
    end

    def drawText(x,y,text,font = @font)
        #font.style(STRIKETHROUGH)
        tmp_alpha = font.alpha
        font.alpha = (alpha/255.0)*(tmp_alpha/255.0)*255.0
        font.draw(x+@x,y+@y,text)
        font.alpha = tmp_alpha
    end
    def drawSprite(x,y,sprite)
        tmp_alpha = sprite.alpha
        sprite.alpha = (alpha/255.0)*(tmp_alpha/255.0)*255.0
        sprite.draw(x+@x,y+@y)
        sprite.alpha = tmp_alpha
    end
    def stretchSprite(x,y,w,h,sprite)
        tmp_alpha = sprite.alpha
        sprite.alpha = (alpha/255.0)*(tmp_alpha/255.0)*255.0
        sprite.stretch(x+@x,y+@y,w,h)
        sprite.alpha = tmp_alpha
    end

    def color=(c)
        @color = c
    end
    def color
        @color
    end
    def applyAttributes
        $_windowBack.color = @color
        $_windowFrame.color = @color
        $_windowBack.alpha = @alpha
        $_windowFrame.alpha = @alpha
    end

    def draw(x=0,y=0)
        applyAttributes

        pw = @w / 100
        ph = @h / 100
        $_windowBack.stretch(
            @x+pw,@y+pw,
            @w-pw*2,@h-ph*2)
        $_windowFrame.stretch(  
            @x,@y,@w,@h)
    end
    def update
        if @visible == true
            self.draw(@x,@y)
        end
    end

    def event(e,arg)
        if e == QUIT
            dispose
        end
    end


###############
    def focus
        setFocus(self)
    end
    def  focused
        if $windowFocus == @id
            return true
        else return nil
        end
    end


###############
    def initializeHandler
        self.lostFocusHandler = method(:nullHandler)
        self.getFocusHandler = method(:nullHandler)
    end
    def getFocusHandler=(handler)
        @getFocusHandler = handler
    end
    def lostFocusHandler=(handler)
        @lostFocusHandler = handler
    end
end