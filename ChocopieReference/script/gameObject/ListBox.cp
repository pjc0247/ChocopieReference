class ListBox < WindowBase
    attr_accessor :item
    
    attr_accessor :select, :hot
    
    include EventHandler
    
    def initialize(x,y,w,h)
        super(x,y,w,h)
        
        @item = []
        
        @select = 0
        @hot = 0
		@hover = nil
        
        @font = Font.new("gulim.ttc", 15)
        @font.style = BOLD
		@cache = FontCache.new(@font)

        @visibleLines = ((h-6).to_f / (@font.size*1.2)).to_i
        
        @scroll = ScrollBar.new(x+w,y,10,h)
        @scroll.ips = @visibleLines

    end

    def dispose
       super

	   @scroll.dispose
    end
   
    def drawText(x,y,msg,color=Color.White,shadow=Color.DarkGray)
        @font.color = shadow
        @cache.draw(x+@x+2,y+@y+1,msg)
        @font.color = color
        @cache.draw(x+@x,y+@y,msg)
    end
    def draw(x=0,y=0)
        $graphic.color = Color.new(128,128,128,128)
        $graphic.fill(x,y,w,h)
        
        min = @scroll.value
        max = @item.size-1

        if max-min > @visibleLines-1
            max = min + @visibleLines - 1
        end
        
        for i in min..max
            if @select == i
                $graphic.color = Color.White
                $graphic.fill(3+x,y+3+(i-min)*@font.size*1.2,@w-6,@font.size+2)
                drawText(5,3+(i-min)*@font.size*1.2,@item[i],
                            Color.Black,Color.Gray)
            elsif @hot == i
                $graphic.color = Color.DarkGray
                $graphic.fill(3+x,y+3+(i-min)*@font.size*1.2,@w-6,@font.size+2)
                drawText(5,3+(i-min)*@font.size*1.2,@item[i])
            else
                drawText(5,3+(i-min)*@font.size*1.2,@item[i])
            end
        end
    end
    def update
        super
    end

	def mouseHover(x,y)
		@hover = true
	end
	def mouseLeave(x,y)
		@hover = nil
		@hot = -1
	end

    def mouseMove(x,y,state)
		@hot = ((y).to_f / (@font.size*1.2)).to_i + @scroll.value
    end
    def leftDown(x,y)
		@cache.delete @item[@select]
        @select = ((y).to_f / (@font.size*1.2)).to_i + @scroll.value
		@cache.delete @item[@select]
        if @item[@select] != nil
            @itemSelectedHandler.call(self,@select)
        end
    end
    
    def add(v)
        @item[@item.size] = v
        @scroll.max = @item.size - @visibleLines
    end
    def delete(v)
        @item.delete_if {|v,a| a == v }
        @scroll.max = @item.size - @visibleLines
    end
    def clear
        @item.clear
        @scroll.max = 0
        @scroll.scroll = 0 
        @select = 0
    end
    
    def initializeHandler
        super
        self.itemSelectedHandler = method(:nullHandler)
    end
    def itemSelectedHandler=(handler)
        @itemSelectedHandler = handler
    end
end