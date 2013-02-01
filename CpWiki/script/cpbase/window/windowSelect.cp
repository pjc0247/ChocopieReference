###################################################
#             ChocoPie GameEngine                 #
#                           Window Select         #
###################################################

begin
    $_windowCursor    = Sprite.new("cpbase\\common\\windowCursor.png",1,1)
rescue
    puts "WindowSelect - 커먼 리소스 로드 실패"
end


class WindowSelect < WindowBase
    attr_accessor :dx, :dy
    attr_accessor :cursor

    def initialize(x,y,item,alpha=255)
        super(x,y,0,0,alpha)

        for i in 0..item.size-1
            size = @font.size(item[i])
            if @w < size.w  
                @w = size.w
            end
            @h += size.h
        end
        


        @dx = 10
        @dy = (@h*0.6 - @h*0.5).ceil
        
        @w *= 1.5
        @h *= 1.2

        @w = @w.ceil
        @h = @h.ceil
        
        @item = item
        @cursor = 0

        @align = NONE

        @alphaCur = 32 
        @alphaInc = 1
        @timer = Timer.new(15)
        @timer.start
    end

    def item
        @item
    end
    def item=(item)
        @text = item
    end

    def align
        @align
    end
    def align=(a)
        @align = a
    end 

    def draw(x=0,y=0)
        super
        for i in 0..@item.size-1
            if @cursor == i
                 $_windowCursor.alpha = @alphaCur
                stretchSprite(10,@dy+20*i,@w-20,20,
                        $_windowCursor)
            end

            if @align == CENTER
                size = @font.size(@item[i])
                drawText(@w/2-size.w/2,@dy+20*i,@item[i])
            else
                drawText(@dx,@dy+20*i,@item[i])
            end
        end
    end
    def update
        super

        if self.focused
            if @timer.done
                @alphaCur += @alphaInc
                if @alphaCur >= 128 or @alphaCur <= 32
                    @alphaInc *= -1
                end
            end

            if $input.trigger(UP) and @cursor != 0
                @cursor -= 1
                @cursorChangedHandler.call(self, @cursor)
            elsif $input.trigger(DOWN) and @cursor != @item.size-1
                puts "ASDF"
                @cursor += 1
                @cursorChangedHandler.call(self, @cursor)
            elsif $input.trigger(RETURN)
                puts self
                @itemSelectedHandler.call(self, @cursor)
                return @cursor
            end            
        end
    end


################

    def initializeHandler
        super
        self.cursorChangedHandler = method(:nullHandler)
        self.itemSelectedHandler = method(:nullHandler)
    end
    def cursorChangedHandler=(handler)
        @cursorChangedHandler = handler
    end
    def itemSelectedHandler=(handler)
        @itemSelectedHandler = handler
    end
end

