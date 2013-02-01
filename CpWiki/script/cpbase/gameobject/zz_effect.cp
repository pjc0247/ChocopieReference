###################################################
#             ChocoPie GameEngine                 #
#                           Effect Class          #
###################################################

class EffectObject < GameObject
    def initialize(x,y,w,h,link,img,interval = 30)
        super(x,y,img)
        @timer = Timer.new(interval)
        @timer.start
        @maxStep = @sprite.stepW * @sprite.stepH
        $layerEffect.add(self)

        if w != -1
            @w = w
            @h = h
        else
            @w = @sprite.w
            @h = @sprite.h
        end

        @link = link
    end
    def dispose
        super
        @timer.dispose
        $layerEffect.delete(self)
    end
    
    def draw(x,y)
        @sprite.step = @step
        @sprite.stretch(x,y,@w,@h)
    end
    def update
        if @link == nil
            draw(@x,@y)
        else
            draw(@link.x,@link.y)
        end
        
        if @timer.done
            @step += 1
            if @step == @maxStep
                dispose            
            end
        end        
    end
end

class Effect
    attr_accessor :sprite

    def initialize(img,w,h,sfx=nil,interval=30)
        @sprite = Sprite.new(img,w,h)
        @sfx = sfx
        @interval = interval
        if @sfx != nil
            @sfx = Sound.new(sfx,0)
        end
    end
    def dispose
        effectLayer = $objmgr.get(Z_EFFECT)
        effectLayer.o.each do |key,value|
            if value.sprite == @sprite
                effectLayer.delete value
            end
        end

        @sprite.dispose
        if @sfx != nil
            @sfx.dispose
        end
    end

    def create(x,y,w=-1,h=-1,link=nil)
        e = EffectObject.new(x,y,w,h,link,@sprite,@interval)
        if @sfx != nil        
            @sfx.play
        end
    end

    def update
        
    end
end