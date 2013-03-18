###################################################
#             ChocoPie GameEngine                 #
#                           Window Select         #
###################################################

begin
    $_windowCursor    = Sprite.new("cpbase\\common\\windowCursor.png",1,1)
    if $_windowCursor == nil
	Debug.error "WindowSelect - Failed to load common resource"
    end   
end


class WindowSelect < WindowBase
    attr_accessor :dx, :dy
    attr_accessor :cursor
	
	include EventHandler

    def initialize(x,y,item,alpha=255)
        super(x,y,0,0,alpha)

        for i in 0..item.size-1
            size = @font.query(item[i])
			p size
            if @w < size.w  
                @w = size.w
            end
            @h += size.h
        end
        
        @dx = 10
        @dy = (@h*0.1).ceil
        
        @w *= 1.5
        @h *= 1.15

        @w = @w.ceil + 10
        @h = @h.ceil + 5	
        
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
                size = @font.query(@item[i])
                drawText(@w/2-size.w/2,@dy+20*i,@item[i])
            else
                drawText(@dx,@dy+20*i+2,@item[i])
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
        end
    end

	def keyDown(key)
		p key
		case key
			when UP
				if not @cursor == 0
					@cursor -= 1
					@cursorChangedHandler.call(self, @cursor)
				end
			when DOWN
				if not @cursor == @item.size-1
					@cursor += 1
					@cursorChangedHandler.call(self, @cursor)
				end
			when RETURN
				@itemSelectedHandler.call(self, @cursor)
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

