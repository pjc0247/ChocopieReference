class Sprite < Sprite_

    def self.new(path,w=1,h=1)
        return super(path,w,h)
    end

    def dispose
        if ! self.disposed
            @disposed = true
            super
        end
    end

    def disposed
        if @disposed == true
            return true
        else return nil
        end
    end
end