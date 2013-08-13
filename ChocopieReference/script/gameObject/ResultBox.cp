class TextObject
    attr_accessor :color, :alpha, :size, :style
    attr_accessor :font
    attr_accessor :layer, :parent
    
    def initialize(x,y,msg)
        @color = Color.Black
        @alpha = 255
        @size = 20
        @style = NONE
        @parent = nil
        
        @msg = msg
        @x = x
        @y = y
    end
    def dispose
		@cache.clear
    end
    
    def font=(font)
        @font = font
        if @cache != nil
             @cache.clear
        else
             @cache = FontCache.new(@font)
        end
    end
    def draw(x,y)
        
        @font.color = @color
        @font.style = @style
        @cache.draw(x,y,@msg)    
    end
    def update
        draw(@x,@y-@parent.scroll.value)
    end
end
class LinkObject
end

class ResultBox < WindowBase
    attr_reader :scroll
    def initialize(x,y,w,h)
        super(x,y,w,h)

        @scroll = ScrollBar.new(x+w,y,10,h)
        @scroll.max = 100
        @scroll.ips = h
        
        @client = Sprite.new(nil,w,h)
        @client.map "resultClient"
        
        @ch = 0 # content height
        
        @font = []
        
        # pre-caching
        @font[20] = Font.new("gulim.ttc", 20)
        @font[13] = Font.new("gulim.ttc", 13)
        
        @layerObject = Layer.new(Z_OBJECT)
        $objmgr.delete @layerObject
    end

    def dispose
        super
    end

    def draw(x=0,y=0)
        $graphic.color = Color.new(128,128,128,128)
        $graphic.fill(x,y,w,h)
        
        $graphic.target = "resultClient"
        $graphic.clear
        $graphic.color = Color.new(0,0,0,0)
        $graphic.fill(0,0,@w,@h)
        @layerObject.update
        $graphic.target = nil
           
        drawSprite(0,0,@client)
    end
    def update
        super
    end
   
    def script
        
        
    end
    def load(file)
		@layerObject.clear
		@scroll.scroll = 0

        f = File.new(file,"r")
        doc = f.readlines
        f.close
        
        ystep = 10
        color = Color.Black
        size = 20
        style = NONE
        
        for i in 0..doc.size-1
            if doc[i][0].chr == '!'
                sp = doc[i].split(' ')
                cmd = sp[0]
                cmd = cmd[1..cmd.length]
                param = sp[1]
                
                case cmd
					when "color"
						c = param.split(',')
						color = Color.new(
									c[0].to_i,
									c[1].to_i,
									c[2].to_i)
					when "size"
						size = param.to_i
					when "style"
						case param
							when "bold"
								style = BOLD
							when "none"
								style = NONE
							when "underline"
								style = UNDERLINE
							when "stroke"
								style = STROKE
						end
                end
            else
				if doc[i].length > 1
					doc[i] = doc[i][0..doc[i].length-2]
					o = TextObject.new(10,ystep,doc[i])

					if @font[size] == nil
						@font[size] = Font.new("gulim.ttc", size)
         			end

					o.font = @font[size]
         			o.parent = self
         			o.color = color
					o.style = style

					@layerObject.add o      
				end

				ystep += size + 5
			end
        end

        o = TextObject.new(360,ystep + 30,"written by pjc")
        o.font = @font[13]
        o.style = BOLD
        o.parent = self
        o.color = Color.Black
        @layerObject.add o
        
        @ch = ystep + 100
        @scroll.max = @ch - @h
        @scroll.ips = @h

       # puts "ch " + @ch.to_s + ", ips " + @h.to_s
    end
end
