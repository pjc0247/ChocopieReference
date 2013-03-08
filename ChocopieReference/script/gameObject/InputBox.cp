#NONE = 0
EDIT = 1

class InputBox < WindowBase
    include EventHandler

    attr_accessor :text, :default

    @@font = Font.new("gulim.ttc",20)
    @@font.style = BOLD

    def initialize(x,y,w,h)
        super(x,y,w,h)

        @default = ""        
        @text = ""
        @shown = ""
        @state = NONE

        @carrot = "_"
        
        @timerCarrot = Timer.new(700)
        @timerCarrot.start
        
        @length = 0
        
        self.getFocusHandler = method(:getFocus)
        self.lostFocusHandler = method(:lostFocus)
    end
    def dispose
        super
    end

    def drawText(x,y,msg,color=Color.White,shadow=Color.DarkGray)
        @@font.color = shadow
        super(x+3,y+3,msg, @@font)
        @@font.color = color
        super(x,y,msg, @@font)
    end
    def draw(x=0,y=0)
        if @state == NONE
            $graphic.color = Color.new(128,128,128,128)
        elsif @state == EDIT
            $graphic.color = Color.new(90,90,90,190)
        end

        $graphic.blend = BLEND
        $graphic.fill(x,y,@w,@h)
        if @text.length == 0
            drawText(5,5, @default,
                    Color.new(180,180,180),Color.DarkGray)
        else
            drawText(5,5, @shown)
        end
    end
    def update
        super

        if @timerCarrot.done
            if @carrot == "_"
                @carrot = ""
            else
                @carrot = "_"
            end
        end
        
        if @state == EDIT
            @text = getTextInput
            if @text.length != @length
                @length = @text.length
                @textChangedHandler.call(self,nil)
            end
            @shown = @text + @carrot
        end
    end

    def leftUp(x,y)
        setFocus self
    end
    
    def getFocus(e,args)
        @state = EDIT
        @text = ""
        startTextInput
    end
    def lostFocus(e,args)
        @state = NONE
        endTextInput
    end
    
    
    def initializeHandler
        super
        self.textChangedHandler = method(:nullHandler)
    end
    def textChangedHandler=(handler)
        @textChangedHandler = handler
    end
end