class SpriteNumber
    def initialize(img)
        @sprite = Sprite.new(img,10,1)
    end
    def dispose
        @sprite.dispose
    end

    def draw(x,y,num)
        str = String(num)

        for i in 0..str.length-1
            @sprite.setStep(
                num%10)
            @sprite.draw(
                x+@sprite.w*(str.length-i-1), y)
            num /= 10
        end
    end
end
