# 지연 로딩을 하는 스프라이트 이미지 리소스
class SpriteDelayLoad < Sprite
    attr_accessor :tw,:th, :tpath, :loaded

    def self.new(path,w=1,h=1)
        obj = super(nil,-1,-1)
        obj.tw = w
        obj.th = h
        obj.tpath = path
        obj.loaded = false
        return obj
    end

    # SpriteDelayLoad 객체의 메모리를 해제합니다. 만약 스프라이트가 메모리에 올려져 있다면
    # 메모리에서 내려줍니다.
    def dispose
        if (! self.disposed) and (self.loaded)
            @disposed = true
            super
        end
    end

    # 이 객체가 dispose되었는지 조사합니다.
    def disposed
        if @disposed == true
            return true
        else return nil
        end
    end

    # 강제로 메모리에 스프라이트를 로드합니다.
    def load
        if ! loaded
            Sprite.new(@tpath,@tw,@th)
            @loaded = true
        end
    end

    # 강제로 메모리에서 스프라이트를 언로드합니다.
    def unload
        if loaded
            self.dispose
            @loaded = false
        end
    end

    # 이 객체의 스프라이트가 로드되었는지 조사합니다.
    def loaded
        if @loaded == true
            return true
        else return nil
        end
    end

    # x,y 좌표에 스프라이트를 그립니다.
    def draw(x,y)
        if ! loaded
            load
        end
        super(x,y)
    end
end