class FontCache
    def initialize(font)
        @font = font
        @cache = {}
    end
    def dispose
        clear
    end

	def loaded(msg)
		@cache[msg]
	end
	def unload(msg)
		delete msg
	end
	def load(msg)
		return if loaded(msg)
		befColor = @font.color
        @font.color = Color.White
        @cache[msg] = @font.render(msg)
        @font.color = befColor
	end
    def delete(msg)
        return if not loaded(msg)
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