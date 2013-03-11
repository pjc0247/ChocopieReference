class Size
    attr_accessor :w, :h

    def initialize(w=0,h=0)
        set(w,h)
    end

    def dispose
    end

    def set(w=0,h=0)
        @w = w
        @h = h
    end

    def +(obj)
        return Size.new(@w+obj.w,@h+obj.h)
    end
    def -(obj)
        return Size.new(@w-obj.w,@h-obj.h)
    end
    def *(m)
        return Size.new(@w*m,@h*m)
    end
    def /(d)
        return Size.new(@w/m,@h/m)
    end
end
