#NONE = 0
#HOT = 1
SCROLL = 2

class ScrollBar < WindowBase
    attr_accessor :scroll
    attr_accessor :ips
    
    include EventHandler
    
    def initialize(x,y,w,h)
        super(x-50,y,w+100,h)
        
        @max = 0
        @scroll = 0
        
        @state = NONE
        
        @ips = 10
    end

    def dispose
       super
    end
   
    def boxHeight
        if @ips > (@max+@ips)
            min = (@max+@ips)
            max = @ips
        else
            min = @ips
            max = (@max+@ips)
        end
        h = (min.to_f / (max+1)) * (@h-8) #((@h-8)/(@max+1)+1)
        
           
        
        if h < @h * 0.2
            h = @h * 0.2
        end
        h.round
    end
    def draw(x=0,y=0)
        $graphic.color = Color.new(128,128,128,128)
        $graphic.fill(x+50,y,w-100,h)
        
        if @max == 0
            return
        end
        
        if @state == NONE
            $graphic.color = Color.new(90,90,90,128)
        elsif @state == HOT
            $graphic.color = Color.new(60,60,60,190)
        elsif @state == SCROLL
            $graphic.color = Color.new(40,40,40,190)
        end

        $graphic.blend = BLEND
        $graphic.fill(x+52,y+@scroll+4,@w-104,boxHeight)
    end
    def update
        super
    end

    def max
        @max
    end
    def max=(v)
        @max = v
        if @max < 0
            @max = 0
        end
    end
    def value
        ((@scroll.to_f)/(@h-8-boxHeight) * @max).round
    end
    def box
        Rect.new(52,@scroll+4,@w-104,boxHeight)
    end
    def mouseMove(x,y,state)
        if @state == SCROLL
            @scroll = y-box.h/2
            
            if @scroll < 0
                @scroll = 0 
            elsif @scroll > @h-boxHeight-8
                @scroll = @h-boxHeight-8
            end
        else
            point = Rect.new(x,y,1,1)
        
            if HasIntersection(point,box)
                @state = HOT
            else
                @state = NONE
            end
        end
    end
    def leftDown(x,y)
        point = Rect.new(x,y,1,1)
        
        if HasIntersection(point,box)
            @state = SCROLL
        end
    end
    def leftUp(x,y)
        point = Rect.new(x,y,1,1)
        
        if HasIntersection(point,box)
            @state = HOT
        else
            @state = NONE
        end
    end
end