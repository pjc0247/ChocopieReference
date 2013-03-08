class SpriteList
    attr_accessor :step

    def initialize(basePath)
        @list = []
        
        for i in 0..999
            path = basePath
##path += 
        end
    end
    def dispose
        for i in 0..@list.size-1
            @list[i].dispose
        end
    end

    def draw(x,y)
        
    end
end