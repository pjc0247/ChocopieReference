class FontCache
    def initialize(font)
        @font = font
        @cache = {}
    end
    def dispose
        clear
    end

    def delete(msg)
        if @cache[msg] == nil
            return
        end
        @cache[msg].dispose
        @cache.delete_if { |key,value| key == msg} 
    end
    def clear
        @cache.each do |key,value|
            value.dispose
        end
    end
    def draw(x,y,msg)
        if @cache[msg] == nil
            befColor = @font.color
            @font.color = Color.White
            @cache[msg] = @font.render(msg)
            @font.color = befColor
        end
        @cache[msg].color = @font.color
        @cache[msg].draw(x,y)
    end
end